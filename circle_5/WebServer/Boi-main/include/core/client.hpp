#ifndef CLIENT_SESSION_HPP
# define CLIENT_SESSION_HPP
# include <string>
# include <ctime>
# include <map>
# include "config/configParser.hpp"
# include <list>
# include <vector>
# include <sstream>
# include <cstring>

#define RESPONSE_BUFFER_SIZE 16384
#define PRE_ALLOCATED_BUFFERS 3

struct HttpRequest;
class HttpResponse;

/*
 * ClientSession represents a connection to a client.
 * Important: To prevent duplicated responses, ensure that:
 * 1. has_queued_requests is properly managed and reset after processing queued requests
 * 2. request_queue is cleared when finishing a response
 * 3. When cookies are needed, they're properly handled before sending the response
 * 4. ready_to_write is only set to true when a response is ready to be sent
 */
class ClientSession
{
	public:
		int fd;
		std::string in_buf;
		std::string resp_data;
		bool resp_ready;
		std::string ip;
		time_t last_active;
		size_t req_in_win;
		time_t win_start;
		std::string sess_id;
		bool need_cookie;
		std::string req_path;
		std::string host;
		std::string srv_name;
		bool should_close;
		std::string method;
		std::string version;
		std::string chunk_buf;
		bool is_chunked;
		bool chunk_done;
		std::string resp_dbg;
		bool conn_closed;
		bool req_done;
		size_t total_chunk;
		bool hdrs_parsed;
		bool need_cgi;
		bool req_processed;
		bool write_disabled;
		bool cgi_stream;
		pid_t cgi_pid;
		int cgi_in;
		int cgi_out;
		bool cgi_hdr_sent;
		std::string cgi_output;
		std::string chunk_rem;
		Route* route;
		size_t bytes_sent;
		bool chunk_proc;
		bool keep_alive;
		bool hdrs_done;
		std::map<std::string, std::string> hdrs;
		std::string raw_req;
		std::string req_body;
		std::string chunk_body;
		std::size_t content_len;
		bool content_done;
		bool is_chunk_req;
		std::map<std::string, std::string> req_hdrs;
		std::map<std::string, std::string> cookies;
		char bufs[PRE_ALLOCATED_BUFFERS][RESPONSE_BUFFER_SIZE];
		int buf_idx;
		std::vector<HttpRequest*> req_queue;
		bool has_queued;
		
		ClientSession();
		ClientSession(const ClientSession& other);
		ClientSession& operator=(const ClientSession& other);
		~ClientSession();
		bool hasReq() const;
		void clearBuf();
		void updateActive();
		bool isTimeout(time_t cur, int timeout) const;
		bool isChunked() const;
	
		struct ChunkState {
			enum State {
				WAIT_SIZE,
				READ_HDRS,
				READ_SIZE,
				READ_DATA,
				READ_END,
				READ_TRAIL,
				DONE,
				ERROR
			};
			
			State state;
			std::string body;
			size_t chunk_sz;
			size_t bytes_read;
			bool is_final;
			bool end_write;
			bool ready;
			size_t total_sz;
			
			ChunkState() : 
			state(WAIT_SIZE),
			chunk_sz(0),
			bytes_read(0),
			is_final(false),
			end_write(false),
			ready(false),
			total_sz(0) {}
		};
		ChunkState chunk_st;
		char* getNextBuf();
		void resetBufs();
		bool parseHdrs();
		void clearReq();
		void queueReq(HttpRequest* req);
		HttpRequest* getNextReq();
		void appendChunk(const std::string& str);
		std::string getChunk() const;
};

#endif