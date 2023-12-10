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
    } else {
        printf("Connected...... \n");
    }

    while(1) {
        fputs("Input message(Q to quit): ", stdout);
        fgets(message, BUFSIZE, stdin);

        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;

        write(sock, message, strlen(message));
        str_len = read(sock, message, BUFSIZE-1);
        message[str_len] = 0;
        printf("Message from server: %s", message);
    }

    close(sock);

    return 0;
}
