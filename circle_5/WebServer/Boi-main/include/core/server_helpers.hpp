#ifndef SERVER_HELPERS_HPP
#define SERVER_HELPERS_HPP

#include <string>
#include <map>
#include <sstream>

std::string trimWS(const std::string& s);
std::string numToStr(long long n);
std::string buildJSON(const std::map<std::string, std::string>& data);
std::string getContentType(const std::string& path);
std::string extractBody(const std::string& buf);

#endif

