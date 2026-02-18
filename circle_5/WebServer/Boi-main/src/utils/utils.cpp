#include "utils/utils.hpp"

long TimeMgr::start = 0;
long TimeMgr::counter = 0;
unsigned long RandGen::seed = 1;


char* my_strcpy(char* dest, const char* src) {
    char* original_dest = dest;
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
    return original_dest;
}
int my_strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}
int my_atoi(const char* str) {
    int result = 0;
    int sign = 1;
    while (*str == ' ' || *str == '\t' || *str == '\n')
        str++;
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return sign * result;
}
int my_isdigit(int c) {
    return (c >= '0' && c <= '9');
}
int my_isalnum(int c) {
    return (c >= '0' && c <= '9') || 
           (c >= 'A' && c <= 'Z') || 
           (c >= 'a' && c <= 'z');
}
size_t my_strlen(const char* s) {
    size_t len = 0;
    while (*s++) len++;
    return len;
}
void int_to_str(int num, char* buffer) {
    if (num == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }
    int is_negative = 0;
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    int i = 0;
    while (num > 0) {
        buffer[i++] = '0' + (num % 10);
        num /= 10;
    }
    if (is_negative) {
        buffer[i++] = '-';
    }
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }
    buffer[i] = '\0';
}
void* my_memset(void* s, int c, size_t n) {
    unsigned char* p = (unsigned char*)s;
    while (n--) {
        *p++ = (unsigned char)c;
    }
    return s;
}
void* my_memcpy(void* dest, const void* src, size_t n) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}
void TimeMgr::init() {
    counter = 0;
}
long TimeMgr::getTime() {
    return ++counter;
}
static long tick_counter = 0;
long getTimeTick() {
    return ++tick_counter;
}
void TimeMgr::fmtTime(char* buffer, size_t) {
    long t = getTime();
    long hours = (t / 3600) % 24;
    long minutes = (t / 60) % 60;
    long seconds = t % 60;
    char temp[20];
    int pos = 0;
    temp[pos++] = '0' + (hours / 10);
    temp[pos++] = '0' + (hours % 10);
    temp[pos++] = ':';
    temp[pos++] = '0' + (minutes / 10);
    temp[pos++] = '0' + (minutes % 10);
    temp[pos++] = ':';
    temp[pos++] = '0' + (seconds / 10);
    temp[pos++] = '0' + (seconds % 10);
    temp[pos] = '\0';
    my_strcpy(buffer, temp);
}
void RandGen::setSeed(unsigned long s) {
    seed = s;
}
int RandGen::gen() {
    seed = seed * 1103515245 + 12345;
    return (unsigned int)(seed / 65536) % 32768;
}
void debug_write(const char* message) {
    int fd = open("debug.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd != -1) {
        write(fd, message, my_strlen(message));
        close(fd);
    }
}
void debug_write_int(int number) {
    char buffer[20];
    int_to_str(number, buffer);
    debug_write(buffer);
}
const char* my_strsignal(int signum) {
    switch (signum) {
        case 1: return "SIGHUP";
        case 2: return "SIGINT";
        case 3: return "SIGQUIT";
        case 4: return "SIGILL";
        case 5: return "SIGTRAP";
        case 6: return "SIGABRT";
        case 8: return "SIGFPE";
        case 9: return "SIGKILL";
        case 10: return "SIGUSR1";
        case 11: return "SIGSEGV";
        case 12: return "SIGUSR2";
        case 13: return "SIGPIPE";
        case 14: return "SIGALRM";
        case 15: return "SIGTERM";
        case 18: return "SIGCONT";
        case 19: return "SIGSTOP";
        case 20: return "SIGTSTP";
        default: return "Unknown signal";
    }
}
unsigned long my_strtoul(const char* str, char** endptr, int base) {
    unsigned long result = 0;
    int digit;
    while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r') {
        str++;
    }
    if (base == 0 || base == 16) {
        if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
            str += 2;
            base = 16;
        } else if (base == 0) {
            if (str[0] == '0') {
                base = 8;
            } else {
                base = 10;
            }
        }
    }
    while (*str) {
        if (*str >= '0' && *str <= '9') {
            digit = *str - '0';
        } else if (*str >= 'a' && *str <= 'z') {
            digit = *str - 'a' + 10;
        } else if (*str >= 'A' && *str <= 'Z') {
            digit = *str - 'A' + 10;
        } else {
            break;
        }
        if (digit >= base) {
            break;
        }
        result = result * base + digit;
        str++;
    }
    if (endptr) {
        *endptr = (char*)str;
    }
    return result;
}
static char ip_str[16];
char* my_inet_ntoa(struct in_addr in) {
    unsigned char* bytes = (unsigned char*)&in.s_addr;
    for (int i = 0; i < 16; i++) {
        ip_str[i] = 0;
    }
    int pos = 0;
    for (int i = 0; i < 4; i++) {
        int value = bytes[i];
        char tmp[4];
        int tmp_pos = 0;
        if (value == 0) {
            tmp[tmp_pos++] = '0';
        } else {
            int div = 100;
            while (div > 0) {
                int digit = value / div;
                if (digit > 0 || tmp_pos > 0) {
                    tmp[tmp_pos++] = '0' + digit;
                    value %= div;
                }
                div /= 10;
            }
        }
        tmp[tmp_pos] = '\0';
        int j = 0;
        while (tmp[j]) {
            ip_str[pos++] = tmp[j++];
        }
        if (i < 3) {
            ip_str[pos++] = '.';
        }
    }
    ip_str[pos] = '\0';
    return ip_str;
} 
