#include "core/server.hpp"
#include "core/server_helpers.hpp"


bool WebServerEngine::_server_running = true;

void WebServerEngine::signalHandler(int signum)
{
    std::cout << "\n[SIG] Caught " << signum << " (" 
              << my_strsignal(signum) << ") - stopping" << std::endl;
    _server_running = false;
}

void WebServerEngine::configureSignalHandlers()
{
    if (signal(SIGINT, &signalHandler) == SIG_ERR)
        throw std::runtime_error("SIGINT bind fail");
    if (signal(SIGTERM, &signalHandler) == SIG_ERR)
        throw std::runtime_error("SIGTERM bind fail");
    if (signal(SIGQUIT, &signalHandler) == SIG_ERR)
        throw std::runtime_error("SIGQUIT bind fail");
    if (signal(SIGTSTP, &signalHandler) == SIG_ERR)
        throw std::runtime_error("SIGTSTP bind fail");
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        throw std::runtime_error("SIGPIPE ignore fail");
}

WebServerEngine::WebServerEngine() : _event_monitor_fd(-1), _total_request_count(0), _total_error_count(0), _requests_per_second_count(0)
{
        _event_monitor_fd = epoll_create1(0);
        if (_event_monitor_fd == -1) {
            throw std::runtime_error("epoll init error");
        }
        configureSignalHandlers();
        initializeConnectionPool();
        TimeMgr::init();
        
        _last_cleanup_time = TimeMgr::getTime();
        _last_rate_limit_cleanup_time = TimeMgr::getTime();
        _last_rps_update_time = TimeMgr::getTime();
}

void WebServerEngine::initializeConnectionPool()
{
    _connection_pool.reserve(CONNECTION_POOL_SIZE);
    for (int i = 0; i < CONNECTION_POOL_SIZE; ++i) {
        _connection_pool.push_back(ClientSession());
    }
}

bool WebServerEngine::validateRateLimit(const std::string& ip)
{
    long current_time = TimeMgr::getTime();
    
    if (current_time - _last_rate_limit_cleanup_time > 10) {
        cleanupRateLimits();
        _last_rate_limit_cleanup_time = current_time;
    }
    if (_request_timestamps.find(ip) == _request_timestamps.end()) {
        _request_timestamps[ip] = current_time;
        _request_counters[ip] = 1;
        return true;
    }
    if (current_time - _request_timestamps[ip] >= 1) {
        _request_counters[ip] = 1;
        _request_timestamps[ip] = current_time;
        return true;
    }
    return (++_request_counters[ip] <= MAX_REQUESTS_PER_SECOND);
}

void WebServerEngine::cleanupRateLimits()
{
    long current_time = TimeMgr::getTime();
    std::vector<std::string> to_remove;
    
    for (std::map<std::string, time_t>::iterator it = _request_timestamps.begin();
         it != _request_timestamps.end(); ++it) {
        if (current_time - it->second > 60) {
            to_remove.push_back(it->first);
        }
    }
    for (size_t i = 0; i < to_remove.size(); ++i) {
        _request_timestamps.erase(to_remove[i]);
        _request_counters.erase(to_remove[i]);
    }
}

void WebServerEngine::updateServerStatistics()
{
    long current_time = TimeMgr::getTime();
    if (current_time - _last_rps_update_time >= 1) {
        _requests_per_second_count = _total_request_count - _last_rps_update_time;
        _last_rps_update_time = _total_request_count;
    }
    _total_request_count++;
}

/*
 * =============================================================================
 * STEP 3: INITIALIZE ALL SERVER SOCKETS
 * =============================================================================
 * After loading configuration, this function:
 * 1. Collects all unique ports from server configurations
 * 2. Creates listening sockets for each port
 * 3. Sets up non-blocking socket configuration
 * 4. Binds sockets to ports and starts listening
 * 
 * Flow: initializeAllServerSockets() -> initializeServerSocket() (for each port)
 * Next: startServer() - begins the main event loop
 * =============================================================================
 */
void WebServerEngine::initializeAllServerSockets()
{
    std::set<int> unique_ports;
    
    for (size_t i = 0; i < _server_configurations.size(); ++i)
    {
        unique_ports.insert(_server_configurations[i].port);
    }
    for (std::set<int>::iterator it = unique_ports.begin(); it != unique_ports.end(); ++it)
    {
        try {
            initializeServerSocket(*it);
        } catch (const std::exception& e) {
            std::cerr << "[SRV] port " << *it << " init fail: " << e.what() << std::endl;
        }
    }
    
    if (_listening_sockets.empty())
    {
        throw std::runtime_error("all ports unavailable");
    }
}

WebServerEngine::~WebServerEngine()
{
    shutdownServer();
}

bool WebServerEngine::addToPolling(int fd, uint32_t events)
{
        struct epoll_event ev;
        ev.events = events | EPOLLET;
        ev.data.fd = fd;
        if (epoll_ctl(_event_monitor_fd, EPOLL_CTL_ADD, fd, &ev) == -1) {
            std::cerr << "[POLL] add err: " << strerror(errno) << std::endl;
            return false;
        }
        return true;
}
    
bool WebServerEngine::removeFromPolling(int fd)
{
    if (epoll_ctl(_event_monitor_fd, EPOLL_CTL_DEL, fd, NULL) == -1) {
        if (errno != EBADF && errno != ENOENT) {
            std::cerr << "[POLL] del err: " << strerror(errno) << std::endl;
            return false;
        }
    }
    return true;
}

void WebServerEngine::configureNonBlockingSocket(int socket)
{
    int flags = fcntl(socket, F_GETFL, 0);
    if (flags == -1)
        throw std::runtime_error("fcntl F_GETFL fail");
    if (fcntl(socket, F_SETFL, flags | O_NONBLOCK) == -1)
        throw std::runtime_error("fcntl O_NONBLOCK fail");
}

void WebServerEngine::configureClientSocket(int client_fd)
{
    int opt = 1;
    setsockopt(client_fd, SOL_SOCKET, SO_KEEPALIVE, &opt, sizeof(opt));
    setsockopt(client_fd, IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(opt));
    
    int send_buffer = SOCKET_SEND_BUFFER;
    int recv_buffer = SOCKET_RECV_BUFFER;
    setsockopt(client_fd, SOL_SOCKET, SO_SNDBUF, &send_buffer, sizeof(send_buffer));
    setsockopt(client_fd, SOL_SOCKET, SO_RCVBUF, &recv_buffer, sizeof(recv_buffer));
    
    struct linger lin;
    lin.l_onoff = 0;
    lin.l_linger = 0;
    setsockopt(client_fd, SOL_SOCKET, SO_LINGER, &lin, sizeof(lin));
    
}

ClientSession WebServerEngine::createNewClientSession(int client_fd, const std::string& client_ip)
{
    ClientSession client_conn;
    client_conn.fd = client_fd;
    client_conn.ip = client_ip;
    client_conn.last_active = TimeMgr::getTime();
    client_conn.bytes_sent = 0;
    client_conn.resp_ready = false;
    client_conn.is_chunked = false;
    client_conn.chunk_done = false;
    client_conn.keep_alive = true;
    return client_conn;
}

bool WebServerEngine::acceptAndRegisterClient(int server_socket, int client_fd, const std::string& client_ip)
{
    ClientSession client_conn = createNewClientSession(client_fd, client_ip);
    
    _active_sessions[client_fd] = client_conn;
    _socket_port_mapping[client_fd] = _socket_port_mapping[server_socket];
    _ip_connection_counts[client_ip]++;
    
    if (!addToPolling(client_fd, EPOLLIN)) {
        std::cerr << "[POLL] client add failed" << std::endl;
        removeClientSession(client_fd);
        return false;
    }
    return true;
}

/*
 * =============================================================================
 * STEP 4: PROCESS NEW CLIENT CONNECTIONS
 * =============================================================================
 * This function handles incoming client connections:
 * 1. Accepts new client connections from listening sockets
 * 2. Validates rate limits and connection limits
 * 3. Configures client socket (non-blocking, TCP options)
 * 4. Creates new client session and adds to epoll monitoring
 * 5. Registers client for future event handling
 * 
 * Flow: processNewConnection() -> accept() -> validateRateLimit() -> addToPolling()
 * Next: handleClientData() - when client sends data
 * =============================================================================
 */
void WebServerEngine::processNewConnection(int server_socket)
{
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    
    for (int batch = 0; batch < 16; batch++) {
        int client_fd = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                break;
            }
            if (errno == EINTR) {
                continue;
            }
            std::cerr << "[NET] accept err: " << strerror(errno) << std::endl;
            break;
        }
        
        std::string client_ip = my_inet_ntoa(client_addr.sin_addr);
        if (!validateRateLimit(client_ip)) {
            close(client_fd);
            continue;
        }
        if (_active_sessions.size() >= MAX_CONNECTIONS) {
            close(client_fd);
            continue;
        }
        
        configureNonBlockingSocket(client_fd);
        configureClientSocket(client_fd);
        acceptAndRegisterClient(server_socket, client_fd, client_ip);
    }
}

void WebServerEngine::performPeriodicMaintenance(long& last_cleanup, long& last_stats)
{
    long current_time = TimeMgr::getTime();
    if (current_time - last_cleanup > CLEANUP_INTERVAL) {
        cleanupInactiveClientSessions();
        cleanupRateLimits();
        _user_session_manager.cleanup();
        last_cleanup = current_time;
        if (current_time - last_stats > 60) {
            last_stats = current_time;
        }
    }
}

int WebServerEngine::waitForEvents(void* events)
{
    return epoll_wait(_event_monitor_fd, (struct epoll_event*)events, MAX_EVENTS, 1000);
}

void WebServerEngine::extractEventData(void* events, int index, int& fd, uint32_t& event_flags)
{
    struct epoll_event* ev = (struct epoll_event*)events;
    fd = ev[index].data.fd;
    event_flags = ev[index].events;
}

bool WebServerEngine::isListeningSocket(int fd)
{
    for (size_t j = 0; j < _listening_sockets.size(); ++j)
    {
        if (fd == _listening_sockets[j])
        {
            return true;
        }
    }
    return false;
}

void WebServerEngine::handleClientEvent(int fd, uint32_t event_flags)
{
    try {
        if (event_flags & EPOLLIN) {
            handleClientData(fd);
        }
        if (event_flags & EPOLLOUT)
            processClientWrite(fd);
        if (event_flags & (EPOLLERR | EPOLLHUP)) {
            removeClientSession(fd);
            _total_error_count++;
        }
    } catch (const std::exception& e) {
        std::cerr << "[CLI] err on " << fd << ": " << e.what() << std::endl;
        removeClientSession(fd);
        _total_error_count++;
    }
}

void WebServerEngine::processEvents(void* events, int nfds)
{
    for (int i = 0; i < nfds; i++)
    {
        int current_fd;
        uint32_t current_event_buffer;
        
        extractEventData(events, i, current_fd, current_event_buffer);
        
        if (isListeningSocket(current_fd))
        {
            if (current_event_buffer & EPOLLIN)
                processNewConnection(current_fd);
        }
        else
        {
            handleClientEvent(current_fd, current_event_buffer);
        }
    }
}

/*
 * =============================================================================
 * STEP 2: MAIN SERVER EVENT LOOP
 * =============================================================================
 * This is the heart of the web server - the main event loop:
 * 1. Initializes epoll event monitoring
 * 2. Runs continuous loop while server is running
 * 3. Performs periodic maintenance (cleanup, statistics)
 * 4. Waits for events using epoll (new connections, data, etc.)
 * 5. Processes all ready events (new connections, client data, responses)
 * 6. Handles shutdown gracefully
 * 
 * Flow: startServer() -> waitForEvents() -> processEvents() -> [handle events]
 * Events: processNewConnection(), handleClientData(), processClientWrite()
 * =============================================================================
 */
void WebServerEngine::startServer()
{
    _server_running = true;
    struct epoll_event events[MAX_EVENTS];
    void* events_ptr = events;
    
    long last_cleanup = TimeMgr::getTime();
    long last_stats = TimeMgr::getTime();
    
    while (_server_running)
    {
        performPeriodicMaintenance(last_cleanup, last_stats);
        
        int nfds = waitForEvents(events_ptr);
        
        if (nfds == -1)
        {
            if (errno == EINTR)
            {
                if (!_server_running)
                {
                    std::cout << "[SRV] terminating..." << std::endl;
                    break;
                }
                continue;
            }
            throw std::runtime_error("poll wait err: " + std::string(strerror(errno)));
        }
        
        processEvents(events_ptr, nfds);
    }
    performServerCleanup();
}

void WebServerEngine::shutdownServer()
{
    _server_running = false;
    for (std::map<int, ClientSession>::iterator it = _active_sessions.begin(); 
         it != _active_sessions.end(); ++it) {
        close(it->first);
    }
    _active_sessions.clear();
    if (_event_monitor_fd != -1) {
        close(_event_monitor_fd);
        _event_monitor_fd = -1;
    }
    for (std::vector<int>::iterator it = _listening_sockets.begin(); 
         it != _listening_sockets.end(); ++it) {
        if (*it != -1) {
            close(*it);
        }
    }
    _listening_sockets.clear();
}

void WebServerEngine::cleanupInactiveClientSessions()
{
    long current_time = TimeMgr::getTime();
    std::vector<int> to_remove;
    
    for (std::map<int, ClientSession>::iterator it = _active_sessions.begin(); it != _active_sessions.end(); ++it) {
        if (current_time - it->second.last_active > CONNECTION_TIMEOUT) {
            to_remove.push_back(it->first);
        }
    }
    
    if (!to_remove.empty()) {
        for (size_t i = 0; i < to_remove.size(); ++i) {
            removeClientSession(to_remove[i]);
        }
    }
}

/*
 * =============================================================================
 * STEP 1: LOAD SERVER CONFIGURATION
 * =============================================================================
 * This function loads the server configuration from file:
 * 1. Creates a configuration parser instance
 * 2. Parses the configuration file (webserver.conf)
 * 3. Loads server settings (host, port, routes, methods, etc.)
 * 4. Validates configuration is not empty
 * 
 * Flow: loadConfiguration() -> ConfigurationParser::parseConfigurationFile()
 * Next: initializeAllServerSockets() - create listening sockets
 * =============================================================================
 */
void WebServerEngine::loadConfiguration(const std::string& config_file) 
{
    ConfigurationParser parser;
    _server_configurations = parser.parseConfigurationFile(config_file);
    if (_server_configurations.empty())
        throw std::runtime_error("empty config: " + config_file);
}

ServerConfig* WebServerEngine::findMatchingConfiguration(const std::string& host, int port, const std::string& srv_name) 
{
    ServerConfig* default_config = NULL;
    
    for (size_t i = 0; i < _server_configurations.size(); ++i)
    {
        ServerConfig& config = _server_configurations[i];
        
        if (config.port == port)
        {
            if (!default_config)
                default_config = &config;

            if (config.host == host || 
                (config.host == "127.0.0.1" && host == "localhost") ||
                (config.host == "localhost" && host == "127.0.0.1"))
            {
                std::vector<std::string>::const_iterator name_it;
                for (name_it = config.server_names.begin();
                     name_it != config.server_names.end();
                     ++name_it)
                {
                    if (*name_it == srv_name)
                        return &config;
                }
                if (!default_config)
                    default_config = &config;
            }
        }
    }
    return default_config;
}

void WebServerEngine::performServerCleanup()
{
    for (size_t i = 0; i < _listening_sockets.size(); ++i)
    {
        if (_listening_sockets[i] != -1)
            close(_listening_sockets[i]);
    }
    _listening_sockets.clear();
    _socket_port_mapping.clear();
    
    for (std::map<int, ClientSession>::iterator it = _active_sessions.begin(); 
         it != _active_sessions.end(); ++it) {
        close(it->first);
    }
    _active_sessions.clear();   
    if (_event_monitor_fd != -1)
    {
        close(_event_monitor_fd);
        _event_monitor_fd = -1;
    }
}

void WebServerEngine::updateClientSessionActivity(int client_fd)
{
    std::map<int, ClientSession>::iterator it = _active_sessions.find(client_fd);
    if (it != _active_sessions.end())
        it->second.last_active = TimeMgr::getTime();
}

void WebServerEngine::initializeServerSocket(int port)
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
        throw std::runtime_error("socket() fail");
    
    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
        throw std::runtime_error("SO_REUSEADDR fail");

    #ifdef SO_REUSEPORT
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) == -1)
        throw std::runtime_error("SO_REUSEPORT fail");
    #endif
    
    if (setsockopt(server_socket, IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(opt)) == -1)
        throw std::runtime_error("Failed to set TCP_NODELAY option");
    
    int buffer_size = 2 * 1024 * 1024;
    if (setsockopt(server_socket, SOL_SOCKET, SO_SNDBUF, &buffer_size, sizeof(buffer_size)) < 0)
        throw std::runtime_error("Failed to set SO_SNDBUF option");
        
    if (setsockopt(server_socket, SOL_SOCKET, SO_RCVBUF, &buffer_size, sizeof(buffer_size)) < 0)
        throw std::runtime_error("Failed to set SO_RCVBUF option");

    int keepalive = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_KEEPALIVE, &keepalive, sizeof(keepalive)) < 0)
        throw std::runtime_error("Failed to set SO_KEEPALIVE option");
    
    
    struct linger so_linger;
    so_linger.l_onoff = 0;
    so_linger.l_linger = 0;
    if (setsockopt(server_socket, SOL_SOCKET, SO_LINGER, &so_linger, sizeof(so_linger)) < 0)
        std::cerr << "Warning: Failed to set SO_LINGER option" << std::endl;
    
    configureNonBlockingSocket(server_socket);
    
    struct sockaddr_in server_addr;
    my_memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
        throw std::runtime_error("bind() rejected");
        
    if (listen(server_socket, TCP_MAX_BACKLOG) == -1)
        throw std::runtime_error("Failed to listen on server socket");
    
    _listening_sockets.push_back(server_socket);
    _socket_port_mapping[server_socket] = port;
    
    
    if (!addToPolling(server_socket, EPOLLIN))
        throw std::runtime_error("Failed to add server socket to polling");
}

void WebServerEngine::removeClientSession(int client_fd)
{
    removeFromPolling(client_fd);
    
    std::map<int, ClientSession>::iterator client_it = _active_sessions.find(client_fd);
    if (client_it != _active_sessions.end()) {
        const std::string& client_ip = client_it->second.ip;
        
        std::map<std::string, int>::iterator ip_it = _ip_connection_counts.find(client_ip);
        if (ip_it != _ip_connection_counts.end()) {
            if (--ip_it->second <= 0) {
                _ip_connection_counts.erase(ip_it);
            }
        }
        
        _socket_port_mapping.erase(client_fd);
        _active_sessions.erase(client_it);
    }
    
    shutdown(client_fd, SHUT_RDWR);
    close(client_fd);
}

std::string WebServerEngine::buildJsonResponse(const std::map<std::string, std::string>& data) const
{
    return buildJSON(data);
}

std::string WebServerEngine::convertNumberToString(long long number) const
{
    return numToStr(number);
}

std::string WebServerEngine::getCurrentTimeString() const
{
    char buffer[26];
    TimeMgr::fmtTime(buffer, 26);
    return std::string(buffer);
}
