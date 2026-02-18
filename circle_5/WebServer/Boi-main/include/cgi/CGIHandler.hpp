#ifndef CGI_PROCESSOR_HPP
#define CGI_PROCESSOR_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <map>
#include <stdexcept>
#include <cstring>
#include <cerrno>
#include <sstream>
#include <fcntl.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <cstdio>
#include <poll.h>
#include <vector>

#define TIME_OUT 2
#define CGI_PATH "./cgi-bin/"

class CGIProcessor {
	private:
		int pipe_file_descriptors_[2];
		int input_pipe_;
		pid_t cgi_process_id_;
		std::string script_file_path_;
	std::map<std::string, std::string> environment_variables_;
	std::string request_path_;
	std::string route_pattern_;
	std::string document_root_;

	void validateScriptPath(const std::string &scriptPath);
	char **convertMapToCharArray();
		void configureNonBlockingSocket(int fd);
		void handleTimeoutSignal(int sig);

	public:
		CGIProcessor();
		CGIProcessor(const std::map<std::string, std::string> &env);
		CGIProcessor(const CGIProcessor &src);
		~CGIProcessor();
		
		CGIProcessor &operator=(const CGIProcessor &src);
		void setRequestInformation(const std::string& requestPath, const std::string& routePattern, const std::string& documentRoot);
		std::string executeScript();
		std::string executeScriptWithInput(const std::string& input_data);
		void setScriptFilePath(const std::string& path);
 
};

#endif