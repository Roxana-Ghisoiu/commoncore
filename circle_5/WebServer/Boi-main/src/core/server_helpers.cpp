#include "core/server_helpers.hpp"

std::string trimWS(const std::string& s)
{
	size_t start = s.find_first_not_of(" \t\r\n");
	if (start == std::string::npos) return "";
	size_t end = s.find_last_not_of(" \t\r\n");
	return s.substr(start, (end - start + 1));
}
std::string numToStr(long long n)
{
	std::ostringstream ss;
	ss << n;
	return ss.str();
}
std::string buildJSON(const std::map<std::string, std::string>& data)
{
	std::ostringstream j;
	j << "{";
	bool first = true;
	for (std::map<std::string, std::string>::const_iterator it = data.begin(); it != data.end(); ++it)
	{
		if (!first) j << ",";
		else first = false;
		j << "\"" << it->first << "\":\"" << it->second << "\"";
	}
	j << "}";
	return j.str();
}
std::string getContentType(const std::string& path)
{
	std::string ext = path.substr(path.find_last_of('.') + 1);
	if (ext == "html" || ext == "htm") return "text/html";
	if (ext == "css") return "text/css";
	if (ext == "js") return "application/javascript";
	if (ext == "jpg" || ext == "jpeg") return "image/jpeg";
	if (ext == "png") return "image/png";
	if (ext == "gif") return "image/gif";
	return "text/plain";
}
std::string extractBody(const std::string& buf)
{
	size_t pos = buf.find("\r\n\r\n");
	if (pos == std::string::npos) return "";
	return buf.substr(pos + 4);
}
