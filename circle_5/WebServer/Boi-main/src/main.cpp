#include "core/server.hpp"
#include "core/client.hpp"
#include "cgi/CGIHandler.hpp"
#include <iostream>
#include <signal.h>
#include "utils/utils.hpp"


/*
 * =============================================================================
 * MAIN ENTRY POINT - WEB SERVER INITIALIZATION
 * =============================================================================
 * This is where everything begins. The main function:
 * 1. Initializes system components (time manager, random generator)
 * 2. Sets up signal handlers to ignore SIGPIPE
 * 3. Creates the WebServerEngine instance
 * 4. Loads configuration from file
 * 5. Initializes server sockets for listening
 * 6. Starts the main server loop
 * 
 * Flow: main() -> loadConfiguration() -> initializeAllServerSockets() -> startServer()
 * =============================================================================
 */
int main(int argc, char** argv) 
{
    TimeMgr::init();
    RandGen::setSeed(42);
    signal(SIGPIPE, SIG_IGN);
    try {
        std::string configuration_file = "conf/webserver.conf";
        if (argc > 1) {
            configuration_file = argv[1];
        }
        WebServerEngine web_server_engine;
        web_server_engine.loadConfiguration(configuration_file);
        web_server_engine.initializeAllServerSockets();
        web_server_engine.startServer();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
