#include "client.h"
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZ 255
#define PORT 6666
#define HOST "127.0.0.1"

int main() {
    char wbuf[BUFFER_SIZ];
    char rbuf[BUFFER_SIZ];

    // 1) 创建一个套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket create fail");
        exit(EXIT_FAILURE);
    }
    printf("socket create success\n");

    // 2) 设置服务器地址
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);

    // 转换 IP 地址并检查错误
    if (inet_aton(HOST, &(addr.sin_addr)) == 0) {
        perror("Invalid IP address");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // 3) 连接服务器
    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
        perror("connect error");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("connect server success...\n");

    // 4) 数据接收与发送
    while (1) {
        // 接收服务器消息
        memset(rbuf, 0, sizeof(rbuf));
        int rsize = read(sockfd, rbuf, sizeof(rbuf) - 1);
        if (rsize <= 0) {
            printf("Connection closed by server\n");
            break;
        }
        printf("server: %s\n", rbuf);

        // 发送消息给服务器
        printf("请输入消息：");
        fflush(stdout);  // 清除输出缓冲区的内容
        memset(wbuf, 0, sizeof(wbuf));
        scanf("%s", wbuf);  // 从键盘输入待发送的消息

        rsize = write(sockfd, wbuf, strlen(wbuf));
        if (rsize == -1) {
            perror("write fail");
            break;
        }

        // 如果输入的是"bye"，则退出
        if (strcmp(wbuf, "bye") == 0) {
            printf("Closing connection...\n");
            break;
        }
    }

    // 5) 关闭套接字
    if (close(sockfd) != 0) {
        perror("close error");
        exit(EXIT_FAILURE);
    }

    return 0;
}
