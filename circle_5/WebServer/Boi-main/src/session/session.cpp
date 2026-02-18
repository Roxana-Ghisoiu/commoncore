#include "session/session.hpp"
#include "utils/utils.hpp"

SessionMgr::SessionMgr()
{
	RandGen::setSeed(static_cast<unsigned long>(TimeMgr::getTime()));
}

SessionMgr::~SessionMgr()
{
	_sessions.clear();
}

std::string SessionMgr::genId() const
{
	const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string id;
	id.reserve(ID_LEN);
	for (size_t i = 0; i < ID_LEN; ++i)
	{
		id += chars[RandGen::gen() % chars.length()];
	}    
	return id;
}

bool SessionMgr::validId(const std::string& id) const
{
	if (id.length() != ID_LEN)
		return false;
	for (size_t i = 0; i < id.length(); ++i) {
		if (!my_isalnum(id[i])) {
			return false;
		}
	}
	return true;
}
void SessionMgr::cleanup()
{
	long current_time = TimeMgr::getTime();
	std::vector<std::string> expired;
	for (std::map<std::string, Session>::const_iterator it = _sessions.begin();
		 it != _sessions.end(); ++it) {
		if (current_time - it->second.last_access > TIMEOUT) {
			expired.push_back(it->first);
		}
	}	
	for (size_t i = 0; i < expired.size(); ++i) {
		_sessions.erase(expired[i]);
	}
}
std::string SessionMgr::create(const std::string& agent, const std::string& ip)
{
	cleanup();	
	std::string id = genId();
	Session s;
	s.id = id;
	s.created = TimeMgr::getTime();
	s.last_access = s.created;
	s.agent = agent;
	s.ip = ip;
	_sessions[id] = s;
	return id;
}
bool SessionMgr::validate(const std::string& id)
{
	if (!validId(id))
		return false;
	std::map<std::string, Session>::iterator it = _sessions.find(id);
	if (it == _sessions.end())
		return false;
	long current_time = TimeMgr::getTime();
	if (current_time - it->second.last_access > TIMEOUT) {
		_sessions.erase(it);
		return false;
	}
	return true;
}
void SessionMgr::updateAccess(const std::string& id)
{
	if (_sessions.find(id) != _sessions.end()) {
		_sessions[id].last_access = TimeMgr::getTime();
	}
}
void SessionMgr::destroy(const std::string& id)
{
	_sessions.erase(id);
}
void SessionMgr::setData(const std::string& id, 
								  const std::string& key, 
								  const std::string& val)
{
	if (_sessions.find(id) != _sessions.end()) {
		_sessions[id].data[key] = val;
	}
}
std::string SessionMgr::getData(const std::string& id,
										 const std::string& key) const
{
	std::map<std::string, Session>::const_iterator it = _sessions.find(id);
	if (it != _sessions.end()) {
		std::map<std::string, std::string>::const_iterator data_it = it->second.data.find(key);
		if (data_it != it->second.data.end()) {
			return data_it->second;
		}
	}
	return "";
}
std::string SessionMgr::genCookie(const std::string& id) const
{
	std::string cookie = "sessionid=";
	cookie += id;
	cookie += "; Path=/";
	char time_buffer[80];
	TimeMgr::fmtTime(time_buffer, sizeof(time_buffer));
	cookie += "; Expires=";
	cookie += time_buffer;
	cookie += "; HttpOnly; SameSite=Strict";
	return cookie;
}
std::string SessionMgr::parseCookie(const std::string& hdr) const
{
	size_t pos = hdr.find("sessionid=");
	if (pos == std::string::npos)
		return "";	
	pos += 10;
	size_t end = hdr.find(';', pos);
	if (end == std::string::npos)
		end = hdr.length();
	std::string id = hdr.substr(pos, end - pos);
	return validId(id) ? id : "";
}
