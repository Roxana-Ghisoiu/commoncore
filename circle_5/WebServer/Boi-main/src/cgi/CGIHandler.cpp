
#include "cgi/CGIHandler.hpp"
#include "cgi/cgi_helpers.hpp"
#include "utils/utils.hpp"

CGIProcessor::CGIProcessor() {
	input_pipe_ = -1;
	cgi_process_id_ = -1;
	pipe_file_descriptors_[0] = -1;
	pipe_file_descriptors_[1] = -1;
}

CGIProcessor::CGIProcessor(const std::map<std::string, std::string> &env)
{
	input_pipe_ = -1;
	cgi_process_id_ = -1;
	pipe_file_descriptors_[0] = -1;
	pipe_file_descriptors_[1] = -1;
	if (env.empty()) {
		throw std::runtime_error("Environment map cannot be empty");
	}
	this->environment_variables_ = env;
	if (env.find("SCRIPT_FILENAME") != env.end()) {
		this->script_file_path_ = env.at("SCRIPT_FILENAME");
	} else {
		throw std::runtime_error("SCRIPT_FILENAME missing from environment");
	}
	if (env.find("REQUEST_PATH") != env.end()) {
		this->request_path_ = env.at("REQUEST_PATH");
	} else {
		this->request_path_ = "";
	}
	if (env.find("SCRIPT_NAME") != env.end()) {
		this->request_path_ = env.at("SCRIPT_NAME");
	} else {
		this->request_path_ = "";
	}
	if (env.find("ROUTE_PATH") != env.end()) {
		this->route_pattern_ = env.at("ROUTE_PATH");
	} else {
		this->route_pattern_ = "";
	}
	if (env.find("DOCUMENT_ROOT") != env.end()) {
		this->document_root_ = env.at("DOCUMENT_ROOT");
	} else {
		this->document_root_ = ".";
	}
	validateScriptPath(this->script_file_path_);
}
void CGIProcessor::setScriptFilePath(const std::string& path) {
    script_file_path_ = path;
}
CGIProcessor::CGIProcessor(const CGIProcessor &src)
{
	*this = src;
}
CGIProcessor::~CGIProcessor() {
    if (pipe_file_descriptors_[0] >= 0) {
        close(pipe_file_descriptors_[0]);
        pipe_file_descriptors_[0] = -1;
    }
    if (pipe_file_descriptors_[1] >= 0) {
        close(pipe_file_descriptors_[1]);
        pipe_file_descriptors_[1] = -1;
    }
    if (input_pipe_ >= 0) {
        close(input_pipe_);
        input_pipe_ = -1;
    }
    if (cgi_process_id_ > 0) {
        kill(cgi_process_id_, SIGKILL);
        waitpid(cgi_process_id_, NULL, WNOHANG);
        cgi_process_id_ = -1;
    }
}
CGIProcessor &CGIProcessor::operator=(const CGIProcessor &src)
{
	if (this == &src) {
		return *this;
	}
	this->environment_variables_ = src.environment_variables_;
	this->script_file_path_ = src.script_file_path_;
	this->request_path_ = src.request_path_;
	this->route_pattern_ = src.route_pattern_;
	this->document_root_ = src.document_root_;
	this->cgi_process_id_ = src.cgi_process_id_;
	this->input_pipe_ = src.input_pipe_;
	this->pipe_file_descriptors_[0] = src.pipe_file_descriptors_[0];
	this->pipe_file_descriptors_[1] = src.pipe_file_descriptors_[1];
	return *this;
}
void CGIProcessor::handleTimeoutSignal(int sig)
{
	if (sig == SIGALRM)
	{
		if (cgi_process_id_ > 0)
		{
			if (input_pipe_ >= 0) {
				close(input_pipe_);
				input_pipe_ = -1;
			}
			kill(cgi_process_id_, SIGKILL);
			waitpid(cgi_process_id_, NULL, 0);
			cgi_process_id_ = -1;
		}
		throw std::runtime_error("Script timeout exceeded");
	}
}
void CGIProcessor::setRequestInformation(const std::string& requestPath, const std::string& routePattern, const std::string& documentRoot)
{
	request_path_ = requestPath;
	route_pattern_ = routePattern;
	document_root_ = documentRoot;
}
void CGIProcessor::validateScriptPath(const std::string &scriptPath)
{
	struct stat st;
	if (scriptPath.find("..") != std::string::npos &&
		scriptPath.find(CGI_PATH) != 0 && 
		scriptPath.find("./") != 0) {
		throw std::runtime_error("Path traversal blocked");
	}
	bool isValidPath = (scriptPath.find(CGI_PATH) == 0) || (scriptPath.find("./") == 0);
	if (!isValidPath) {
		throw std::runtime_error("Invalid CGI path");
	}
	if (stat(scriptPath.c_str(), &st) == -1) {
		throw std::runtime_error(std::string(strerror(errno)));
	}
	bool isPythonScript = false;
	size_t ext_pos = scriptPath.rfind(".");
	if (ext_pos != std::string::npos) {
		std::string ext = scriptPath.substr(ext_pos);
		if (ext == ".py") {
			isPythonScript = true;
		}
	}
	if (scriptPath.find("cgi_tester") == std::string::npos && 
		!isPythonScript && 
		st.st_uid != getuid()) {
		throw std::runtime_error("Script owner mismatch");
	}
	if (!(st.st_mode & S_IXUSR) && !isPythonScript) {
		throw std::runtime_error("Script lacks execute permission");
	}
}
static int sendDataToPipe(int fd, const std::string& data)
{
	size_t sent = 0;
	size_t rem = data.length();
	const char* ptr = data.c_str();
	while (sent < data.length())
	{
		ssize_t w = write(fd, ptr + sent, rem);
		if (w < 0) {
			if (errno == EINTR) continue;
			return -1;
		} 
		if (w == 0) break;
		sent += w;
		rem -= w;
	}
	return 0;
}
std::string CGIProcessor::executeScriptWithInput(const std::string& input_data)
{
	const size_t THRESHOLD = 1 * 1024 * 1024;
	bool use_tmp = input_data.size() > THRESHOLD;
	std::vector<int> tmp_fds;
	std::vector<std::string> tmp_names;
	int in_p[2] = {-1, -1};
	int out_p[2] = {-1, -1};
	std::string result;
	pid_t pid = -1;
	try {
		if (!use_tmp && pipe(in_p) < 0) {
			throw std::runtime_error("Pipe creation error");
		}
		if (pipe(out_p) < 0) {
			throw std::runtime_error("Output pipe error");
		}
		if (use_tmp) {
			if (input_data.size() > 50 * 1024 * 1024) {
				if (createTempFiles(input_data, tmp_fds, tmp_names) != 0) {
					throw std::runtime_error("Temp file creation failed");
				}
			} else {
				char tmp[64] = "/tmp/webserv_cgi_XXXXXX";
				int fd = mkstemp(tmp);
				if (fd == -1) throw std::runtime_error("mkstemp failed");
				tmp_fds.push_back(fd);
				tmp_names.push_back(std::string(tmp));
				if (writeTempFile(fd, input_data, 0, input_data.length()) != 0) {
					close(fd);
					unlink(tmp);
					throw std::runtime_error("Temp write failed");
				}
				lseek(fd, 0, SEEK_SET);
			}
		}
		pid = fork();
		cgi_process_id_ = pid;
		if (pid < 0) {
			throw std::runtime_error("Fork error");
		}
		if (pid == 0)
		{
			if (use_tmp) {
				if (tmp_fds.size() == 1) {
					if (dup2(tmp_fds[0], STDIN_FILENO) == -1) exit(EXIT_FAILURE);
					close(tmp_fds[0]);
				} else {
					int cat_p[2];
					if (pipe(cat_p) < 0) exit(EXIT_FAILURE);
					pid_t cat_pid = forkCatHelper(tmp_fds, cat_p[1]);
					if (cat_pid < 0) exit(EXIT_FAILURE);
					close(cat_p[1]);
					if (dup2(cat_p[0], STDIN_FILENO) == -1) exit(EXIT_FAILURE);
					close(cat_p[0]);
					for (size_t i = 0; i < tmp_fds.size(); i++) {
						close(tmp_fds[i]);
					}
				}
			} else {
				close(in_p[1]);
				if (dup2(in_p[0], STDIN_FILENO) == -1) exit(EXIT_FAILURE);
				close(in_p[0]);
			}
			close(out_p[0]);
			if (dup2(out_p[1], STDOUT_FILENO) == -1) exit(EXIT_FAILURE);
			close(out_p[1]);
			char *argv[] = {const_cast<char*>(script_file_path_.c_str()), NULL};
			char **envp = convertMapToCharArray();
			execve(script_file_path_.c_str(), argv, envp);
			const char* err = "Exec failed\n";
			write(STDERR_FILENO, err, strlen(err));
			exit(EXIT_FAILURE);
		}
		else 
		{
			if (!use_tmp) {
				close(in_p[0]);
			} else {
				for (size_t i = 0; i < tmp_fds.size(); i++) {
					close(tmp_fds[i]);
				}
			}
			close(out_p[1]);
			if (!use_tmp && !input_data.empty())
			{
				if (sendDataToPipe(in_p[1], input_data) != 0) {
					close(in_p[1]);
					close(out_p[0]);
					if (use_tmp) cleanupTempFiles(tmp_fds, tmp_names);
					throw std::runtime_error("Data write error");
				}
				close(in_p[1]);
			}
			int fl = fcntl(out_p[0], F_GETFL, 0);
			if (fl == -1 || fcntl(out_p[0], F_SETFL, fl | O_NONBLOCK) == -1) {
				close(out_p[0]);
				cleanupTempFiles(tmp_fds, tmp_names);
				throw std::runtime_error("Non-blocking setup failed");
			}
			int max_it = 10;
			if (input_data.size() > 50 * 1024 * 1024) {
				max_it = 1000;
			} else if (input_data.size() > 10 * 1024 * 1024) {
				max_it = 300;
			}
			if (input_data.size() > 10 * 1024 * 1024) {
				result.reserve(input_data.size() / 10);
			}
			result = readCGIOutput(out_p[0], max_it);
			close(out_p[0]);
			int st;
			waitpid(pid, &st, 0);
			cleanupTempFiles(tmp_fds, tmp_names);
			return result;
		}
	}
	catch (const std::exception& e) {
		if (!use_tmp) {
			if (in_p[0] >= 0) close(in_p[0]);
			if (in_p[1] >= 0) close(in_p[1]);
		}
		if (out_p[0] >= 0) close(out_p[0]);
		if (out_p[1] >= 0) close(out_p[1]);
		cleanupTempFiles(tmp_fds, tmp_names);
		if (pid > 0) {
			kill(pid, SIGKILL);
			waitpid(pid, NULL, 0);
		}
		throw;
	}
	return "";
}
char **CGIProcessor::convertMapToCharArray()
{
	std::map<std::string, std::string>::const_iterator it = environment_variables_.begin();
	char **env = new char*[environment_variables_.size() + 1];
	int i = 0;
	while (it != environment_variables_.end())
	{
		env[i] = new char[it->first.size() + it->second.size() + 2];
		my_strcpy(env[i], (it->first + "=" + it->second).c_str());
		++it;
		++i;
	}
	env[i] = NULL;
	return env;
}
void CGIProcessor::configureNonBlockingSocket(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1) {
		throw std::runtime_error("Fcntl get error: " + std::string(strerror(errno)));
	}
	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
		throw std::runtime_error("Fcntl set error: " + std::string(strerror(errno)));
	}
}
std::string CGIProcessor::executeScript()
{
	int p[2];
	std::string out;
	pid_t pid;
	char buf[4096];
	if (pipe(p) == -1) {
		throw std::runtime_error("Pipe error: " + std::string(strerror(errno)));
	}
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	sigaction(SIGALRM, &sa, NULL);
	pid = fork();
	if (pid == -1) {
		close(p[0]);
		close(p[1]);
		throw std::runtime_error("Fork error: " + std::string(strerror(errno)));
	}
	if (pid == 0) {
		close(p[0]);
		if (dup2(p[1], STDOUT_FILENO) == -1) exit(EXIT_FAILURE);
		close(p[1]);
		char **env = convertMapToCharArray();
		bool is_py = false;
		std::string py_path = "";
		size_t dot = script_file_path_.rfind(".");
		if (dot != std::string::npos) {
			std::string ext = script_file_path_.substr(dot);
			if (ext == ".py") {
				is_py = true;
				py_path = findPythonInterp();
			}
		}
		if (is_py && !py_path.empty()) {
			execPythonScript(py_path, script_file_path_, env);
		} else {
			execRegularScript(script_file_path_, env);
		}
		exit(EXIT_FAILURE);
	}
	close(p[1]);
	configureNonBlockingSocket(p[0]);
	input_pipe_ = p[0];
	cgi_process_id_ = pid;
	bool active = true;
	int tmo = 0;
	const int max_tmo = 3;
	fd_set rds;
	struct timeval tv;
	while (active && tmo < max_tmo)
	{
		FD_ZERO(&rds);
		FD_SET(p[0], &rds);
		tv.tv_sec = 1;
		tv.tv_usec = 0;
		int ret = select(p[0] + 1, &rds, NULL, NULL, &tv);
		if (ret == -1) {
			if (errno == EINTR) continue;
			close(p[0]);
			input_pipe_ = -1;
			throw std::runtime_error("Select error");
		} 
		else if (ret > 0) {
			ssize_t r = read(p[0], buf, sizeof(buf) - 1);
			if (r > 0) {
				buf[r] = '\0';
				out.append(buf, r);
				tmo = 0;
			} else if (r == 0) {
				active = false;
				break;
			} else {
				if (errno != EAGAIN && errno != EWOULDBLOCK && errno != EINTR) {
					close(p[0]);
					input_pipe_ = -1;
					throw std::runtime_error("Read error");
				}
			}
		}
		else {
			tmo++;
		}
	}
	if (tmo >= max_tmo) {
		if (kill(pid, 0) == 0) {
			kill(pid, SIGTERM);
			usleep(100);
			if (kill(pid, 0) == 0) {
				kill(pid, SIGKILL);
			}
		}
	}
	close(p[0]);
	input_pipe_ = -1;
	int st;
	waitpid(pid, &st, WNOHANG);
	cgi_process_id_ = -1;
	alarm(0);
	signal(SIGALRM, SIG_DFL);
	return out;
}
