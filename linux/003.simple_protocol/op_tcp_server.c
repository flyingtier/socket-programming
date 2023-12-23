#include "../common.h"

#define SERVER_PORT 9000
#define BUF_SIZE    512

int calc(int operand_cnt, int oprands[], char op_code);

int main(int argc, char *argv[]) {
    int s_sock, c_sock;
    struct sockaddr_in s_addr, c_addr;
    socklen_t c_addr_size;

    char message[BUF_SIZE];
    int result = 0, operand_cnt = 0, i = 0;
    int recv_cnt = 0, recv_len = 0;

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

        // protocol에 맞게 data를 받아 처리
        // operand_cnt: 1byte
        // operand: operand_cnt * sizeof(int) byte
        // op_code: 1byte
        operand_cnt = 0;
        read(c_sock, &operand_cnt, 1);

        recv_len = 0;
        while((operand_cnt*sizeof(int) + 1) > recv_len) {
            recv_cnt = read(c_sock, &message[recv_len], BUF_SIZE-1);
            recv_len += recv_cnt;
        }

        // calculate
        result = calc(operand_cnt, (int*)message, message[recv_len-1]);
        write(c_sock, (char*)&result, sizeof(result));
        close(c_sock);
    }

    close(s_sock);
    return 0;
}

int calc(int operand_cnt, int oprands[], char op_code) {
    int result = oprands[0], i;

    switch(op_code) {
        case '+':
            for(i = 1; i < operand_cnt; i++) {
                result += oprands[i];
            }
            break;
        case '-':
            for(i = 1; i < operand_cnt; i++) {
                result -= oprands[i];
            }
        case '*':
            for(i = 1; i < operand_cnt; i++) {
                result *= oprands[i];
            }
    }

    printf("operand_cnt: %d, op_code: %c, result: %d \n", operand_cnt, op_code, result);
    return result;
}
