#include "../common.h"

#define SERVER_PORT 9000
#define BUF_SIZE    512

int main(int argc, char *argv[]) {
    int s_sock;
    socklen_t c_addr_size;
    struct sockaddr_in s_addr, c_addr;

    char message[BUF_SIZE];
    int str_len;

    // socket 생성 시, SOCK_DGRAM 사용
    s_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (s_sock == INVALID_SOCKET) {
        err_handling("UDP socket create error!!");
    }

    // server 주소 설정
    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s_addr.sin_port = htons(SERVER_PORT);

    // client에 상관 없이 bind 시 할당되는 주소(s_addr)로 전달되는 모든 데이터 수신..
    if (bind(s_sock, (struct sockaddr*)&s_addr, sizeof(s_addr)) == INVALID_SOCKET) {
        err_handling("bind error..");
    }

    // udp의 경우, listen, accept는 필요 없음.
    // recvfrom(), sendto() 사용.. sys/socket.h
    while(1) {
        c_addr_size = sizeof(c_addr);
        str_len = recvfrom(s_sock, message, BUF_SIZE, 0, (struct sockaddr*)&c_addr, &c_addr_size);
        sendto(s_sock, message, str_len, 0, (struct sockaddr*)&c_addr, c_addr_size);
    }

    close(s_sock);
    return 0;
}


