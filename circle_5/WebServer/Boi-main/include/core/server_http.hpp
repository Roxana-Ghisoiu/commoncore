#ifndef SERVER_HTTP_HPP
#define SERVER_HTTP_HPP

#include "core/server.hpp"

class HTTPHandler
{
public:
	static void handleGET(WebServerEngine* srv, ClientSession& cli);
	static void handlePOST(WebServerEngine* srv, ClientSession& cli);
	static void handlePUT(WebServerEngine* srv, ClientSession& cli);
	static void handleDEL(WebServerEngine* srv, ClientSession& cli);
	static void handleCGI(WebServerEngine* srv, ClientSession& cli, Route* r);
	static bool handleChunks(WebServerEngine* srv, ClientSession& cli);
};

#endif

