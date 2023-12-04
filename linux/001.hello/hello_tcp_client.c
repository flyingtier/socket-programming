#include "../common.h"

#define SERVER_PORT 9000
#define BUFSIZE     512

char *SERVER_IP = (char*)"127.0.0.1";

int main(int argc, char* argv[]){
    int sock;
    struct sockaddr_in serv_addr;
    char message[BUFSIZE];
    int str_len = 0, read_len = 0;
    int index = 0;
    
    if (argc > 1) {
        SERVER_IP = argv[1];
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        err_handling("socket() error..");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serv_addr.sin_port = htons(SERVER_PORT);

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == INVALID_SOCKET) {
        err_handling("connect() error.. ");
    }

#if 0
    // original code to read data from server.
    str_len = read(sock, message, sizeof(message)-1);
    if (str_len < 0) {
        err_handling("read() error.. ");
    }
#else
    // TCP Socket doesn't have boundary..
    // server write data 1 time, but client can read data several times.
    while (read_len = read(sock, &message[index++], 1)) {
        if (read_len < 0) {
            err_handling("read() error.. ");
        }
        printf("read_len: %d, str_len: %d.. \n", read_len, str_len);
        str_len += read_len;
    }
#endif

    printf("Meesage from Server: %s \n", message);

    close(sock);

    return 0;
}
