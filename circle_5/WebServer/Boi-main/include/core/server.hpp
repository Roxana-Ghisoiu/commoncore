#ifndef WEBSERVER_ENGINE_HPP
# define WEBSERVER_ENGINE_HPP

#include <sys/epoll.h>

#include <iterator>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <map>
#include <vector>
#include <list>
#include <string>
#include <ctime>
#include <sys/time.h>
#include <netinet/tcp.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <iostream>
#include <arpa/inet.h>
#include <signal.h>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <dirent.h>
#include <algorithm>
#include <sys/wait.h>
#include <sstream>
#include "cgi/CGIHandler.hpp"
#include "core/client.hpp"
#include "session/session.hpp"
#include "config/configParser.hpp"
#include "http/httpResponseManager.hpp"
#include "utils/utils.hpp"
#define MAX_CONNECTIONS 4096
#define MAX_CONNECTIONS_PER_IP 1000
#define CONNECTION_TIMEOUT 1000000
#define MAX_EVENTS 10240
#define CHUNK_SIZE 16384
#define TCP_MAX_BACKLOG 1024
#define CONNECTION_POOL_SIZE 1024
#define MAX_REQUEST_SIZE (200 * 1024 * 1024)
#define SOCKET_SEND_BUFFER (512 * 1024)
#define SOCKET_RECV_BUFFER (512 * 1024)
#define MAX_REQUESTS_PER_SECOND 10000
#define CLEANUP_INTERVAL 5


class HttpResponse
{
    public:
        typedef std::vector<unsigned char> data_chunks_type;
        enum TransferMode { tStandard, tChunked } transfer_mode;
        std::map<std::string, std::string> response_headers;
        std::list<data_chunks_type> data_chunks;
        std::size_t response_content_length;
        bool response_status;
        std::string file_mounted_path;
        std::pair<std::string, std::string>* location_path;
        std::string http_status_code;
        std::string http_status_message;

        HttpResponse() : transfer_mode(tStandard), response_content_length(0), response_status(false), location_path(NULL) {}
};

class CGIException : public std::exception
{
    public:
        CGIException(HttpResponse& response, const std::string& message) 
            : _http_response(response), _error_message(message) {}
        
        virtual ~CGIException() throw() {}
        
        virtual const char* what() const throw() {
            return _error_message.c_str();
        }
        
        HttpResponse& _http_response;
        std::string _error_message;
};

class EventMonitor
{
    public:
        EventMonitor() : _file_descriptors() {}
        
        void clearAll() 
        { 
            _file_descriptors.clear();
        }

        void addFileDescriptor(int fd, short events)
        {
            struct pollfd poll_fd;
            poll_fd.fd = fd;
            poll_fd.events = events;
            poll_fd.revents = 0;
            _file_descriptors.push_back(poll_fd);
        }

        int waitForEvents(int timeout)
        {
            return ::poll(&_file_descriptors[0], _file_descriptors.size(), timeout);
        }

        bool isFileDescriptorReady(int fd) const
        {
            for (std::vector<struct pollfd>::const_iterator it = _file_descriptors.begin(); 
                it != _file_descriptors.end(); ++it) {
                if (it->fd == fd && (it->revents & it->events)) {
                    return true;
                }
            }
            return false;
        }

    private:
        std::vector<struct pollfd> _file_descriptors;
};

struct HttpRequest
{
    typedef std::vector<unsigned char> data_chunks_type;
    typedef unsigned char data_byte_type;
    std::string http_method;
    std::size_t request_content_length;
    enum TransferState { tStandard, tChunked } transfer_state;
    std::list<data_chunks_type> data_chunks;
    std::map<std::string, std::string> request_headers;
    static const std::string newline;
    static const std::string end_of_file;
    
    HttpRequest() : request_content_length(0), transfer_state(tStandard) {}
    
    std::size_t getRequestContentLength() const {
        if (transfer_state == tChunked) {
            return 0;
        }
        return request_content_length;
    }
    
    data_byte_type* parseChunkSize(data_byte_type* message_start, data_byte_type* message_end) {
        data_byte_type* separator = std::search(message_start, message_end, newline.begin(), newline.end());
        data_byte_type* boundary = separator;

        if (separator == message_start) {
            separator = std::search(message_start + newline.size(), message_end, newline.begin(), newline.end());
        }
        separator += static_cast<size_t>(message_end - separator) > newline.size() ? newline.size() : message_end - separator;
        _chunk_tail.append(message_start, separator);
        message_start = separator;
        if (_chunk_tail.substr(0, end_of_file.size()) == end_of_file) {
            request_content_length = 0;
            transfer_state = tStandard;
            _chunk_tail.clear();
            return message_start;
        }
        if (boundary == message_end) {
            return message_start;
        }
        request_content_length = my_strtoul(_chunk_tail.c_str(), NULL, 16);
        _chunk_tail.clear();
        if (!request_content_length) {
            return parseChunkSize(boundary, message_end);
        }
        return message_start;
    }
    
    private:
        std::string _chunk_tail;
};

class WebServerEngine
{
	private:
		std::vector<int> _listening_sockets;
		std::map<int, int> _socket_port_mapping;
	int _event_monitor_fd;
		std::map<int, ClientSession> _active_sessions;
		std::map<std::string, int> _ip_connection_counts;
		std::string _configuration_file_path;
		static bool _server_running;
		SessionMgr _user_session_manager;
		std::vector<ServerConfig> _server_configurations;
		std::map<std::string, time_t> _file_upload_timestamps;
		static const size_t MAX_UPLOADS_PER_MINUTE = 10;
		static const size_t MAX_UPLOAD_SIZE = 10 * 1024 * 1024;
		ServerConfig* findMatchingConfiguration(const std::string& host, int port, const std::string& server_name);
		void initializeServerSocket(int port);		
		void configureNonBlockingSocket(int socket);
		void updateClientSessionActivity(int client_fd);
		void cleanupInactiveClientSessions();
		void handleClientError(int client_fd, const std::string& status, const std::string& message = "");
		void configureSignalHandlers();
		void performServerCleanup();
		void updateServerStatistics();
		bool validateRateLimit(const std::string& ip);
		std::string buildJsonResponse(const std::map<std::string, std::string>& data) const;
		std::vector<ClientSession> _connection_pool;
		std::map<std::string, size_t> _request_counters;
		std::map<std::string, time_t> _request_timestamps;
		time_t _last_cleanup_time;
		time_t _last_rate_limit_cleanup_time;
		unsigned long _total_request_count;
		unsigned long _total_error_count;
		unsigned long _requests_per_second_count;
		time_t _last_rps_update_time;
		
		void configureClientSocket(int client_fd);
		ClientSession createNewClientSession(int client_fd, const std::string& client_ip);
		bool acceptAndRegisterClient(int server_socket, int client_fd, const std::string& client_ip);
		
		void parseRequestLine(ClientSession& client, const std::string& line);
		void parseHostHeader(ClientSession& client, const std::string& header_value);
		void parseHeaderLine(ClientSession& client, const std::string& line);
		void initializeClientSession(ClientSession& client);
		
		std::string executeCGIScript(ClientSession& client, CGIProcessor& cgi);
		void processCGIHeaders(const std::string& cgi_headers, std::string& response_headers, bool& has_content_type);
		void buildCGIResponse(ClientSession& client, const std::string& cgi_output);
		
		bool readClientData(int client_fd, ClientSession& client);
		Route* findAlternativeRoute(ServerConfig* config, ClientSession& client, Route* current_route);
		bool handleMethodNotAllowed(ClientSession& client);
		void dispatchRequestByMethod(ClientSession& client);
		bool processCompleteRequest(ClientSession& client, int client_fd);
		size_t calculateChunkSize(const ClientSession& client);
		bool handleSendError(int client_fd, int error_code);
		void resetClientForNextRequest(ClientSession& client);
		
		void performPeriodicMaintenance(long& last_cleanup, long& last_stats);
		int waitForEvents(void* events);
		void extractEventData(void* events, int index, int& fd, uint32_t& event_flags);
		bool isListeningSocket(int fd);
		void handleClientEvent(int fd, uint32_t event_flags);
		void processEvents(void* events, int nfds);
		
		bool loadCustomErrorPage(const std::string& error_page_path, std::string& file_content);
		void buildErrorResponse(ClientSession& client, const std::string& status, const std::string& content, const std::string& content_type);
		bool tryCustomErrorPage(ClientSession& client, const std::string& status, int status_code, ServerConfig* config);
		bool handleChunkReadHeaders(ClientSession& client, const std::string& body_data, size_t& pos);
		bool handleChunkReadSize(ClientSession& client, const std::string& body_data, size_t& pos);
		bool handleChunkReadData(ClientSession& client, const std::string& body_data, size_t& pos);
		bool handleChunkReadEnd(ClientSession& client, const std::string& body_data, size_t& pos);
		void replaceChunkHeadersWithContentLength(ClientSession& client);
		bool handleChunkReadTrailer(ClientSession& client, const std::string& body_data, size_t& pos);
		std::vector<std::string> readDirectoryEntries(const std::string& dir_path);
		std::string buildDirectoryListingHTML(ClientSession& client, const std::string& dir_path, const std::vector<std::string>& entries);

	public:
		WebServerEngine();
		~WebServerEngine();
		void startServer();
		void shutdownServer();
		void processNewConnection(int server_socket);
		void processClientWrite(int client_fd);
		void removeClientSession(int client_fd);
		void parseHttpRequest(ClientSession &client);
		static void signalHandler(int signum);
		void loadConfiguration(const std::string& config_file);
		void initializeAllServerSockets();
		bool isDirectScript(const std::string& req_path, Route* route);
		bool handlePOSTChunked(ClientSession& client);
		size_t calcBodySize(ClientSession& client);
		void fixChunkedHeaders(ClientSession& client);
		void processPostRequest(ClientSession& client);
		std::string resolveFilePath(const std::string& req_path, Route* route, int client_fd);
		void processGetRequest(ClientSession& client);
		std::string determineContentType(const std::string& path) const;
		void sendErrorResponse(ClientSession& client, int status_code, const std::string& message);
		void sendDirectoryListing(ClientSession& client, const std::string& dir_path);
		Route* findMatchingRoute(const std::string& path, ServerConfig* config) const;
		std::string resolveCGIPath(const std::string& req_path, Route* route);
	bool validateCGIScript(const std::string& path, int client_fd);
	std::map<std::string, std::string> buildCGIEnv(ClientSession& client, Route* route, const std::string& script_path);
	void addPOSTEnvVars(ClientSession& client, std::map<std::string, std::string>& env);
	void addHTTPHeaders(ClientSession& client, std::map<std::string, std::string>& env);
	void executeCGI(ClientSession& client, Route* route);
		std::string convertNumberToString(long long number) const;
		std::string convertToString(size_t value) const;
		void debugPrintRequest(const ClientSession& client) const;
		void addCookieHeaderIfNeeded(std::ostringstream& response, ClientSession& client, bool is_empty_post_to_root);
		std::string getCurrentTimeString() const;
		void processNotImplemented(ClientSession& client);
		bool isMethodAllowed(Route* route, const std::string& method) const;
		void processPutRequest(ClientSession& client);
		void modifyEpollEvent(int fd, uint32_t events);
		void processDeleteRequest(ClientSession& client);
		std::string processChunkedTransfer(const std::string& chunkData) const;
		bool processChunkedTransfer(ClientSession& client);
		bool processChunkedBody(ClientSession& client, const std::string& data);
		void logRequestDebug(const ClientSession& client, const std::string& functionName) const;
		void handleClientData(int client_fd);
		bool ensureDirectoryExists(const std::string& dir_path);
		std::string extractRequestBody(ClientSession& client) const;
		bool saveUploadedFile(const std::string& upload_dir, const std::string& filename, const std::string& body);
		bool processIncomingChunkedData(ClientSession& client);
		bool processChunkedData(ClientSession& client);
		void processPostChunkedCGI(ClientSession &client, Route* route);
		bool processChunkedUpload(ClientSession& client);
		bool handleChunkedRequest(ClientSession &client, Route* route);
		void processChunkedPostRequest(ClientSession& client, Route* route);
		bool addToPolling(int fd, uint32_t events);
    	bool removeFromPolling(int fd);
        std::string trimString(const std::string& str) const;
        void initializeConnectionPool();
		void cleanupRateLimits();
		unsigned long getTotalRequestCount() const { return _total_request_count; }
		unsigned long getTotalErrorCount() const { return _total_error_count; }
		unsigned long getRequestsPerSecondCount() const { return _requests_per_second_count; }
		void updateRequestCounts();
};

#endif
