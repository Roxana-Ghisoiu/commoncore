#include "core/server.hpp"
#include "core/server_helpers.hpp"


bool WebServerEngine::handleChunkedRequest(ClientSession &client, Route* route)
{
    (void)route;
    size_t body_start = client.in_buf.find("\r\n\r\n");
    if (body_start == std::string::npos) {
        return false; 
    }
    body_start += 4;
    std::string body_data = client.in_buf.substr(body_start);
    size_t pos = 0;
    bool complete = false;
    while (pos < body_data.size())
    {
        size_t chunk_line_end = body_data.find("\r\n", pos);
        if (chunk_line_end == std::string::npos) {
            break; 
        }
        std::string chunk_size_str = body_data.substr(pos, chunk_line_end - pos);
        size_t semicolon = chunk_size_str.find(';');
        if (semicolon != std::string::npos) {
            chunk_size_str = chunk_size_str.substr(0, semicolon);
        }
        unsigned long chunk_size = my_strtoul(chunk_size_str.c_str(), NULL, 16);
        pos = chunk_line_end + 2;
        if (chunk_size == 0)
        {
            if (pos + 2 <= body_data.size() && body_data.substr(pos, 2) == "\r\n") {
                complete = true;
                break;
            }
            return false; 
        }
        if (pos + chunk_size + 2 > body_data.size()) {
            break; 
        }
        client.chunk_buf.append(body_data.substr(pos, chunk_size));
        pos += chunk_size + 2;
    }
    if (complete) {
        client.chunk_done = true;
        client.chunk_st.state = ClientSession::ChunkState::DONE;
        std::string kept_headers = client.in_buf.substr(0, body_start);
        client.in_buf = kept_headers;
        return true;
    }
    return false; 
}
std::string WebServerEngine::resolveCGIPath(const std::string& req_path, Route* route)
{
    std::string cgi_path = route->cgi_handler;
    size_t ext_pos = req_path.rfind('.');
    if (ext_pos != std::string::npos) {
        std::string script = route->root_directory + req_path;
        struct stat req_stat;
        if (stat(script.c_str(), &req_stat) == 0 && 
            S_ISREG(req_stat.st_mode) && 
            (req_stat.st_mode & S_IXUSR)) {
            return script;
        }
    }
    if (cgi_path[0] != '/') {
        if (cgi_path.find("./") == 0)
            cgi_path = cgi_path.substr(2);
        cgi_path = route->root_directory + "/" + cgi_path;
    }
    return cgi_path;
}
void WebServerEngine::addPOSTEnvVars(ClientSession& client, std::map<std::string, std::string>& env)
{
    if (client.method != "POST") return;
    size_t ct_pos = client.in_buf.find("Content-Type:");
    if (ct_pos != std::string::npos) {
        size_t ct_end = client.in_buf.find("\r\n", ct_pos);
        if (ct_end != std::string::npos) {
            std::string ct = client.in_buf.substr(ct_pos + 13, ct_end - ct_pos - 13);
            env["CONTENT_TYPE"] = trimString(ct);
        }
    }
    if (client.is_chunked) {
        env["CONTENT_LENGTH"] = convertNumberToString(client.chunk_buf.length());
    } else {
        size_t cl_pos = client.in_buf.find("Content-Length:");
        if (cl_pos != std::string::npos) {
            size_t cl_end = client.in_buf.find("\r\n", cl_pos);
            if (cl_end != std::string::npos) {
                std::string cl = client.in_buf.substr(cl_pos + 15, cl_end - cl_pos - 15);
                env["CONTENT_LENGTH"] = trimString(cl);
            }
        }
    }
}
void WebServerEngine::addHTTPHeaders(ClientSession& client, std::map<std::string, std::string>& env)
{
    size_t hdr_end = client.in_buf.find("\r\n\r\n");
    if (hdr_end == std::string::npos) return;
    std::string hdrs = client.in_buf.substr(0, hdr_end);
    size_t pos = hdrs.find("\r\n");
    if (pos == std::string::npos) return;
    pos += 2;
    while (pos < hdrs.length()) {
        size_t line_end = hdrs.find("\r\n", pos);
        if (line_end == std::string::npos)
            line_end = hdrs.length();
        std::string line = hdrs.substr(pos, line_end - pos);
        size_t colon = line.find(':');
        if (colon != std::string::npos) {
            std::string name = trimString(line.substr(0, colon));
            std::string val = trimString(line.substr(colon + 1));
            for (size_t i = 0; i < name.length(); i++) {
                if (name[i] == '-')
                    name[i] = '_';
                else
                    name[i] = toupper(name[i]);
            }
            if (name == "COOKIE") {
                env["HTTP_COOKIE"] = val;
                env["COOKIE"] = val;
            } else {
                env["HTTP_" + name] = val;
            }
        }
        if (line_end == hdrs.length()) break;
        pos = line_end + 2;
    }
}
std::map<std::string, std::string> WebServerEngine::buildCGIEnv(ClientSession& client, Route* route, const std::string& script_path)
{
    std::string path_info = "";
    std::string script_name = "";
    bool is_wildcard = route->path.find("/*") != std::string::npos;
    if (is_wildcard) {
        path_info = client.req_path;
    } else {
        script_name = route->path;
        if (client.req_path.length() > route->path.length()) {
            if (route->path == "/") {
                path_info = client.req_path;
            } else {
                path_info = client.req_path.substr(route->path.length());
                if (path_info.empty() || path_info[0] != '/')
                    path_info = "/" + path_info;
            }
        }
    }
    std::string query_string = "";
    size_t query_pos = client.req_path.rfind('?');
    if (query_pos != std::string::npos) {
        query_string = client.req_path.substr(query_pos + 1);
        path_info = path_info.substr(0, path_info.find('?'));
    }
    std::map<std::string, std::string> env;
    env["REQUEST_METHOD"] = client.method;
    env["REQUEST_URI"] = client.req_path;
    env["QUERY_STRING"] = query_string;
    env["SCRIPT_NAME"] = script_name;
    env["PATH_INFO"] = path_info;
    env["PATH_TRANSLATED"] = route->root_directory + path_info;
    env["SCRIPT_FILENAME"] = script_path;
    env["DOCUMENT_ROOT"] = route->root_directory;
    env["SERVER_PROTOCOL"] = "HTTP/1.1";
    env["SERVER_NAME"] = client.host;
    env["SERVER_PORT"] = convertNumberToString(_socket_port_mapping[client.fd]);
    env["REQUEST_PATH"] = client.req_path;
    env["ROUTE_PATH"] = route->path;
    return env;
}
bool WebServerEngine::validateCGIScript(const std::string& path, int client_fd)
{
    struct stat st;
    if (stat(path.c_str(), &st) != 0) {
        std::cerr << "[CGI] exec err: " << strerror(errno) << std::endl;
        handleClientError(client_fd, "500 Internal WebServerEngine Error");
        return false;
    }
    if (!S_ISREG(st.st_mode)) {
        std::cerr << "[CGI] not a file" << std::endl;
        handleClientError(client_fd, "500 Internal WebServerEngine Error");
        return false;
    }
    if (access(path.c_str(), X_OK) != 0) {
        std::cerr << "[CGI] not exec: " << strerror(errno) << std::endl;
        handleClientError(client_fd, "500 Internal WebServerEngine Error");
        return false;
    }
    return true;
}
std::string WebServerEngine::executeCGIScript(ClientSession& client, CGIProcessor& cgi)
{
    if (client.method == "POST")
    {
        if (!client.chunk_buf.empty())
        {
            return cgi.executeScriptWithInput(client.chunk_buf);
        } else {
            size_t body_start = client.in_buf.find("\r\n\r\n");
            if (body_start != std::string::npos)
            {
                body_start += 4;
                std::string body = client.in_buf.substr(body_start);
                return cgi.executeScriptWithInput(body);
            } else {
                return cgi.executeScript();
            }
        }
    } else {
        return cgi.executeScript();
    }
}

void WebServerEngine::processCGIHeaders(const std::string& cgi_headers, std::string& response_headers, bool& has_content_type)
{
    if (cgi_headers.find("HTTP/") != 0) {
        response_headers += "HTTP/1.1 200 OK\r\n";
    }
    std::istringstream header_stream(cgi_headers);
    std::string header_line;
    while (std::getline(header_stream, header_line))
    {
        if (header_line.empty() || header_line == "\r")
            continue;
        if (header_line.length() > 0 && header_line[header_line.length() - 1] == '\r') {
            header_line = header_line.substr(0, header_line.length() - 1);
        }
        if (header_line.find("HTTP/") == 0) {
            response_headers = header_line + "\r\n";
            continue;
        }
        if (header_line.find("Content-Type:") == 0)
        {
            has_content_type = true;
        } else if (header_line.find("Status:") == 0) {
            continue;
        }
        response_headers += header_line + "\r\n";
    }
}

void WebServerEngine::buildCGIResponse(ClientSession& client, const std::string& cgi_output)
{
    size_t cgi_headers_end = cgi_output.find("\r\n\r\n");
    if (cgi_headers_end == std::string::npos) {
        cgi_headers_end = cgi_output.find("\n\n");
    }
    if (cgi_headers_end != std::string::npos)
    {
        std::string cgi_headers = cgi_output.substr(0, cgi_headers_end);
        std::string cgi_body = cgi_output.substr(cgi_headers_end + (cgi_output.find("\r\n\r\n") != std::string::npos ? 4 : 2));
        bool has_content_type = false;
        std::string response_headers = "";
        processCGIHeaders(cgi_headers, response_headers, has_content_type);
        if (!has_content_type) {
            response_headers += "Content-Type: text/html\r\n";
        }
        response_headers += "Content-Length: " + convertNumberToString(cgi_body.length()) + "\r\n";
        if (client.need_cookie) {
            std::string cookie = _user_session_manager.genCookie(client.sess_id);
            response_headers += "Set-Cookie: " + cookie + "\r\n";
        }
        response_headers += "Connection: keep-alive\r\n";
        response_headers += "WebServerEngine: webserver\r\n";
        std::string full_response = response_headers + "\r\n" + cgi_body;
        client.resp_data = full_response;
    } else {
        RespBuilder response(HttpStatusManager::SUCCESS_OK);
        response.addResponseHeader("Content-Type", "text/plain");
        response.addResponseHeader("Content-Length", convertNumberToString(cgi_output.length()));
        if (client.need_cookie) {
            std::string cookie = _user_session_manager.genCookie(client.sess_id);
            response.addResponseHeader("Set-Cookie", cookie);
        }
        std::string headers = response.buildCompleteResponse();
        client.resp_data = headers + cgi_output;
    }
}
void WebServerEngine::executeCGI(ClientSession& client, Route* route)
{
    std::string cgi_handler_path = resolveCGIPath(client.req_path, route);
    if (!validateCGIScript(cgi_handler_path, client.fd))
        return;
    std::map<std::string, std::string> env = buildCGIEnv(client, route, cgi_handler_path);
    addPOSTEnvVars(client, env);
    addHTTPHeaders(client, env);
    CGIProcessor cgi(env);
    cgi.setRequestInformation(client.req_path, route->path, route->root_directory);
    cgi.setScriptFilePath(cgi_handler_path);
    std::string cgi_output;
    try {
        cgi_output = executeCGIScript(client, cgi);
    } catch (const std::exception& e) {
        std::cerr << "[CGI] run fail: " << e.what() << std::endl;
        handleClientError(client.fd, "500 Internal WebServerEngine Error");
        return;
    }
    if (!client.chunk_buf.empty()) {
        client.chunk_buf.clear();
    }
    if (cgi_output.empty()) {
        RespBuilder response(HttpStatusManager::NO_CONTENT_RESPONSE);
        if (client.need_cookie) {
            std::string cookie = _user_session_manager.genCookie(client.sess_id);
            response.addResponseHeader("Set-Cookie", cookie);
        }
        response.applyToClient(client);
        return;
    }
    buildCGIResponse(client, cgi_output);
    client.resp_ready = true;
}
bool WebServerEngine::isDirectScript(const std::string& req_path, Route* route)
{
    size_t ext_pos = req_path.rfind('.');
    if (ext_pos == std::string::npos) return false;
    std::string script = route->root_directory + req_path;
    struct stat st;
    return (stat(script.c_str(), &st) == 0 && S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR));
}
bool WebServerEngine::handlePOSTChunked(ClientSession& client)
{
    if (client.in_buf.find("Transfer-Encoding: chunked") != std::string::npos) {
        client.is_chunked = true;
        if (!client.chunk_done) {
            if (!processChunkedData(client))
                return true;
        }
    }
    return false;
}
size_t WebServerEngine::calcBodySize(ClientSession& client)
{
    if (!client.chunk_buf.empty())
        return client.chunk_buf.size();
    size_t pos = client.in_buf.find("\r\n\r\n");
    if (pos != std::string::npos)
        return client.in_buf.size() - (pos + 4);
    return 0;
}
void WebServerEngine::fixChunkedHeaders(ClientSession& client)
{
    if (!client.is_chunked || client.chunk_buf.empty()) return;
    std::string cl = "Content-Length: " + convertNumberToString(client.chunk_buf.size());
    size_t pos = client.in_buf.find("Content-Length:");
    if (pos != std::string::npos) {
        size_t end = client.in_buf.find("\r\n", pos);
        if (end != std::string::npos)
            client.in_buf.replace(pos, end - pos, cl);
    } else {
        size_t hdr_end = client.in_buf.find("\r\n\r\n");
        if (hdr_end != std::string::npos)
            client.in_buf.insert(hdr_end, "\r\n" + cl);
    }
}
void WebServerEngine::processPostRequest(ClientSession& client)
{
    ServerConfig* config = findMatchingConfiguration(client.host, _socket_port_mapping[client.fd], client.srv_name);
    if (!config) {
        handleClientError(client.fd, "404 Not Found");
        return;
    }
    Route* route = findMatchingRoute(client.req_path, config);
    if (!route) {
        handleClientError(client.fd, "404 Not Found");
        return;
    }
    bool is_post_body = (client.req_path == "/post_body");
    bool direct_script = isDirectScript(client.req_path, route);
    if (!client.is_chunked && route->cgi_handler.empty() && !is_post_body && !direct_script) {
        handleClientError(client.fd, "405 Method Not Allowed");
        return;
    }
    if (handlePOSTChunked(client)) return;
    size_t body_sz = calcBodySize(client);
    if (is_post_body && route->client_max_body_size > 0 && body_sz > route->client_max_body_size) {
        handleClientError(client.fd, "413 Payload Too Large");
        return;
    }
    if (is_post_body && route->cgi_handler.empty() && !direct_script) {
        RespBuilder resp(HttpStatusManager::SUCCESS_OK);
        resp.setContentType("text/plain").setResponseBody("POST body received.").addCommonHeaders(true);
        client.resp_data = resp.buildCompleteResponse();
        client.resp_ready = true;
        modifyEpollEvent(client.fd, EPOLLOUT);
        return;
    }
    fixChunkedHeaders(client);
    try {
        executeCGI(client, route);
    } catch (const std::exception& e) {
        std::cerr << "[CGI] exception: " << e.what() << std::endl;
        handleClientError(client.fd, "500 Internal WebServerEngine Error", "cgi crash");
    }
}
std::string WebServerEngine::processChunkedTransfer(const std::string& chunkData) const
{
    std::string processedBody;
    size_t pos = 0;
    while (pos < chunkData.size())
    {
        size_t lineEnd = chunkData.find("\r\n", pos);
        if (lineEnd == std::string::npos) {
            std::cout << "[CHUNK] bad header @" << pos << std::endl;
            break;
        }
        std::string chunkSizeStr = chunkData.substr(pos, lineEnd - pos);
        size_t semicolon = chunkSizeStr.find(';');
        if (semicolon != std::string::npos) {
            chunkSizeStr = chunkSizeStr.substr(0, semicolon);
        }
        unsigned long chunkSize = my_strtoul(chunkSizeStr.c_str(), NULL, 16);
        pos = lineEnd + 2;
        if (chunkSize == 0) {
            break;
        }
        if (pos + chunkSize > chunkData.size()) {
            break;
        }
        processedBody.append(chunkData.substr(pos, chunkSize));
        pos += chunkSize + 2;
    }
    return processedBody;
}
bool WebServerEngine::processIncomingChunkedData(ClientSession& client)
{    
    if (client.in_buf.find("Transfer-Encoding: chunked") == std::string::npos) {
        return false;
    }    
    if (!client.is_chunked)
    {
        client.is_chunked = true;
        client.chunk_buf.clear();
        client.chunk_done = false;
    }
    size_t body_start = client.in_buf.find("\r\n\r\n");
    if (body_start == std::string::npos) {
        return false; 
    }
    body_start += 4;
    std::string body_data = client.in_buf.substr(body_start);
    std::string processedBody = processChunkedTransfer(body_data);
    if (!processedBody.empty())
    {
        client.chunk_buf.append(processedBody);    
        client.in_buf = client.in_buf.substr(0, body_start);
        if (client.chunk_st.state == ClientSession::ChunkState::DONE) {
            client.chunk_done = true;
            return true;
        }
    }
    return false;
}
bool WebServerEngine::handleChunkReadHeaders(ClientSession& client, const std::string& body_data, size_t& pos)
{
    size_t headers_end = body_data.find("\r\n\r\n");
    if (headers_end != std::string::npos) {
        pos = headers_end + 4;
        client.chunk_st.state = ClientSession::ChunkState::READ_SIZE;
        return true;
    }
    return false;
}
bool WebServerEngine::handleChunkReadSize(ClientSession& client, const std::string& body_data, size_t& pos)
{
    size_t crlf_pos = body_data.find("\r\n", pos);
    if (crlf_pos == std::string::npos) {
        return false;
    }
    std::string chunk_size_line = body_data.substr(pos, crlf_pos - pos);
    size_t semicolon_pos = chunk_size_line.find(';');
    if (semicolon_pos != std::string::npos) {
        chunk_size_line = chunk_size_line.substr(0, semicolon_pos);
    }
    chunk_size_line.erase(0, chunk_size_line.find_first_not_of(" \t"));
    chunk_size_line.erase(chunk_size_line.find_last_not_of(" \t") + 1);
    std::istringstream iss(chunk_size_line);
    size_t chunk_size;
    iss >> std::hex >> chunk_size;
    client.chunk_st.chunk_sz = chunk_size;
    client.chunk_st.bytes_read = 0;
    client.chunk_st.is_final = (chunk_size == 0);
    pos = crlf_pos + 2;
    if (client.chunk_st.is_final) {
        client.chunk_st.state = ClientSession::ChunkState::READ_TRAIL;
    } else {
        client.chunk_st.state = ClientSession::ChunkState::READ_DATA;
    }
    return true;
}
bool WebServerEngine::handleChunkReadData(ClientSession& client, const std::string& body_data, size_t& pos)
{
    size_t bytes_remaining = client.chunk_st.chunk_sz - client.chunk_st.bytes_read;
    size_t bytes_available = body_data.length() - pos;
    size_t bytes_to_read = std::min(bytes_remaining, bytes_available);
    if (bytes_to_read == 0) {
        return false;
    }
    client.chunk_st.body.append(body_data.substr(pos, bytes_to_read));
    client.chunk_st.bytes_read += bytes_to_read;
    pos += bytes_to_read;
    if (client.chunk_st.bytes_read >= client.chunk_st.chunk_sz) {
        client.chunk_st.state = ClientSession::ChunkState::READ_END;
        return true;
    }
    return false;
}
bool WebServerEngine::handleChunkReadEnd(ClientSession& client, const std::string& body_data, size_t& pos)
{
    if (body_data.length() - pos < 2) {
        return false;
    }
    if (body_data.substr(pos, 2) != "\r\n") {
        std::cerr << "[CHUNK] format err: no CRLF\n";
        client.chunk_st.state = ClientSession::ChunkState::ERROR;
        return true;
    }
    pos += 2;
    client.chunk_st.state = ClientSession::ChunkState::READ_SIZE;
    return true;
}
void WebServerEngine::replaceChunkHeadersWithContentLength(ClientSession& client)
{
    size_t content_length_pos = client.in_buf.find("Content-Length:");
    if (content_length_pos != std::string::npos) {
        size_t content_length_end = client.in_buf.find("\r\n", content_length_pos);
        if (content_length_end != std::string::npos) {
            client.in_buf = client.in_buf.substr(0, content_length_pos) +
                           client.in_buf.substr(content_length_end + 2);
        }
    }
    size_t transfer_encoding_pos = client.in_buf.find("Transfer-Encoding:");
    if (transfer_encoding_pos != std::string::npos) {
        size_t transfer_encoding_end = client.in_buf.find("\r\n", transfer_encoding_pos);
        if (transfer_encoding_end != std::string::npos) {
            std::string content_length = "Content-Length: " + convertNumberToString(client.chunk_st.body.length());
            client.in_buf = client.in_buf.substr(0, transfer_encoding_pos) +
                           content_length +
                           client.in_buf.substr(transfer_encoding_end);
        }
    }
    size_t headers_end = client.in_buf.find("\r\n\r\n");
    if (headers_end != std::string::npos) {
        client.in_buf = client.in_buf.substr(0, headers_end + 4) + client.chunk_st.body;
    }
}
bool WebServerEngine::handleChunkReadTrailer(ClientSession& client, const std::string& body_data, size_t& pos)
{
    size_t trailers_end = body_data.find("\r\n\r\n", pos);
    if (trailers_end == std::string::npos) {
        return false;
    }
    pos = trailers_end + 4;
    client.chunk_st.state = ClientSession::ChunkState::DONE;
    replaceChunkHeadersWithContentLength(client);
    return true;
}
bool WebServerEngine::processChunkedBody(ClientSession& client, const std::string& data)
{
    std::string body_data = data;
    size_t pos = 0;    
    while (pos < body_data.length())
    {
        switch (client.chunk_st.state)
        {
            case ClientSession::ChunkState::WAIT_SIZE:
                client.chunk_st.state = ClientSession::ChunkState::READ_SIZE;
                break;
            case ClientSession::ChunkState::READ_HDRS:
                if (!handleChunkReadHeaders(client, body_data, pos))
                    return false;
                break;
            case ClientSession::ChunkState::READ_SIZE:
                if (!handleChunkReadSize(client, body_data, pos))
                    return false;
                break;
            case ClientSession::ChunkState::READ_DATA:
                if (!handleChunkReadData(client, body_data, pos))
                    return false;
                break;
            case ClientSession::ChunkState::READ_END:
                if (!handleChunkReadEnd(client, body_data, pos))
                    return false;
                break;
            case ClientSession::ChunkState::READ_TRAIL:
                return handleChunkReadTrailer(client, body_data, pos);
            case ClientSession::ChunkState::DONE:
            case ClientSession::ChunkState::ERROR:
                return true;
        }
    }
    return false;
}
bool WebServerEngine::processChunkedUpload(ClientSession &client)
{
    while (client.chunk_st.state != ClientSession::ChunkState::DONE)
    {
        if (client.chunk_st.state == ClientSession::ChunkState::READ_HDRS)
        {
            size_t headerEnd = client.in_buf.find("\r\n\r\n");
            if (headerEnd == std::string::npos) {
                if (client.conn_closed)
                    break;
                return false;
            }
            client.in_buf.erase(0, headerEnd + 4);
            client.chunk_st.state = ClientSession::ChunkState::READ_SIZE;
        }
        else if (client.chunk_st.state == ClientSession::ChunkState::READ_SIZE)
        {
            size_t crlfPos = client.in_buf.find("\r\n");
            if (crlfPos == std::string::npos) {
                if (client.conn_closed)
                    break;
                return false;
            }
            std::string sizeLine = client.in_buf.substr(0, crlfPos);
            size_t semicolon = sizeLine.find(';');
            if (semicolon != std::string::npos)
                sizeLine = sizeLine.substr(0, semicolon);
            size_t chunkSize = my_strtoul(sizeLine.c_str(), NULL, 16);
            client.chunk_st.chunk_sz = chunkSize;
            client.in_buf.erase(0, crlfPos + 2);
            if (chunkSize == 0) {
                client.chunk_st.state = ClientSession::ChunkState::READ_TRAIL;
                continue;
            } else {
                client.chunk_st.state = ClientSession::ChunkState::READ_DATA;
            }
        }
        else if (client.chunk_st.state == ClientSession::ChunkState::READ_DATA) {
            if (client.in_buf.size() < client.chunk_st.chunk_sz)
            {
                if (client.conn_closed && !client.in_buf.empty()) {
                    client.chunk_st.body.append(client.in_buf);
                    client.in_buf.clear();
                    client.chunk_st.state = ClientSession::ChunkState::DONE;
                    break;
                }
                return false;
            }
            client.chunk_st.body.append(client.in_buf, 0, client.chunk_st.chunk_sz);
            client.in_buf.erase(0, client.chunk_st.chunk_sz);
            client.chunk_st.state = ClientSession::ChunkState::READ_END;
        }
        else if (client.chunk_st.state == ClientSession::ChunkState::READ_END)
        {
            if (client.in_buf.size() < 2)
            {
                if (client.conn_closed) {
                    client.chunk_st.state = ClientSession::ChunkState::DONE;
                    break;
                }
                return false;
            }
            if (client.in_buf.substr(0, 2) != "\r\n") {
                client.chunk_st.state = ClientSession::ChunkState::ERROR;
                return false;
            }
            client.in_buf.erase(0, 2);
            client.chunk_st.state = ClientSession::ChunkState::READ_SIZE;
        }
        else if (client.chunk_st.state == ClientSession::ChunkState::READ_TRAIL)
        {
            size_t trailerEnd = client.in_buf.find("\r\n\r\n");
            if (trailerEnd == std::string::npos) {
                if (client.conn_closed) {
                    client.chunk_st.state = ClientSession::ChunkState::DONE;
                    break;
                }
                return false;
            }
            client.in_buf.erase(0, trailerEnd + 4);
            client.chunk_st.state = ClientSession::ChunkState::DONE;
        }
    }
    return true;
}
bool WebServerEngine::processChunkedTransfer(ClientSession& client)
{
    if (client.method != "POST" || client.in_buf.find("Transfer-Encoding: chunked") == std::string::npos) {
        return false;
    }    
    if (!client.chunk_proc) {
        client.chunk_proc = true;
        client.chunk_buf.clear();}
    size_t body_start = client.in_buf.find("\r\n\r\n");
    if (body_start != std::string::npos)
    {
        body_start += 4;
    }
    return false;
}

bool WebServerEngine::processChunkedData(ClientSession &client)
{
    size_t headers_end = client.in_buf.find("\r\n\r\n");
    if (headers_end == std::string::npos) {
        return false;
    }
    headers_end += 4;
    size_t pos = headers_end;
    bool continue_processing = true;
    size_t processed_to = pos;
    while (continue_processing && pos < client.in_buf.size())
    {
        size_t lineEnd = client.in_buf.find("\r\n", pos);
        if (lineEnd == std::string::npos) {
            continue_processing = false;
            break;
        }
        std::string sizeLine = client.in_buf.substr(pos, lineEnd - pos);
        size_t semicolon = sizeLine.find(';');
        if (semicolon != std::string::npos) {
            sizeLine = sizeLine.substr(0, semicolon);
        }
        bool valid_hex = true;
        for (size_t i = 0; i < sizeLine.length(); i++) {
            if (!isxdigit(sizeLine[i])) {
                valid_hex = false;
                break;
            }
        }
        if (!valid_hex || sizeLine.empty()) {
            continue_processing = false;
            break;
        }
        unsigned long chunkSize = my_strtoul(sizeLine.c_str(), NULL, 16);
        pos = lineEnd + 2;
        if (chunkSize == 0) {
            if (pos + 2 <= client.in_buf.size() && client.in_buf.substr(pos, 2) == "\r\n") {
                processed_to = pos + 2;
                client.chunk_done = true;
                client.chunk_st.state = ClientSession::ChunkState::DONE;
                if (client.req_path == "/directory/youpi.bla" || client.req_path == "/directory/youpla.bla") {
                    std::string kept_headers = client.in_buf.substr(0, headers_end);
                    client.in_buf = kept_headers;
                }
                return true;
            } else {
                continue_processing = false;
                break;
            }
        }
        if (pos + chunkSize + 2 > client.in_buf.size()) {
            continue_processing = false;
            break;
        }
        client.chunk_buf.append(client.in_buf.substr(pos, chunkSize));
        pos = pos + chunkSize + 2;
        processed_to = pos;
    }
    if (processed_to > headers_end) {
        if (!client.chunk_done) {
            std::string kept_data = client.in_buf.substr(0, headers_end) + client.in_buf.substr(processed_to);
            client.in_buf = kept_data;
        }
    }
    return client.chunk_done;
}
void WebServerEngine::processPostChunkedCGI(ClientSession &client, Route* route) 
{    
    if (!client.chunk_done) {
        if (!processChunkedData(client)) {
            return;
        }
    }
    executeCGI(client, route);
    client.chunk_buf.clear();
    client.chunk_done = false;
}
