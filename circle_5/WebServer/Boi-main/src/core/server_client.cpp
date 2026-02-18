#include "core/server.hpp"
#include "core/server_helpers.hpp"


bool WebServerEngine::readClientData(int client_fd, ClientSession& client)
{
    const int BUFFER_SIZE = CHUNK_SIZE;
    char buffer[BUFFER_SIZE];
    
    ssize_t bytes_read = recv(client_fd, buffer, BUFFER_SIZE - 1, MSG_DONTWAIT);
    
    if (bytes_read < 0) {
        if (errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK) {
            return true;
        }
        removeClientSession(client_fd);
        _total_error_count++;
        return false;
    }
    if (bytes_read == 0) {
        removeClientSession(client_fd);
        return false;
    }
    if (client.in_buf.size() + bytes_read > MAX_REQUEST_SIZE) {
        handleClientError(client.fd, "413 Payload Too Large");
        _total_error_count++;
        return false;
    }
    buffer[bytes_read] = '\0';
    client.in_buf.append(buffer, bytes_read);
    client.updateActive();
    return true;
}
Route* WebServerEngine::findAlternativeRoute(ServerConfig* config, ClientSession& client, Route* current_route)
{
    if (client.method != "POST")
        return current_route;
    for (std::vector<Route>::iterator itr = config->routes.begin(); itr != config->routes.end(); ++itr)
    {
        if (itr->path.length() >= 3 && itr->path.substr(0, 3) == "/*.")
        {        
            std::string pattern_ext = itr->path.substr(2);
            if (client.req_path.length() >= pattern_ext.length() &&
                client.req_path.compare(client.req_path.length() - pattern_ext.length(),
                                         pattern_ext.length(), pattern_ext) == 0 &&
                isMethodAllowed(&(*itr), client.method)) {
                return &(*itr);
            }
        }
    }
    return current_route;
}
bool WebServerEngine::handleMethodNotAllowed(ClientSession& client)
{
    if (client.method == "POST" && client.req_path == "/") {
        RespBuilder response(HttpStatusManager::METHOD_NOT_SUPPORTED);
        response.setContentType("text/html")
                .addCommonHeaders(false)
                .setResponseBody("<html><body><h1>405 Method Not Allowed</h1><p>Method not allowed for this resource</p></body></html>");
        response.applyToClient(client);
        client.keep_alive = false;
        client.resp_ready = true;
        modifyEpollEvent(client.fd, EPOLLIN | EPOLLOUT);
    } else {
        handleClientError(client.fd, "405 Method Not Allowed", "Method not allowed for this resource");
    }
    return false;
}
void WebServerEngine::dispatchRequestByMethod(ClientSession& client)
{
    if (client.method == "GET") {
        processGetRequest(client);
    } else if (client.method == "POST") {
        processPostRequest(client);
    } else if (client.method == "PUT") {
        processPutRequest(client);
    } else if (client.method == "DELETE") {
        processDeleteRequest(client);
    } else {
        processNotImplemented(client);
    }
}
/*
 * =============================================================================
 * STEP 7: PROCESS COMPLETE HTTP REQUEST
 * =============================================================================
 * This function processes a complete HTTP request:
 * 1. Parses HTTP headers if not already done
 * 2. Updates server statistics and request counters
 * 3. Finds matching server configuration and route
 * 4. Validates HTTP method is allowed for this route
 * 5. Dispatches request to appropriate handler (GET, POST, etc.)
 * 6. Sets up epoll for response sending
 * 
 * Flow: processCompleteRequest() -> findMatchingRoute() -> dispatchRequestByMethod()
 * Next: processGetRequest(), processPostRequest(), etc. - handle specific methods
 * =============================================================================
 */
bool WebServerEngine::processCompleteRequest(ClientSession& client, int client_fd)
{
    if (!client.hdrs_parsed) {
        parseHttpRequest(client);
        if (!client.hdrs_parsed) {
            return false;
        }
    }
    _total_request_count++;
    updateServerStatistics();
    ServerConfig* config = findMatchingConfiguration(client.host, _socket_port_mapping[client.fd], client.srv_name);
    Route* route = findMatchingRoute(client.req_path, config);
    if (!route) {
        handleClientError(client.fd, "404 Not Found", "Resource not found");
        _total_error_count++;
        return false;
    }
    if (!isMethodAllowed(route, client.method))
    {
        route = findAlternativeRoute(config, client, route);
        if (!isMethodAllowed(route, client.method))
        {
            return handleMethodNotAllowed(client);
        }
    }
    try {
        dispatchRequestByMethod(client);
        if (client.resp_ready) {
            modifyEpollEvent(client_fd, EPOLLIN | EPOLLOUT);
        }
    } catch (const std::exception& e) {
        std::cerr << "[REQ] handle err: " << e.what() << std::endl;
        handleClientError(client.fd, "500 Internal WebServerEngine Error");
        _total_error_count++;
        return false;
    }
    return true;
}
/*
 * =============================================================================
 * STEP 5: HANDLE CLIENT DATA RECEPTION
 * =============================================================================
 * This function processes incoming data from clients:
 * 1. Finds the client session for this file descriptor
 * 2. Reads incoming data from the client socket
 * 3. Checks if complete HTTP request headers received (\r\n\r\n)
 * 4. If complete, processes the full request
 * 5. Handles errors and cleanup
 * 
 * Flow: handleClientData() -> readClientData() -> processCompleteRequest()
 * Next: parseHttpRequest() - parse the HTTP headers
 * =============================================================================
 */
void WebServerEngine::handleClientData(int client_fd)
{
    std::map<int, ClientSession>::iterator it = _active_sessions.find(client_fd);
    if (it == _active_sessions.end()) {
        removeFromPolling(client_fd);
        close(client_fd);
        return;
    }    
    ClientSession& client = it->second;
    if (client.resp_ready) {
        return;
    }
    try {
        if (!readClientData(client_fd, client)) {
            return;
        }
        if (client.in_buf.find("\r\n\r\n") != std::string::npos) {
            processCompleteRequest(client, client_fd);
        }
    } catch (const std::exception& e) {
        std::cerr << "[DATA] process err: " << e.what() << std::endl;
        removeClientSession(client_fd);
        _total_error_count++;
    }
}
size_t WebServerEngine::calculateChunkSize(const ClientSession& client)
{
    size_t remaining = client.resp_data.size() - client.bytes_sent;
    if (client.resp_data.size() > 1 * 1024 * 1024) {
        return std::min(static_cast<size_t>(CHUNK_SIZE / 4), remaining);
    } else {
        return std::min(static_cast<size_t>(CHUNK_SIZE), remaining);
    }
}
bool WebServerEngine::handleSendError(int client_fd, int error_code)
{
    static int retry_count = 0;
    const int max_retries = 5;
    if (error_code == EAGAIN || error_code == EWOULDBLOCK) {
        if (retry_count < max_retries) {
            retry_count++;
            usleep(50 * retry_count);
            modifyEpollEvent(client_fd, EPOLLIN | EPOLLOUT);
            return true;
        } else {
            retry_count = 0;
            usleep(500);
            modifyEpollEvent(client_fd, EPOLLIN | EPOLLOUT);
            return true;
        }
    } else if (error_code == ENOBUFS || error_code == ENOMEM) {
        std::cerr << "[BUF] exhausted client " << client_fd 
                  << ": " << strerror(error_code) << std::endl;
        usleep(1000);
        modifyEpollEvent(client_fd, EPOLLIN | EPOLLOUT);
        return true;
    }
    std::cerr << "[SEND] err client " << client_fd << ": " << strerror(error_code) << std::endl;
    removeClientSession(client_fd);
    return false;
}
void WebServerEngine::resetClientForNextRequest(ClientSession& client)
{
    client.resp_data.clear();
    client.bytes_sent = 0;
    client.resp_ready = false;
    client.in_buf.clear();
    client.chunk_buf.clear();
    client.chunk_done = false;
    client.hdrs_parsed = false;
}
/*
 * =============================================================================
 * STEP 9: SEND RESPONSE TO CLIENT
 * =============================================================================
 * This function sends the prepared response to the client:
 * 1. Finds the client session for this file descriptor
 * 2. Calculates optimal chunk size for sending
 * 3. Sends data using send() system call
 * 4. Handles partial sends and errors
 * 5. Updates bytes sent counter
 * 6. If response complete, resets client for next request
 * 7. Handles keep-alive vs connection close
 * 
 * Flow: processClientWrite() -> send() -> resetClientForNextRequest()
 * Next: Back to handleClientData() for next request (if keep-alive)
 * =============================================================================
 */
void WebServerEngine::processClientWrite(int client_fd)
{
    if (_active_sessions.find(client_fd) == _active_sessions.end()) {
        return;
    }    
    ClientSession& client = _active_sessions[client_fd];
    client.updateActive();
    if (client.resp_data.empty()) {
        return;
    }
    size_t chunk_size = calculateChunkSize(client);
    ssize_t bytes_sent = send(client_fd, 
                             client.resp_data.c_str() + client.bytes_sent,
                             chunk_size,
                             MSG_NOSIGNAL | MSG_DONTWAIT);
    if (bytes_sent < 0) {
        handleSendError(client_fd, errno);
        return;
    }
    if (bytes_sent == 0) {
        std::cerr << "[CLI] " << client_fd << " disconnected mid-write" << std::endl;
        removeClientSession(client_fd);
        return;
    }
    client.bytes_sent += bytes_sent; 
    if (client.bytes_sent >= client.resp_data.size()) {   
        resetClientForNextRequest(client);
        if (!client.keep_alive) {
            removeClientSession(client_fd);
        } else {
            modifyEpollEvent(client_fd, EPOLLIN);
        }
    } else {
        modifyEpollEvent(client_fd, EPOLLIN | EPOLLOUT);
    }
}
void WebServerEngine::parseRequestLine(ClientSession& client, const std::string& line)
{
    std::istringstream request_line(line);
    request_line >> client.method >> client.req_path >> client.version;
}
void WebServerEngine::parseHostHeader(ClientSession& client, const std::string& header_value)
{
    std::string value = trimString(header_value);
    size_t colon_pos = value.find(':');
    if (colon_pos != std::string::npos)
    {
        client.host = value.substr(0, colon_pos);
        client.srv_name = client.host;
    } else {
        client.host = value;
        client.srv_name = value;
    }
}

void WebServerEngine::parseHeaderLine(ClientSession& client, const std::string& line)
{
    size_t colon_pos = line.find(':');
    if (colon_pos == std::string::npos)
        return;
    std::string header_name = trimString(line.substr(0, colon_pos));
    std::string header_value = trimString(line.substr(colon_pos + 1));
    if (header_name == "Host")
    {
        parseHostHeader(client, header_value);
    }
    else if (header_name == "Cookie")
    {
        client.sess_id = _user_session_manager.parseCookie(header_value);
    }
}

void WebServerEngine::initializeClientSession(ClientSession& client)
{
    if (client.sess_id.empty())
    {
        client.sess_id = _user_session_manager.create(client.hdrs["User-Agent"], client.ip);
    } else {
        _user_session_manager.updateAccess(client.sess_id);
    }
}

/*
 * =============================================================================
 * STEP 6: PARSE HTTP REQUEST HEADERS
 * =============================================================================
 * This function parses the HTTP request headers:
 * 1. Finds the end of headers (\r\n\r\n)
 * 2. Extracts and parses the request line (method, path, version)
 * 3. Parses individual header lines (Host, Cookie, etc.)
 * 4. Detects chunked transfer encoding
 * 5. Initializes client session with parsed data
 * 6. Marks headers as parsed
 * 
 * Flow: parseHttpRequest() -> parseRequestLine() -> parseHeaderLine()
 * Next: processCompleteRequest() - process the parsed request
 * =============================================================================
 */
void WebServerEngine::parseHttpRequest(ClientSession &client) 
{
    size_t header_end = client.in_buf.find("\r\n\r\n");
    if (header_end == std::string::npos)
    {
        return;
    }
    
    std::string header_data = client.in_buf.substr(0, header_end);
    std::istringstream header_stream(header_data);
    std::string line;
    bool first_line = true;
    client.need_cookie = true;
    client.sess_id = "";

    if (client.in_buf.find("Transfer-Encoding: chunked") != std::string::npos)
    {
        client.is_chunked = true;
    } else {
        client.is_chunked = false;
    }
    
    while (std::getline(header_stream, line))
    {
        if (line.empty() || line == "\r")
            continue;
        if (first_line)
        {
            parseRequestLine(client, line);
            first_line = false;
            continue;
        }
        parseHeaderLine(client, line);
    }
    initializeClientSession(client);
    client.hdrs_parsed = true;
}
std::string WebServerEngine::trimString(const std::string& str) const
{
    return trimWS(str);
}
void WebServerEngine::modifyEpollEvent(int fd, uint32_t events)
{
    struct epoll_event event;
    event.events = events;
    event.data.fd = fd;
    if (epoll_ctl(_event_monitor_fd, EPOLL_CTL_MOD, fd, &event) == -1) {
        std::cerr << "[POLL] mod err: " << strerror(errno) << std::endl;
    }
}
void WebServerEngine::addCookieHeaderIfNeeded(std::ostringstream& response, ClientSession& client, bool is_empty_post_to_root)
{
    if (client.need_cookie || is_empty_post_to_root) {
        std::string cookie = _user_session_manager.genCookie(client.sess_id);
        response << "Set-Cookie: " << cookie << "\r\n";
    }
}
void WebServerEngine::logRequestDebug(const ClientSession& client, const std::string& functionName) const
{
    std::cout << "\n=== Debug Log [" << functionName << "] ===" << std::endl;
    std::cout << "Client FD: " << client.fd << "\n";
    std::cout << "Request path: " << client.req_path << "\n";
    std::cout << "Request method: " << client.method << "\n";
    std::cout << "Host: " << client.host << "\n";
    std::cout << "WebServerEngine name: " << client.srv_name << "\n";    
    std::cout << "\n==== DEBUG: TRANSFER_COMPLETE REQUEST BUFFER ====\n";
    std::cout << client.in_buf.substr(0, 1000);
    if (client.in_buf.length() > 1000) {
        std::cout << "\n... [truncated, total size: " << client.in_buf.length() << " bytes]\n";
    }
    std::cout << "\n==== END TRANSFER_COMPLETE REQUEST BUFFER ====\n";
}
void WebServerEngine::debugPrintRequest(const ClientSession& client) const
{
    std::cout << "\n=== Request Debug Info ===" << std::endl;
    std::cout << "Client IP: " << client.ip << std::endl;
    std::cout << "Client FD: " << client.fd << std::endl;    
    size_t first_line_end = client.in_buf.find("\r\n");
    if (first_line_end != std::string::npos)
    {
        std::string request_line = client.in_buf.substr(0, first_line_end);
        std::cout << "Request Line: " << request_line << std::endl;    
        size_t method_end = request_line.find(' ');
        size_t path_end = request_line.find(' ', method_end + 1);
        if (method_end != std::string::npos && path_end != std::string::npos)
        {
            std::string method = request_line.substr(0, method_end);
            std::string path = request_line.substr(method_end + 1, path_end - (method_end + 1));
            std::string version = request_line.substr(path_end + 1);    
            std::cout << "  ┌ Method:  " << method << std::endl;
            std::cout << "  ├ Path:    " << path << std::endl;
            std::cout << "  └ Version: " << version << std::endl;
        }
    }
    size_t headers_start = first_line_end + 2;
    size_t headers_end = client.in_buf.find("\r\n\r\n");
    if (headers_end != std::string::npos && headers_start < headers_end)
    {
        std::string headers_section = client.in_buf.substr(headers_start, headers_end - headers_start);
        std::cout << "\nRequest Headers:\n";    
        size_t pos = 0;
        size_t line_end;
        while ((line_end = headers_section.find("\r\n", pos)) != std::string::npos)
        {
            std::string header_line = headers_section.substr(pos, line_end - pos);
            size_t colon_pos = header_line.find(':');
            if (colon_pos != std::string::npos)
            {
                std::string name = header_line.substr(0, colon_pos);
                std::string value = header_line.substr(colon_pos + 1);
                value.erase(0, value.find_first_not_of(' '));
                std::cout << "  " << name << ": " << value << std::endl;
            } else {
                std::cout << "  " << header_line << std::endl;
            }
            pos = line_end + 2;
        }
    }
    if (headers_end != std::string::npos)
    {
        size_t body_start = headers_end + 4;
        if (body_start < client.in_buf.size())
        {
            std::string body = client.in_buf.substr(body_start);
            size_t content_length = body.length();    
            std::cout << "\nRequest Body:\n";
            std::cout << "  Content-Length: " << content_length << " bytes\n";
            if (content_length > 0)
            {
                bool is_binary = false;
                for (size_t i = 0; i < std::min(content_length, (size_t)100) && !is_binary; i++)
                {
                    if (body[i] < 32 && body[i] != '\r' && body[i] != '\n' && body[i] != '\t') {
                        is_binary = true;
                    }
                }
                if (is_binary)
                {
                    std::cout << "  [Binary data - first 50 bytes shown as hex]\n  ";
                    for (size_t i = 0; i < std::min(size_t(50), body.length()); ++i) {
                        char hex_buf[4];
                        hex_buf[0] = "0123456789ABCDEF"[(unsigned char)body[i] >> 4];
                        hex_buf[1] = "0123456789ABCDEF"[(unsigned char)body[i] & 0x0F];
                        hex_buf[2] = ' ';
                        hex_buf[3] = '\0';
                        write(STDOUT_FILENO, hex_buf, 3);
                        if ((i + 1) % 16 == 0) write(STDOUT_FILENO, "\n  ", 3);
                    }
                    std::cout << std::endl;
                } else if (content_length > 1000) {
                    std::cout << "  " << body.substr(0, 997) << "...\n";
                    std::cout << "  [" << content_length - 1000 << " more bytes not shown]\n";
                } else {
                    std::cout << "  " << body << std::endl;
                }
            } else {
                std::cout << "  [Empty body]\n";
            }
        }
    }
    std::cout << "==== END CLIENT REQUEST DEBUG ====\n\n";
}
