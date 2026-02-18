#include "config/configParser.hpp"
#include "utils/utils.hpp"

static std::string cleanToken(const std::string& tok)
{
	std::string clean = tok;
	if (!clean.empty() && clean[clean.length() - 1] == ';') {
		clean = clean.substr(0, clean.length() - 1);
	}
	size_t start = clean.find_first_not_of(" \t");
	if (start == std::string::npos) return "";
	size_t end = clean.find_last_not_of(" \t");
	return clean.substr(start, (end - start + 1));
}
static bool validMethod(const std::string& m)
{
	return m == "GET" || m == "POST" || m == "DELETE" || m == "PUT";
}
static void parseMethods(size_t& idx, const std::vector<std::string>& toks, Route& r)
{
	++idx;
	while (idx < toks.size() && toks[idx] != "root" && toks[idx] != "upload_dir" && 
		   toks[idx] != "default_file" && toks[idx] != "cgi_handler")
	{
		std::string m = cleanToken(toks[idx]);
		if (!m.empty()) {
			if (validMethod(m)) {
				r.allowed_methods.insert(m);
			} else {
				std::cerr << "Invalid method: " << m << std::endl;
			}
		}
		++idx;
	}
}
static void parseDirective(const std::string& directive, size_t& idx, 
						   const std::vector<std::string>& toks, 
						   std::string& target)
{
	if (idx + 1 < toks.size()) {
		std::string val = cleanToken(toks[++idx]);
		if (!val.empty()) {
			target = val;
				} else {
			std::cerr << directive << " value empty" << std::endl;
				}
		++idx;
			} else {
		std::cerr << directive << " needs value" << std::endl;
		++idx;
	}
}
static void parseBodySize(size_t& idx, const std::vector<std::string>& toks, size_t& size_val)
{
	if (idx + 1 < toks.size()) {
		std::string val = cleanToken(toks[++idx]);
		size_val = my_atoi(val.c_str());
		++idx;
				} else {
		std::cerr << "Body size requires value" << std::endl;
		++idx;
	}
}
static void parseDirListing(size_t& idx, const std::vector<std::string>& toks, bool& listing)
{
	if (idx + 1 < toks.size()) {
		std::string val = cleanToken(toks[++idx]);
		listing = (val == "on");
		if (val != "on" && val != "off") {
			std::cerr << "Invalid listing value: " << val << std::endl;
		}
		++idx;
				} else {
		std::cerr << "Listing requires on/off" << std::endl;
		listing = false;
		++idx;
	}
}
void ConfigurationParser::parseRouteConfiguration(const std::vector<std::string>& tokens, ServerConfig& server)
{
	Route r;
	r.path = tokens[1];
	r.client_max_body_size = server.client_max_body_size;
	size_t i = 2;
	while (i < tokens.size())
	{
		std::string tok = tokens[i];
		if (tok == "methods") {
			parseMethods(i, tokens, r);
		}
		else if (tok == "root") {
			parseDirective("root", i, tokens, r.root_directory);
		}
		else if (tok == "upload_dir") {
			parseDirective("upload_dir", i, tokens, r.upload_directory);
		}
		else if (tok == "default_file") {
			parseDirective("default_file", i, tokens, r.default_file);
		}
		else if (tok == "cgi_handler") {
			parseDirective("cgi_handler", i, tokens, r.cgi_handler);
		}
		else if (tok == "directory_listing") {
			parseDirListing(i, tokens, r.directory_listing);
		}
		else if (tok == "client_max_body_size") {
			parseBodySize(i, tokens, r.client_max_body_size);
		}
		else {
			std::cerr << "Unknown token: " << tok << std::endl;
			++i;
		}
	}
	if (r.root_directory.empty()) {
		r.root_directory = ".";
		std::cout << "Route " << r.path << " using current dir" << std::endl;
	}
	if (r.allowed_methods.empty()) {
		r.allowed_methods.insert("GET");
		std::cout << "Route " << r.path << " defaults to GET" << std::endl;
	}
	server.routes.push_back(r);
}
static void handleServerDirective(const std::vector<std::string>& toks, ServerConfig& srv)
{
	if (toks.empty()) return;
	if (toks[0] == "host" && toks.size() > 1) {
		srv.host = toks[1];
	}
	else if (toks[0] == "port" && toks.size() > 1) {
		srv.port = my_atoi(toks[1].c_str());
	}
	else if (toks[0] == "server_name") {
		for (size_t i = 1; i < toks.size(); ++i) {
			std::string name = cleanToken(toks[i]);
			if (!name.empty()) {
				srv.server_names.push_back(name);
			}
		}
	}
	else if (toks[0] == "error_page" && toks.size() > 2) {
		int code = my_atoi(toks[1].c_str());
		std::string path = cleanToken(toks[2]);
		srv.error_pages[code] = path;
	}
	else if (toks[0] == "client_max_body_size" && toks.size() > 1) {
		std::string val = cleanToken(toks[1]);
		srv.client_max_body_size = my_atoi(val.c_str());
	}
	else if (toks[0] == "route") {
	}
	else {
		std::cerr << "Unknown directive: " << toks[0] << std::endl;
	}
}
static std::vector<std::string> tokenizeLine(const std::string& line)
{
	std::istringstream iss(line);
	std::vector<std::string> toks;
	std::string tok;
	while (iss >> tok) {
		toks.push_back(tok);
	}
	return toks;
}
std::vector<ServerConfig> ConfigurationParser::parseConfigurationFile(const std::string& filename) 
{
	std::vector<ServerConfig> servers;
	std::ifstream file(filename.c_str());
	if (!file.is_open()) {
		throw std::runtime_error("Config file not found: " + filename);
	}
	ServerConfig srv;
	std::string line;
	bool in_srv = false;
	bool in_rte = false;
	std::vector<std::string> rte_toks;
	while (std::getline(file, line))
	{
		line = cleanToken(line);
		if (line.empty() || line[0] == '#') continue;
		if (line == "server {") {
			in_srv = true;
			srv = ServerConfig();
		}
		else if (line == "}") {
			if (in_rte) {
				in_rte = false;
				parseRouteConfiguration(rte_toks, srv);
				rte_toks.clear();
			}
			else if (in_srv) {
				in_srv = false;
				servers.push_back(srv);
			}
		}
		else if (in_srv) {
			std::vector<std::string> toks = tokenizeLine(line);
			if (!toks.empty())
			{
				if (toks[0] == "route" && toks.size() > 1)
				{
					if (toks[toks.size() - 1] == "{")
					{
						in_rte = true;
						rte_toks = toks;
						rte_toks.pop_back();
					} else {
						parseRouteConfiguration(toks, srv);
					}
				}
				else if (in_rte) {
					for (size_t i = 0; i < toks.size(); ++i) {
						rte_toks.push_back(toks[i]);
					}
				}
				else {
					handleServerDirective(toks, srv);
				}
			}
		}
	}
	if (in_srv || in_rte) {
		throw std::runtime_error("Config block not closed");
	}
	return servers;
}
std::string ConfigurationParser::trimString(const std::string& str)
{
	return cleanToken(str);
}
bool ConfigurationParser::isValidHttpMethod(const std::string& method)
{
	return validMethod(method);
}
void ConfigurationParser::parseConfigurationLine(const std::vector<std::string>& tokens, ServerConfig& current_server)
{
	handleServerDirective(tokens, current_server);
}
