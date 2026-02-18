#ifndef CONFIGURATION_PARSER_HPP
# define CONFIGURATION_PARSER_HPP
# include <string>
# include <vector>
# include <map>
# include <set>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <iostream>
#include <algorithm>

struct Route {
	std::string path;
	std::set<std::string> allowed_methods;
	std::set<std::string> allowed_content_types;
	std::string root_directory;
	std::string redirect_url;
	bool directory_listing;
	std::string default_file;
	std::string cgi_extension;
	std::string upload_directory;
	std::string cgi_handler;
	std::string cgi_path;
	bool allow_empty_post;
	size_t client_max_body_size;
	
	Route() : directory_listing(false), allow_empty_post(true), client_max_body_size(0) {
		 allowed_content_types.insert("application/x-www-form-urlencoded");
		 allowed_content_types.insert("multipart/form-data");
		 allowed_content_types.insert("application/json");
	}
};

struct ServerConfig {
	std::string host;
	int port;
	std::vector<std::string> server_names;
	std::map<int, std::string> error_pages;
	size_t client_max_body_size;
	std::vector<Route> routes;
	
	ServerConfig() : port(8080), client_max_body_size(1024 * 1024) {}
};

class ConfigurationParser {
	private:
		std::string trimString(const std::string& str);
		void parseRouteConfiguration(const std::vector<std::string>& tokens, ServerConfig& server);
		bool isValidHttpMethod(const std::string& method);

	public:
		std::vector<ServerConfig> parseConfigurationFile(const std::string& filename);
		void parseConfigurationLine(const std::vector<std::string>& tokens, ServerConfig& current_server) ;
};

#endif