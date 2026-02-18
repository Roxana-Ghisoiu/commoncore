#include "http/httpResponseManager.hpp"
#include <cstdlib>
#include "utils/utils.hpp"

const ResponseStatusInfo& HttpStatusManager::getStatusByCode(int response_code) 
{
    static std::map<int, ResponseStatusInfo> response_codes_registry;
    
    if (response_codes_registry.empty()) 
    {
        ResponseStatusInfo success_response;
        success_response.status_code = SUCCESS_OK;
        success_response.status_text = "OK";
        success_response.description = "Request succeeded";
        response_codes_registry[SUCCESS_OK] = success_response;
        ResponseStatusInfo resource_created;
        resource_created.status_code = RESOURCE_CREATED;
        resource_created.status_text = "Created";
        resource_created.description = "Resource created successfully";
        response_codes_registry[RESOURCE_CREATED] = resource_created;
        ResponseStatusInfo empty_response;
        empty_response.status_code = NO_CONTENT_RESPONSE;
        empty_response.status_text = "No Content";
        empty_response.description = "Request succeeded with no content";
        response_codes_registry[NO_CONTENT_RESPONSE] = empty_response;
        ResponseStatusInfo unchanged_resource;
        unchanged_resource.status_code = NOT_MODIFIED_RESOURCE;
        unchanged_resource.status_text = "Not Modified";
        unchanged_resource.description = "Resource not modified";
        response_codes_registry[NOT_MODIFIED_RESOURCE] = unchanged_resource;
        ResponseStatusInfo malformed_request;
        malformed_request.status_code = MALFORMED_REQUEST;
        malformed_request.status_text = "Bad Request";
        malformed_request.description = "Invalid request syntax";
        response_codes_registry[MALFORMED_REQUEST] = malformed_request;
        ResponseStatusInfo auth_required;
        auth_required.status_code = AUTHENTICATION_REQUIRED;
        auth_required.status_text = "Unauthorized";
        auth_required.description = "Authentication required";
        response_codes_registry[AUTHENTICATION_REQUIRED] = auth_required;
        ResponseStatusInfo access_denied;
        access_denied.status_code = ACCESS_FORBIDDEN;
        access_denied.status_text = "Forbidden";
        access_denied.description = "Access not allowed";
        response_codes_registry[ACCESS_FORBIDDEN] = access_denied;
        ResponseStatusInfo missing_resource;
        missing_resource.status_code = RESOURCE_NOT_FOUND;
        missing_resource.status_text = "Not Found";
        missing_resource.description = "Resource does not exist";
        response_codes_registry[RESOURCE_NOT_FOUND] = missing_resource;
        ResponseStatusInfo unsupported_method;
        unsupported_method.status_code = METHOD_NOT_SUPPORTED;
        unsupported_method.status_text = "Method Not Allowed";
        unsupported_method.description = "Method not supported";
        response_codes_registry[METHOD_NOT_SUPPORTED] = unsupported_method;
        ResponseStatusInfo rate_limit_exceeded;
        rate_limit_exceeded.status_code = RATE_LIMIT_EXCEEDED;
        rate_limit_exceeded.status_text = "Too Many Requests";
        rate_limit_exceeded.description = "Rate limit exceeded";
        response_codes_registry[RATE_LIMIT_EXCEEDED] = rate_limit_exceeded;
        ResponseStatusInfo oversized_payload;
        oversized_payload.status_code = PAYLOAD_TOO_LARGE_REQUEST;
        oversized_payload.status_text = "Payload Too Large";
        oversized_payload.description = "Request entity too large";
        response_codes_registry[PAYLOAD_TOO_LARGE_REQUEST] = oversized_payload;
        ResponseStatusInfo server_malfunction;
        server_malfunction.status_code = INTERNAL_SERVER_ERROR_OCCURRED;
        server_malfunction.status_text = "Internal Server Error";
        server_malfunction.description = "Server encountered an error";
        response_codes_registry[INTERNAL_SERVER_ERROR_OCCURRED] = server_malfunction;
        ResponseStatusInfo feature_unavailable;
        feature_unavailable.status_code = FEATURE_NOT_IMPLEMENTED;
        feature_unavailable.status_text = "Not Implemented";
        feature_unavailable.description = "Functionality not implemented";
        response_codes_registry[FEATURE_NOT_IMPLEMENTED] = feature_unavailable;
        ResponseStatusInfo service_down;
        service_down.status_code = SERVICE_TEMPORARILY_UNAVAILABLE;
        service_down.status_text = "Service Unavailable";
        service_down.description = "Service temporarily unavailable";
        response_codes_registry[SERVICE_TEMPORARILY_UNAVAILABLE] = service_down;
    }
    
    std::map<int, ResponseStatusInfo>::iterator registry_entry = response_codes_registry.find(response_code);
    if (registry_entry != response_codes_registry.end()) 
    {
        return registry_entry->second;
    }
    return response_codes_registry[INTERNAL_SERVER_ERROR_OCCURRED];
}

int HttpStatusManager::parseStatusCodeFromMessage(const std::string& status_message) 
{
    size_t digit_position = status_message.find_first_of("0123456789");
    if (digit_position != std::string::npos) 
    {
        std::string numeric_code;
        while (digit_position < status_message.size() && my_isdigit(status_message[digit_position])) 
        {
            numeric_code += status_message[digit_position++];
        }
        
        if (numeric_code.size() == 3) 
        {
            return my_atoi(numeric_code.c_str());
        }
    }
    if (status_message.find("not found") != std::string::npos ||
        status_message.find("404") != std::string::npos) 
    {
        return RESOURCE_NOT_FOUND;
    }
    else if (status_message.find("forbidden") != std::string::npos ||
             status_message.find("403") != std::string::npos) 
    {
        return ACCESS_FORBIDDEN;
    }
    else if (status_message.find("bad request") != std::string::npos ||
             status_message.find("400") != std::string::npos) 
    {
        return MALFORMED_REQUEST;
    }
    else if (status_message.find("method not allowed") != std::string::npos ||
             status_message.find("405") != std::string::npos) 
    {
        return METHOD_NOT_SUPPORTED;
    }
    else if (status_message.find("too large") != std::string::npos ||
             status_message.find("413") != std::string::npos) 
    {
        return PAYLOAD_TOO_LARGE_REQUEST;
    }
    else if (status_message.find("not implemented") != std::string::npos ||
             status_message.find("501") != std::string::npos) 
    {
        return FEATURE_NOT_IMPLEMENTED;
    }
    else if (status_message.find("too many") != std::string::npos ||
             status_message.find("429") != std::string::npos) 
    {
        return RATE_LIMIT_EXCEEDED;
    }
    return INTERNAL_SERVER_ERROR_OCCURRED;
}

std::string HttpStatusManager::getStatusText(int response_code) 
{
    return getStatusByCode(response_code).status_text;
}

HttpResponseBuilder::HttpResponseBuilder(int response_code) : 
    status_code(response_code), 
    headers_written(false)
{
    status_text = HttpStatusManager::getStatusText(response_code);
}

HttpResponseBuilder& HttpResponseBuilder::setStatusCode(int response_code)
{
    status_code = response_code;
    status_text = HttpStatusManager::getStatusText(response_code);
    return *this;
}

HttpResponseBuilder& HttpResponseBuilder::addResponseHeader(const std::string& header_name, const std::string& header_value)
{
    response_headers[header_name] = header_value;
    return *this;
}

HttpResponseBuilder& HttpResponseBuilder::setContentType(const std::string& content_type)
{
    return addResponseHeader("Content-Type", content_type);
}
HttpResponseBuilder& HttpResponseBuilder::setResponseBody(const std::string& body_content)
{
    response_body = body_content;
    std::ostringstream content_length_stream;
    content_length_stream << response_body.length();
    addResponseHeader("Content-Length", content_length_stream.str());
    return *this;
}
HttpResponseBuilder& HttpResponseBuilder::addCommonHeaders(bool keep_connection_alive)
{
    addResponseHeader("Connection", keep_connection_alive ? "keep-alive" : "close");
    addResponseHeader("Server", "webserver");
    return *this;
}
void HttpResponseBuilder::writeResponseHeaders()
{
    if (headers_written) 
    {
        return;
    }    
    output_stream << "HTTP/1.1 " << status_code << " " << status_text << "\r\n";
    for (std::map<std::string, std::string>::const_iterator header_iterator = response_headers.begin();
         header_iterator != response_headers.end(); ++header_iterator) 
    {
        output_stream << header_iterator->first << ": " << header_iterator->second << "\r\n";
    }
    output_stream << "\r\n";
    headers_written = true;
}

std::string HttpResponseBuilder::buildCompleteResponse()
{
    writeResponseHeaders();
    output_stream << response_body;
    return output_stream.str();
}
void HttpResponseBuilder::applyToClient(ClientSession& client_session)
{
    client_session.resp_data = buildCompleteResponse();
    client_session.resp_ready = true;
}
