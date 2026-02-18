#ifndef CGI_HELPERS_HPP
#define CGI_HELPERS_HPP

#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>

int writeTempFile(int fd, const std::string& data, size_t offset, size_t len);
int createTempFiles(const std::string& input, std::vector<int>& fds, std::vector<std::string>& names);
void cleanupTempFiles(const std::vector<int>& fds, const std::vector<std::string>& names);
pid_t forkCatHelper(const std::vector<int>& fds, int pipe_wr);
std::string readCGIOutput(int fd, int max_iter);
void execPythonScript(const std::string& interp, const std::string& script, char** env);
void execRegularScript(const std::string& script, char** env);
std::string findPythonInterp();

#endif

