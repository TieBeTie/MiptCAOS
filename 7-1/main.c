#define _XOPEN_SOURCE
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define BUFF_SIZE 20

int main() {
    struct tm time_prev;
    struct tm time_now;
    memset(&time_prev, sizeof(struct tm), 0);
    char buff[BUFF_SIZE];
    int has_prev = 0;
    while (fgets(buff, sizeof(buff), stdin)) {
       char *end = memchr(buff, '\n', sizeof(buff));
       *end = '\0';
       memset(&time_now, sizeof(struct tm), 0);
       strptime(buff, "%Y-%m-%d %H:%M", &time_now);
       if (has_prev != 0) {
           time_t unix_time_now = mktime(&time_now);
           time_t unix_time_prev = mktime(&time_prev);
           printf("%ld\n", (unix_time_now - unix_time_prev) / 60);
           time_prev = time_now;
       } else {
           time_prev = time_now;
           has_prev = 1;
       }
    }
    return 0;
}