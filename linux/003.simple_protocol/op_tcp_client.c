#include "../common.h"

#define SERVER_PORT 9000
#define BUFSIZE     512

#define OPERAND_SIZE     1
#define OPERATOR_SIZE    1

char *SERVER_IP = (char*)"127.0.0.1";

int main(int argc, char* argv[]){
    int sock;
    struct sockaddr_in serv_addr;

    char msg[BUFSIZE];
    int result = 0, operand_cnt = 0, i = 0;
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

    // protocol에 맞게 data 처리
    // operand_cnt: 1byte
    // operand: operand_cnt * sizeof(int) byte
    // op_code: 1byte
    fputs("input Operand count: ", stdout);
    scanf("%d", &operand_cnt);
    msg[0] = (char)operand_cnt;

    for(i = 0; i < operand_cnt; i++) {
        printf("input Operand %d: ", i+1);
        scanf("%d", (int*)&msg[OPERAND_SIZE + (i*sizeof(int))]);
    }
    
    fgetc(stdin);   // remove '\n' in the buffer previous input..
    fputs("input Operator(+, -, *): ", stdout);
    scanf("%c", &msg[OPERAND_SIZE + (operand_cnt * sizeof(int))]);

    /*
    printf("%d \n", (int)msg[0]);
    for (i = 0; i < operand_cnt; i++) {
        printf("%d ", msg[1+ (i*sizeof(int))]);
    }
    printf("\n");
    printf("%c\n", msg[1 + (operand_cnt * sizeof(int))]);
    */

    write(sock, msg, OPERAND_SIZE + (operand_cnt * sizeof(int)) + OPERATOR_SIZE);
    read(sock, &result, sizeof(int));

    printf("Operation result: %d \n", result);
    close(sock);

    return 0;
}
