#include "../common.h"

#define SERVER_PORT 9000
#define BUF_SIZE    512

int main(int argc, char *argv[]) {
    int s_sock, c_sock;
    struct sockaddr_in s_addr, c_addr;
    socklen_t c_addr_size;

    char message[BUF_SIZE];
    int str_len;

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

    c_addr_size = sizeof(c_addr);

    for (int i = 0; i < 5; i++) {
        c_sock = accept(s_sock, (struct sockaddr*)&c_addr, &c_addr_size);
        if (c_sock == INVALID_SOCKET) {
            err_handling("accept() error..");
        } else {
            printf("Connected client %d\n", i+1);
        }

        while ((str_len = read(c_sock, message, BUF_SIZE)) != 0) {
            write(c_sock, message, str_len);
        }

        close(c_sock);
    }

    close(s_sock);
    return 0;
}
