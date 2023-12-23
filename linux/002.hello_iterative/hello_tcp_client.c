#include "../common.h"

#define SERVER_PORT 9000
#define BUFSIZE     512

char *SERVER_IP = (char*)"127.0.0.1";

int main(int argc, char* argv[]){
    int sock;
    struct sockaddr_in serv_addr;
    char message[BUFSIZE];
    int send_len = 0, recv_len = 0, recv_cnt = 0;
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

        send_len = write(sock, message, strlen(message));

        // read data from server as sent size
        recv_len = 0;
        while(recv_len < send_len) {
            recv_cnt = read(sock, &message[recv_len], BUFSIZE-1);
            if (recv_cnt == -1) {
                err_handling("read() error..!!");
            }
            recv_len += recv_cnt;
        }

        message[recv_len] = 0;
        printf("Message from server: %s", message);
    }

    close(sock);

    return 0;
}
