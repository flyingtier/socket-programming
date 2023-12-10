#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>         // open, close, write, read
#include <sys/socket.h>     // socket, bind, listen, accept, connect
#include <arpa/inet.h>      // inet_addr, inet_aton, inet_ntoa

#define SOCKET_ERROR    -1
#define INVALID_SOCKET  -1

void err_handling(const char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
