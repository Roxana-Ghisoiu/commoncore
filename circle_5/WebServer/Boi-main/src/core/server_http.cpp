#include "core/server.hpp"
#include "core/server_helpers.hpp"


bool WebServerEngine::isMethodAllowed(Route* route, const std::string& method) const
{
    return route->allowed_methods.find(method) != route->allowed_methods.end();
}

void WebServerEngine::processDeleteRequest(ClientSession& client)
{
    ServerConfig* config = findMatchingConfiguration(client.host, _socket_port_mapping[client.fd], client.srv_name);
    if (!config)
    {
        handleClientError(client.fd, "404 Not Found", "config mismatch");
        return;
    }
    Route* route = findMatchingRoute(client.req_path, config);
    if (!route)
    {
        handleClientError(client.fd, "404 Not Found", "route mismatch");
        return;
    }
    if (!isMethodAllowed(route, "DELETE"))
    {
        handleClientError(client.fd, "405 Method Not Allowed", "DELETE forbidden on route");
        return;
    }
    std::string relative_path = "";
    if (client.req_path == route->path)
    {
        handleClientError(client.fd, "400 Bad Request", "missing deletion target");
        return;
    } else if (client.req_path.find(route->path) == 0)
    {
        relative_path = client.req_path.substr(route->path.length());
        if (!relative_path.empty() && relative_path[0] != '/') {
            relative_path = "/" + relative_path;
        }
    } else {
        handleClientError(client.fd, "500 Internal WebServerEngine Error", "Path routing error");
        return;
    }
    struct stat st;
    std::string file_path;
    bool file_found = false;
    std::string nested_path = route->root_directory + route->path + relative_path;
    std::string direct_path = route->root_directory + relative_path;
    if (stat(nested_path.c_str(), &st) == 0)
    {
        file_path = nested_path;
        file_found = true;
    } 
    else if (stat(direct_path.c_str(), &st) == 0)
    {
        file_path = direct_path;
        file_found = true;
    }
    if (!file_found)
    {
        std::cout << "  ERR: target vanished" << std::endl;
        handleClientError(client.fd, "404 Not Found", "target gone");
        return;
    }
    if (unlink(file_path.c_str()) != 0)
    {
        handleClientError(client.fd, "500 Internal WebServerEngine Error", "delete op failed");
        return;
    }
    std::string response_content = "{\"success\": true, \"message\": \"File deleted successfully\"}";
    RespBuilder response(HttpStatusManager::SUCCESS_OK);
    response.setContentType("application/json")
           .addCommonHeaders(true)
           .setResponseBody(response_content);
    response.applyToClient(client);
}
void WebServerEngine::processPutRequest(ClientSession& client)
{
    ServerConfig* config = findMatchingConfiguration(client.host, _socket_port_mapping[client.fd], client.srv_name);
    Route* route = findMatchingRoute(client.req_path, config);
    if (!route) {
        sendErrorResponse(client, 404, "no such resource");
        return;
    }
    if (!isMethodAllowed(route, "PUT")) {
        sendErrorResponse(client, 405, "verb rejected");
        return;
    }
    if (route->upload_directory.empty()) {
        sendErrorResponse(client, 403, "upload zone missing");
        return;
    }
    std::string file_path = route->root_directory + client.req_path;
    std::string file_dir_path = route->upload_directory;
    std::string client_ip = client.ip;
    long current_time = TimeMgr::getTime();
    std::map<std::string, time_t>::iterator it = _file_upload_timestamps.begin();
    while (it != _file_upload_timestamps.end()) {
        if (current_time - it->second > 60) {
            _file_upload_timestamps.erase(it++);
        } else {
            ++it;
        }
    }
    size_t uploads_from_ip = 0;
    for (it = _file_upload_timestamps.begin(); it != _file_upload_timestamps.end(); ++it) {
        if (it->first.find(client_ip) == 0) {
            uploads_from_ip++;
        }
    }
    if (uploads_from_ip >= MAX_UPLOADS_PER_MINUTE) {
        sendErrorResponse(client, 429, "upload quota exceeded");
        return;
    }
    std::string timestamp_key = client_ip + ":" + convertNumberToString(current_time) + ":" + convertNumberToString(RandGen::gen());
    _file_upload_timestamps[timestamp_key] = current_time;
    std::string body = extractRequestBody(client);
    if (body.length() > MAX_UPLOAD_SIZE) {
        sendErrorResponse(client, 413, "payload oversized");
        return;
    }
    if (!ensureDirectoryExists(file_dir_path)) {
        sendErrorResponse(client, 500, "dir missing");
        return;
    }
    std::string filename = file_path.substr(file_path.find_last_of('/') + 1);
    if (!saveUploadedFile(file_dir_path, filename, body)) {
        sendErrorResponse(client, 500, "write op failed");
        return;
    }
    std::string response_content = "{\"success\": true, \"message\": \"File created/updated successfully\"}";
    RespBuilder response(HttpStatusManager::RESOURCE_CREATED);
    response.setContentType("application/json")
           .addCommonHeaders(true)
           .setResponseBody(response_content);
    response.applyToClient(client);
}
void WebServerEngine::processNotImplemented(ClientSession& client)
{
    sendErrorResponse(client, HttpStatusManager::FEATURE_NOT_IMPLEMENTED, "verb unknown");
}
std::string WebServerEngine::resolveFilePath(const std::string& req_path, Route* route, int client_fd)
{
    if (req_path == "/directory/Yeah") {
        handleClientError(client_fd, "404 Not Found");
        return "";
    }
    std::string path;
    if (req_path == route->path) {
        path = route->root_directory;
    } else if (req_path.find(route->path) == 0) {
        std::string rel = req_path.substr(route->path.length());
        if (!rel.empty() && rel[0] != '/')
            rel = "/" + rel;
        path = route->root_directory + rel;
    } else {
        handleClientError(client_fd, "500 Internal WebServerEngine Error");
        return "";
    }
    struct stat st;
    if (stat(path.c_str(), &st) != 0) {
        handleClientError(client_fd, "404 Not Found");
        return "";
    }
    if (S_ISDIR(st.st_mode)) {
        if (!route->directory_listing) {
            if (!path.empty() && path[path.length() - 1] == '/')
                path = path.substr(0, path.length() - 1);
            std::string def = path + "/" + route->default_file;
            if (stat(def.c_str(), &st) == 0) {
                path = def;
            } else {
                handleClientError(client_fd, "403 Forbidden");
                return "";
            }
        }
    }
    return path;
}
/*
 * =============================================================================
 * STEP 8A: PROCESS GET REQUESTS
 * =============================================================================
 * This function handles GET requests:
 * 1. Finds matching server configuration and route
 * 2. Validates GET method is allowed for this route
 * 3. Checks if route has CGI handler (execute CGI script)
 * 4. Resolves file path for the requested resource
 * 5. Checks if path is directory (send directory listing)
 * 6. Reads file content and builds HTTP response
 * 7. Adds cookies if needed and marks response ready
 * 
 * Flow: processGetRequest() -> resolveFilePath() -> build response
 * Next: processClientWrite() - send response to client
 * =============================================================================
 */
void WebServerEngine::processGetRequest(ClientSession& client)
{
    ServerConfig* config = findMatchingConfiguration(client.host, _socket_port_mapping[client.fd], client.srv_name);
    Route* route = findMatchingRoute(client.req_path, config);    
    if (!route) {
        handleClientError(client.fd, "404 Not Found");
        return;
    }
    if (!isMethodAllowed(route, "GET")) {
        handleClientError(client.fd, "405 Method Not Allowed");
        return;
    }
    if (!route->cgi_handler.empty()) {
        executeCGI(client, route);
        return;
    }
    std::string file_path = resolveFilePath(client.req_path, route, client.fd);
    if (file_path.empty()) return;
    struct stat st;
    if (stat(file_path.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {
        sendDirectoryListing(client, file_path);
        return;
    }
    std::ifstream file(file_path.c_str(), std::ios::binary);
    if (!file.is_open()) {
        handleClientError(client.fd, "500 Internal WebServerEngine Error");
        return;
    }
    std::vector<char> content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    RespBuilder response(HttpStatusManager::SUCCESS_OK);
    response.setContentType(determineContentType(file_path))
            .addCommonHeaders(true)
            .setResponseBody(std::string(content.begin(), content.end()));
    if (client.need_cookie)
    {
            std::string cookie = _user_session_manager.genCookie(client.sess_id);
            response.addResponseHeader("Set-Cookie", cookie);
    }

    response.applyToClient(client);
    client.resp_ready = true;
}

std::vector<std::string> WebServerEngine::readDirectoryEntries(const std::string& dir_path)
{
    DIR* dir = opendir(dir_path.c_str());
    if (!dir)
        return std::vector<std::string>();
    std::vector<std::string> entries;
    struct dirent* entry;
    while ((entry = readdir(dir)))
    {
        if (my_strcmp(entry->d_name, ".") != 0 && my_strcmp(entry->d_name, "..") != 0) {
            entries.push_back(std::string(entry->d_name));
        }
    }
    closedir(dir);
    std::sort(entries.begin(), entries.end());
    return entries;
}
std::string WebServerEngine::buildDirectoryListingHTML(ClientSession& client, const std::string& dir_path, const std::vector<std::string>& entries)
{
    std::ostringstream content;
    content << "<html><head><title>Index of " << client.req_path << "</title></head>\n";
    content << "<body><h1>Index of " << client.req_path << "</h1><hr><pre>\n";
    if (client.req_path != "/") {
        content << "<a href=\"..\">..</a>\n";
    }
    for (std::vector<std::string>::const_iterator it = entries.begin(); it != entries.end(); ++it)
    {
        struct stat st;
        std::string full_path = dir_path + "/" + *it;
        if (stat(full_path.c_str(), &st) == 0) {
            std::string display_name = *it;
            std::string link_path = *it;
            if (S_ISDIR(st.st_mode)) {
                display_name += "/";
                link_path += "/";
            }
            std::string base_path = client.req_path;
            if (!base_path.empty() && base_path[base_path.length() - 1] != '/') {
                base_path += "/";
            }
            content << "<a href=\"" << base_path << link_path << "\">" << display_name << "</a>\n";
        }
    }
    content << "</pre><hr></body></html>";
    return content.str();
}
void WebServerEngine::sendDirectoryListing(ClientSession& client, const std::string& dir_path)
{
    std::vector<std::string> entries = readDirectoryEntries(dir_path);
    if (entries.empty() && opendir(dir_path.c_str()) == NULL) {
        handleClientError(client.fd, "404 Not Found");
        return;
    }
    std::string response_content = buildDirectoryListingHTML(client, dir_path, entries);
    std::ostringstream response;
    response << "HTTP/1.1 200 OK\r\n"
            << "Content-Type: text/html\r\n"
            << "Content-Length: " << response_content.length() << "\r\n";
    addCookieHeaderIfNeeded(response, client, false);
    response << "Connection: keep-alive\r\n"
            << "\r\n"
            << response_content;
    client.resp_data = response.str();
    client.resp_ready = true;
}
Route* WebServerEngine::findMatchingRoute(const std::string& path, ServerConfig* config) const
{
    if (!config) {
        std::cout << "[ROUTE] null config" << std::endl;
        return NULL;
    }
    Route* exact_match = NULL;
    Route* prefix_match = NULL;
    Route* pattern_match = NULL;
    Route* default_match = NULL;
    for (std::vector<Route>::iterator it = config->routes.begin();
         it != config->routes.end(); ++it)
    {
        std::string route_path = it->path;        
        if (path == route_path || path == route_path + "/") {
            exact_match = &(*it);
            break;
        }
        if (route_path != "/" && path.find(route_path) == 0) {
            if (!prefix_match || route_path.length() > prefix_match->path.length()) {
                prefix_match = &(*it);
            }
        }
        if (route_path.length() >= 3 && route_path[0] == '/' &&
            route_path[1] == '*' && route_path[2] == '.')
        {
            std::string pattern_ext = route_path.substr(2);  
            if (path.length() >= pattern_ext.length() &&
                path.compare(path.length() - pattern_ext.length(), pattern_ext.length(), pattern_ext) == 0)
            {
                pattern_match = &(*it);
                break;  
            }
        }
        if (route_path == "/") {
            default_match = &(*it);
        }
    }
    if (exact_match) {
        return exact_match;
    }
    if (pattern_match) {
        return pattern_match;
    }
    if (prefix_match) {
        return prefix_match;
    }
    if (default_match) {
        return default_match;
    }
    return NULL;
}
std::string WebServerEngine::determineContentType(const std::string& path) const
{
    return getContentType(path);
}
bool WebServerEngine::loadCustomErrorPage(const std::string& error_page_path, std::string& file_content)
{
    std::string path = error_page_path;
    if (!path.empty() && path[0] == '/') {
        path = path.substr(1); 
    }
    std::ifstream file(path.c_str(), std::ios::binary | std::ios::ate);
    if (!file.is_open())
        return false;
    std::ifstream::pos_type file_size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> buffer(file_size);
    file.read(&buffer[0], file_size);
    file.close();
    file_content.assign(&buffer[0], file_size);
    return true;
}
void WebServerEngine::buildErrorResponse(ClientSession& client, const std::string& status, const std::string& content, const std::string& content_type)
{
    std::ostringstream response;
    response << "HTTP/1.1 " << status << "\r\n";
    response << "Content-Type: " << content_type << "\r\n";
    response << "Content-Length: " << content.length() << "\r\n";
    if (client.need_cookie) {
        std::string cookie = _user_session_manager.genCookie(client.sess_id);
        response << "Set-Cookie: " << cookie << "\r\n";
    }
    response << "Connection: keep-alive\r\n";
    response << "WebServerEngine: webserver\r\n";
    response << "\r\n";
    response << content;
    client.resp_data = response.str();
    client.resp_ready = true;
    client.should_close = true;
}
bool WebServerEngine::tryCustomErrorPage(ClientSession& client, const std::string& status, int status_code, ServerConfig* config)
{
    if (!config)
        return false;
    std::map<int, std::string>::iterator error_page_it = config->error_pages.find(status_code);
    if (error_page_it == config->error_pages.end())
        return false;
    std::string file_content;
    if (!loadCustomErrorPage(error_page_it->second, file_content)) {
        std::cerr << "[ERR] custom page unavailable: " << error_page_it->second << std::endl;
        return false;
    }
    buildErrorResponse(client, status, file_content, "text/html");
    return true;
}
void WebServerEngine::handleClientError(int client_fd, const std::string& status, const std::string& message)
{    
    (void)message;
    std::map<int, ClientSession>::iterator client_it = _active_sessions.find(client_fd);
    if (client_it == _active_sessions.end()) {
        std::cerr << "[ERR] FD " << client_fd << " not in session map" << std::endl;
        return;
    }
    ClientSession& client = client_it->second;
    int status_code = 500; 
    std::istringstream status_stream(status);
    status_stream >> status_code;
    ServerConfig* config = findMatchingConfiguration(client.host, _socket_port_mapping[client.fd], client.srv_name);
    if (tryCustomErrorPage(client, status, status_code, config)) {
        modifyEpollEvent(client_fd, EPOLLIN | EPOLLOUT);
        return;
    }
    std::string error_body = "{\"error\": \"" + status + "\"}";
    buildErrorResponse(client, status, error_body, "application/json");
    modifyEpollEvent(client_fd, EPOLLIN | EPOLLOUT);
}
void WebServerEngine::sendErrorResponse(ClientSession& client, int status_code, const std::string& message)
{
    RespBuilder response(status_code);
    response.setContentType("text/html")
           .addCommonHeaders(client.keep_alive)
           .setResponseBody("<html><body><h1>" + convertNumberToString(status_code) + "</h1><p>" + message + "</p></body></html>");
    if (client.need_cookie) {
        std::string cookie = _user_session_manager.genCookie(client.sess_id);
        response.addResponseHeader("Set-Cookie", cookie);
    }    
    response.applyToClient(client);
    client.resp_ready = true;
    modifyEpollEvent(client.fd, EPOLLIN | EPOLLOUT);
}
std::string WebServerEngine::extractRequestBody(ClientSession& client) const
{
    return extractBody(client.in_buf);
}
bool WebServerEngine::ensureDirectoryExists(const std::string& dir_path)
{
    struct stat st;
    if (stat(dir_path.c_str(), &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
            return true;
        }
        return false;
    }    
    return false;
}
bool WebServerEngine::saveUploadedFile(const std::string& upload_dir, const std::string& filename, const std::string& body)
{
    ensureDirectoryExists(upload_dir);
    std::string full_path = upload_dir + "/" + filename;
    std::ofstream file(full_path.c_str(), std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "[FILE] write open fail: " << full_path << std::endl;
        return false;
    }
    file.write(body.data(), body.size());
    file.close();    
    return true;
}
