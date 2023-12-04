#include "../common.h"

#define SERVER_PORT 9000
char message[] = "Hello, World";

int main(int argc, char *argv[]) {
    int s_sock, c_sock;
    struct sockaddr_in s_addr, c_addr;
    socklen_t c_addr_size;

    /*
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }
    */

    s_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (s_sock == INVALID_SOCKET) {
        err_handling("socket() error..");
    }

    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s_addr.sin_port = htons(SERVER_PORT);

    if (bind(s_sock, (struct sockaddr*)&s_addr, sizeof(s_addr)) == INVALID_SOCKET) {
        err_handling("bind() error.. ");
    }

    if (listen(s_sock, 5) == INVALID_SOCKET) {
        err_handling("listen() error.. ");
    }

    //while(1) {
    c_addr_size = sizeof(c_addr);
    c_sock = accept(s_sock, (struct sockaddr*)&c_addr, &c_addr_size);
    if (c_sock == INVALID_SOCKET) {
        err_handling("accept() error..");
    }

    write(c_sock, message, sizeof(message));
    close(c_sock);
    //}

    close(s_sock);
    return 0;
}
