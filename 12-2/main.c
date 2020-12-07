#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char** argv) {

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGPIPE);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    uint32_t address = inet_addr("127.0.0.1");
    uint16_t port = htons(atoi(argv[1]));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = address;
    addr.sin_port = port;

    int sock;
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("");
        exit(1);
    }

    int conn;
    if ((conn = connect(sock, (const struct sockaddr*) &addr, sizeof(struct sockaddr_in)) ) == -1) {
        perror("");
        exit(1);
    }


    int my, get;
    while(scanf("%d", &my) != EOF) {
        sendto(sock, &my, sizeof(int), 0,(const struct sockaddr *) &addr, sizeof(addr));
        recvfrom(sock, &get, sizeof(int), 0, NULL, NULL);
        printf("%d\n", get);
        fflush(stdout);
    }

    close(sock);

    return 0;
}
