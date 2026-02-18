#ifndef UTILS_HPP
#define UTILS_HPP

#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stddef.h>

char* my_strcpy(char* dest, const char* src);
int my_strcmp(const char* s1, const char* s2);
int my_atoi(const char* str);
int my_isdigit(int c);
int my_isalnum(int c);
size_t my_strlen(const char* s);
void int_to_str(int num, char* buffer);
void* my_memset(void* s, int c, size_t n);
void* my_memcpy(void* dest, const void* src, size_t n);

class TimeMgr {
    private:
        static long start;
        static long counter;
        
    public:
        static void init();
        static long getTime();
        static void fmtTime(char* buf, size_t size);
};

class RandGen {
    private:
        static unsigned long seed;
        
    public:
        static void setSeed(unsigned long s);
        static int gen();
};

void debug_write(const char* message);
void debug_write_int(int number);
const char* my_strsignal(int signum);
unsigned long my_strtoul(const char* str, char** endptr, int base);
char* my_inet_ntoa(struct in_addr in);
long getTimeTick();

#endif 