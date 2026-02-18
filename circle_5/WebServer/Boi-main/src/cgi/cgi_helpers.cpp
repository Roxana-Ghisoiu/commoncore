#include "cgi/cgi_helpers.hpp"
#include "utils/utils.hpp"
#include <fcntl.h>
#include <sys/wait.h>
#include <cstring>
#include <cerrno>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>

int writeTempFile(int fd, const std::string& data, size_t offset, size_t len)
{
	size_t written = 0;
	const char* ptr = data.c_str() + offset;
	while (written < len)
	{
		ssize_t w = write(fd, ptr + written, len - written);
		if (w < 0) {
			if (errno == EINTR) continue;
			return -1;
		} 
		if (w == 0) break;
		written += w;
	}
	return 0;
}
int createTempFiles(const std::string& input, std::vector<int>& fds, std::vector<std::string>& names)
{
	const size_t CHUNK = 50 * 1024 * 1024;
	size_t remain = input.size();
	size_t offset = 0;
	while (remain > 0)
	{
		char tmp[64] = "/tmp/webserv_cgi_XXXXXX";
		int fd = mkstemp(tmp);
		if (fd == -1) return -1;
		fds.push_back(fd);
		names.push_back(std::string(tmp));
		size_t chunk_sz = (remain > CHUNK) ? CHUNK : remain;
		if (writeTempFile(fd, input, offset, chunk_sz) != 0) {
			return -1;
		}
		lseek(fd, 0, SEEK_SET);
		offset += chunk_sz;
		remain -= chunk_sz;
	}
	return 0;
}
void cleanupTempFiles(const std::vector<int>& fds, const std::vector<std::string>& names)
{
	for (size_t i = 0; i < fds.size(); i++) {
		if (fds[i] >= 0) close(fds[i]);
	}
	for (size_t i = 0; i < names.size(); i++) {
		unlink(names[i].c_str());
	}
}
pid_t forkCatHelper(const std::vector<int>& fds, int pipe_wr)
{
	pid_t p = fork();
	if (p < 0) return -1;
	if (p == 0) {
		char buf[8192];
		for (size_t i = 0; i < fds.size(); i++) {
			ssize_t r;
			while ((r = read(fds[i], buf, sizeof(buf))) > 0) {
				ssize_t w = 0;
				while (w < r) {
					ssize_t wr = write(pipe_wr, buf + w, r - w);
					if (wr < 0) {
						if (errno == EINTR) continue;
						exit(EXIT_FAILURE);
					}
					w += wr;
				}
			}
			close(fds[i]);
		}
		close(pipe_wr);
		exit(EXIT_SUCCESS);
	}
	return p;
}
std::string readCGIOutput(int fd, int max_iter)
{
	std::string out;
	char buf[8192];
	int iter = 0;
	bool active = true;
	fd_set rds;
	struct timeval tv;
	while (active && iter < max_iter)
	{
		FD_ZERO(&rds);
		FD_SET(fd, &rds);
		tv.tv_sec = 0;
		tv.tv_usec = 100000;
		int sel = select(fd + 1, &rds, NULL, NULL, &tv);
		if (sel > 0) {
			ssize_t r = read(fd, buf, sizeof(buf) - 1);
			if (r > 0) {
				buf[r] = '\0';
				out.append(buf, r);
				iter = 0;
			} else if (r == 0) {
				active = false;
			} else if (errno != EAGAIN && errno != EWOULDBLOCK && errno != EINTR) {
				active = false;
			}
		} else if (sel == 0) {
			iter++;
		} else if (errno != EINTR) {
			active = false;
		}
	}
	return out;
}
void execPythonScript(const std::string& interp, const std::string& script, char** env)
{
	char* av[3];
	av[0] = strdup(interp.c_str());
	av[1] = strdup(script.c_str());
	av[2] = NULL;
	if (execve(av[0], av, env) == -1) {
		const char* msg = "Python exec error\n";
		write(STDERR_FILENO, msg, strlen(msg));
		exit(EXIT_FAILURE);
	}
}
void execRegularScript(const std::string& script, char** env)
{
	char* av[2];
	av[0] = strdup(script.c_str());
	av[1] = NULL;
	if (execve(av[0], av, env) == -1) {
		const char* msg = "Script exec error\n";
		write(STDERR_FILENO, msg, strlen(msg));
		exit(EXIT_FAILURE);
	}
}
std::string findPythonInterp()
{
	if (access("/usr/bin/python3", X_OK) == 0) return "/usr/bin/python3";
	if (access("/usr/local/bin/python3", X_OK) == 0) return "/usr/local/bin/python3";
	return "";
}
