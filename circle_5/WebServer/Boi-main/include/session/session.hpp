#ifndef USER_SESSION_HPP
# define USER_SESSION_HPP

#include <string>
#include <map>
#include <ctime>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>

struct Session {
	std::string id;
	std::map<std::string, std::string> data;
	time_t created;
	time_t last_access;
	std::string agent;
	std::string ip;
};

class SessionMgr
{
	private:
		std::map<std::string, Session> _sessions;
		static const time_t TIMEOUT = 1800;
		static const size_t ID_LEN = 32;
		std::string genId() const;
		bool validId(const std::string& id) const;

	public:
		SessionMgr();
		~SessionMgr();
		std::string create(const std::string& agent, const std::string& ip);
		bool validate(const std::string& id);
		void updateAccess(const std::string& id);
		void destroy(const std::string& id);
		void setData(const std::string& id, const std::string& key, const std::string& val);
		std::string getData(const std::string& id, const std::string& key) const;
		std::string genCookie(const std::string& id) const;
		std::string parseCookie(const std::string& hdr) const;
		void cleanup();
};

#endif
