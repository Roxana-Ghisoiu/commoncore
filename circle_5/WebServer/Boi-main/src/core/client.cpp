#include "core/client.hpp"
#include "utils/utils.hpp"

static std::string trimWS(const std::string& s)
{
	size_t st = 0, en = s.length();
	while (st < en && (s[st] == ' ' || s[st] == '\t')) st++;
	while (en > st && (s[en-1] == ' ' || s[en-1] == '\t')) en--;
	return s.substr(st, en - st);
}
static void extractCookies(const std::string& hdr, std::map<std::string, std::string>& ck, std::string& sid)
{
	size_t p = 0;
	while (p < hdr.length()) {
		size_t end = hdr.find(";", p);
		if (end == std::string::npos) end = hdr.length();
		std::string item = hdr.substr(p, end - p);
		size_t eq = item.find("=");
		if (eq != std::string::npos) {
			std::string k = trimWS(item.substr(0, eq));
			std::string v = item.substr(eq + 1);
			ck[k] = v;
			if (k == "user_session_id") sid = v;
		}
		p = end + 1;
		while (p < hdr.length() && (hdr[p] == ' ' || hdr[p] == '\t')) p++;
	}
}
static bool parseReqLine(const std::string& line, std::string& mth, std::string& path)
{
	size_t sp1 = line.find(" ");
	if (sp1 == std::string::npos) return false;
	mth = line.substr(0, sp1);
	size_t sp2 = line.find(" ", sp1 + 1);
	if (sp2 == std::string::npos) return false;
	path = line.substr(sp1 + 1, sp2 - sp1 - 1);
	return true;
}
bool ClientSession::parseHdrs()
{
	std::size_t hdr_end = in_buf.find("\r\n\r\n");
	if (hdr_end == std::string::npos) return false;
	std::string hdrs_str = in_buf.substr(0, hdr_end);
	std::size_t ln_end = hdrs_str.find("\r\n");
	if (ln_end == std::string::npos) return false;
	if (!parseReqLine(hdrs_str.substr(0, ln_end), method, req_path)) {
		return false;
	}
	std::size_t p = ln_end + 2;
	while (p < hdr_end) {
		std::size_t nxt = hdrs_str.find("\r\n", p);
		if (nxt == std::string::npos) break;
		std::string hdr_line = hdrs_str.substr(p, nxt - p);
		std::size_t colon = hdr_line.find(":");
		if (colon != std::string::npos) {
			std::string k = hdr_line.substr(0, colon);
			std::string v = trimWS(hdr_line.substr(colon + 1));
			req_hdrs[k] = v;
			if (k == "Host") host = v;
			if (k == "Content-Length") {
				content_len = my_strtoul(v.c_str(), NULL, 10);
				content_done = false;
			}
			if (k == "Transfer-Encoding" && v == "chunked") {
				is_chunk_req = true;
				chunk_done = false;
			}
			if (k == "Connection") {
				keep_alive = (v != "close");
			}
			if (k == "Cookie") {
				extractCookies(v, cookies, sess_id);
			}
		}
		p = nxt + 2;
	}
	in_buf.erase(0, hdr_end + 4);
	if (!is_chunk_req && !content_done) {
		if (in_buf.length() >= content_len) {
			req_body = in_buf.substr(0, content_len);
			in_buf.erase(0, content_len);
			content_done = true;
		}
	}
	return true;
}
void ClientSession::clearReq()
{
	method.clear();
	req_path.clear();
	req_body.clear();
	req_hdrs.clear();
	chunk_body.clear();
	chunk_buf.clear();
	chunk_rem.clear();
	is_chunk_req = false;
	chunk_done = true;
	content_done = true;
	total_chunk = 0;
	hdrs_parsed = false;
	req_processed = false;
	req_done = false;
	hdrs_done = false;
	chunk_proc = false;
	chunk_st.state = ChunkState::WAIT_SIZE;
	chunk_st.body.clear();
	chunk_st.chunk_sz = 0;
	chunk_st.bytes_read = 0;
	chunk_st.is_final = false;
	chunk_st.end_write = false;
	chunk_st.ready = false;
	chunk_st.total_sz = 0;
}
ClientSession::ClientSession() 
	: fd(-1), resp_ready(false), ip(""),
	  last_active(getTimeTick()), req_in_win(0), win_start(getTimeTick()),
	  sess_id(""), need_cookie(false), req_path(""), host(""), srv_name(""),
	  should_close(false), method(""), version(""), chunk_buf(""),
	  is_chunked(false), chunk_done(true), resp_dbg(""), conn_closed(false),
	  req_done(false), total_chunk(0), hdrs_parsed(false), need_cgi(false),
	  req_processed(false), write_disabled(false), cgi_stream(false),
	  cgi_pid(-1), cgi_in(-1), cgi_out(-1), cgi_hdr_sent(false),
	  cgi_output(""), chunk_rem(""), route(NULL), bytes_sent(0),
	  chunk_proc(false), keep_alive(true), hdrs_done(false),
	  raw_req(""), req_body(""), chunk_body(""), content_len(0),
	  content_done(true), is_chunk_req(false), buf_idx(0), has_queued(false)
{
	resetBufs();
}
ClientSession::ClientSession(const ClientSession& o)
	: fd(o.fd), in_buf(o.in_buf), resp_data(o.resp_data), resp_ready(o.resp_ready),
	  ip(o.ip), last_active(o.last_active), req_in_win(o.req_in_win),
	  win_start(o.win_start), sess_id(o.sess_id), need_cookie(o.need_cookie),
	  req_path(o.req_path), host(o.host), srv_name(o.srv_name),
	  should_close(o.should_close), method(o.method), version(o.version),
	  chunk_buf(o.chunk_buf), is_chunked(o.is_chunked), chunk_done(o.chunk_done),
	  resp_dbg(o.resp_dbg), conn_closed(o.conn_closed), req_done(o.req_done),
	  total_chunk(o.total_chunk), hdrs_parsed(o.hdrs_parsed), need_cgi(o.need_cgi),
	  req_processed(o.req_processed), write_disabled(o.write_disabled),
	  cgi_stream(o.cgi_stream), cgi_pid(o.cgi_pid), cgi_in(o.cgi_in),
	  cgi_out(o.cgi_out), cgi_hdr_sent(o.cgi_hdr_sent), cgi_output(o.cgi_output),
	  chunk_rem(o.chunk_rem), route(o.route), bytes_sent(o.bytes_sent),
	  chunk_proc(o.chunk_proc), keep_alive(o.keep_alive), hdrs_done(o.hdrs_done),
	  hdrs(o.hdrs), raw_req(o.raw_req), req_body(o.req_body),
	  chunk_body(o.chunk_body), content_len(o.content_len),
	  content_done(o.content_done), is_chunk_req(o.is_chunk_req),
	  req_hdrs(o.req_hdrs), cookies(o.cookies), buf_idx(o.buf_idx),
	  has_queued(o.has_queued), chunk_st(o.chunk_st)
{
	for (int i = 0; i < PRE_ALLOCATED_BUFFERS; i++) {
		my_memcpy(bufs[i], o.bufs[i], RESPONSE_BUFFER_SIZE);
	}
	req_queue = o.req_queue;
}
ClientSession& ClientSession::operator=(const ClientSession& o)
{
	if (this != &o) {
		fd = o.fd; in_buf = o.in_buf; resp_data = o.resp_data;
		resp_ready = o.resp_ready; ip = o.ip; last_active = o.last_active;
		req_in_win = o.req_in_win; win_start = o.win_start; sess_id = o.sess_id;
		need_cookie = o.need_cookie; req_path = o.req_path; host = o.host;
		srv_name = o.srv_name; should_close = o.should_close; method = o.method;
		version = o.version; chunk_buf = o.chunk_buf; is_chunked = o.is_chunked;
		chunk_done = o.chunk_done; resp_dbg = o.resp_dbg; conn_closed = o.conn_closed;
		req_done = o.req_done; total_chunk = o.total_chunk; hdrs_parsed = o.hdrs_parsed;
		need_cgi = o.need_cgi; req_processed = o.req_processed;
		write_disabled = o.write_disabled; cgi_stream = o.cgi_stream;
		cgi_pid = o.cgi_pid; cgi_in = o.cgi_in; cgi_out = o.cgi_out;
		cgi_hdr_sent = o.cgi_hdr_sent; cgi_output = o.cgi_output;
		chunk_rem = o.chunk_rem; route = o.route; bytes_sent = o.bytes_sent;
		chunk_proc = o.chunk_proc; keep_alive = o.keep_alive; hdrs_done = o.hdrs_done;
		hdrs = o.hdrs; raw_req = o.raw_req; req_body = o.req_body;
		chunk_body = o.chunk_body; content_len = o.content_len;
		content_done = o.content_done; is_chunk_req = o.is_chunk_req;
		req_hdrs = o.req_hdrs; cookies = o.cookies; buf_idx = o.buf_idx;
		has_queued = o.has_queued; chunk_st = o.chunk_st;
		for (int i = 0; i < PRE_ALLOCATED_BUFFERS; i++) {
			my_memcpy(bufs[i], o.bufs[i], RESPONSE_BUFFER_SIZE);
		}
		req_queue = o.req_queue;
	}
	return *this;
}
ClientSession::~ClientSession()
{
	for (std::vector<HttpRequest*>::iterator it = req_queue.begin(); it != req_queue.end(); ++it) {
	}
	req_queue.clear();
}
bool ClientSession::isChunked() const
{
	return in_buf.find("Transfer-Encoding: chunked") != std::string::npos;
}
bool ClientSession::hasReq() const 
{
	return in_buf.find("\r\n\r\n") != std::string::npos;
}
void ClientSession::clearBuf() 
{
	in_buf.clear();
	resp_data.clear();
}
void ClientSession::updateActive() 
{
	last_active = getTimeTick();
}
bool ClientSession::isTimeout(time_t cur, int timeout) const 
{
	return (cur - last_active) > timeout;
}
char* ClientSession::getNextBuf()
{
	char* b = bufs[buf_idx];
	buf_idx = (buf_idx + 1) % PRE_ALLOCATED_BUFFERS;
	return b;
}
void ClientSession::resetBufs()
{
	for (int i = 0; i < PRE_ALLOCATED_BUFFERS; i++) {
		my_memset(bufs[i], 0, RESPONSE_BUFFER_SIZE);
	}
	buf_idx = 0;
}
void ClientSession::appendChunk(const std::string& s)
{
	chunk_body.append(s);
}
std::string ClientSession::getChunk() const
{
	return chunk_body;
}
void ClientSession::queueReq(HttpRequest* r)
{
	req_queue.push_back(r);
	has_queued = true;
}
HttpRequest* ClientSession::getNextReq()
{
	if (req_queue.empty()) {
		has_queued = false;
		return NULL;
	}
	HttpRequest* r = req_queue.front();
	req_queue.erase(req_queue.begin());
	has_queued = !req_queue.empty();
	return r;
}
