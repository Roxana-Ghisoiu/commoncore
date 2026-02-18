#ifndef HTTP_RESPONSE_MANAGER_HPP
#define HTTP_RESPONSE_MANAGER_HPP

#include <string>
#include <map>
#include <sstream>
#include "core/client.hpp"

struct ResponseStatusInfo {
    int status_code;
    std::string status_text;
    std::string description;
};

namespace HttpStatusManager {
    const int SUCCESS_OK = 200;
    const int RESOURCE_CREATED = 201;
    const int NO_CONTENT_RESPONSE = 204;
    const int NOT_MODIFIED_RESOURCE = 304;
    const int MALFORMED_REQUEST = 400;
    const int AUTHENTICATION_REQUIRED = 401;
    const int ACCESS_FORBIDDEN = 403;
    const int RESOURCE_NOT_FOUND = 404;
    const int METHOD_NOT_SUPPORTED = 405;
    const int RATE_LIMIT_EXCEEDED = 429;
    const int PAYLOAD_TOO_LARGE_REQUEST = 413;
    const int INTERNAL_SERVER_ERROR_OCCURRED = 500;
    const int FEATURE_NOT_IMPLEMENTED = 501;
    const int SERVICE_TEMPORARILY_UNAVAILABLE = 503;
    const int PERMANENT_REDIRECT = 301;
    
    const ResponseStatusInfo& getStatusByCode(int response_code);
    int parseStatusCodeFromMessage(const std::string& error_message);
    std::string getStatusText(int response_code);
}

namespace HttpProtocol {
    static const char* CARRIAGE_RETURN_LINE_FEED = "\r\n";
    static const char* HEADER_END_MARKER = "\r\n\r\n";
}

class HttpResponseBuilder
{
	private:
		std::ostringstream output_stream;
		std::map<std::string, std::string> response_headers;
		std::string response_body;
		int status_code;
		std::string status_text;
		bool headers_written;
		
	public:
		HttpResponseBuilder(int response_code = 200);
		HttpResponseBuilder& setStatusCode(int response_code);
		HttpResponseBuilder& addResponseHeader(const std::string& header_name, const std::string& header_value);
		HttpResponseBuilder& setContentType(const std::string& content_type);
		HttpResponseBuilder& setResponseBody(const std::string& body_content);
		HttpResponseBuilder& addCommonHeaders(bool keep_connection_alive = false);
		void writeResponseHeaders();
		std::string buildCompleteResponse();
		void applyToClient(ClientSession& client_session);
};

typedef ResponseStatusInfo StatusInfo;
typedef HttpResponseBuilder RespBuilder;

namespace HttpStatus = HttpStatusManager;

#endif
