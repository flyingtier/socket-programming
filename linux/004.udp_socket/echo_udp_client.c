#include "../common.h"

#define SERVER_PORT 9000
#define BUFSIZE     512

char *SERVER_IP = (char*)"127.0.0.1";

int main(int argc, char* argv[]){
    int sock;
    socklen_t addr_size;
    struct sockaddr_in s_addr, from_addr;

    char message[BUFSIZE];
    int str_len = 0;

    if (argc > 1) {
        SERVER_IP = argv[1];
    }

    // socket 생성 시, SOCK_DGRAM 사용
    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        err_handling("socket() error..");
    }

    // data를 전송하려는 server 주소 설정
    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    s_addr.sin_port = htons(SERVER_PORT);

    while(1) {
        fputs("Insert messages(q to Quit): ", stdout);
        fgets(message, sizeof(message), stdin);

        if ((!strcmp(message, "q\n")) || (!strcmp(message, "Q\n"))) {
            break;
        }

        // connect 없이, sendto()로 server에 data 전송
        sendto(sock, message, strlen(message), 0, (struct sockaddr*)&s_addr, sizeof(s_addr));

        // from_addr로 부터 data 수신
        addr_size = sizeof(from_addr);
        str_len = recvfrom(sock, message, BUFSIZE, 0, (struct sockaddr*)&from_addr, &addr_size);
        message[str_len] = 0;

        printf("Message from server: %s\n", message);
    }

    close(sock);
    return 0;
}
