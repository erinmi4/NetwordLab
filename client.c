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

int main()
{
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

    // 4) 数据接收

    while (1) {
        memset(rbuf, 0, BUFFER_SIZ); // 清空缓冲区
        int len = read(sockfd, rbuf, BUFFER_SIZ - 1); // 读取最多 4KB 数据
        if (len > 0) {
            printf("server say: %s\n", rbuf);
        } else if (len == 0) {
            printf("server closed connection\n");
            break;
        } else {
            perror("read error");
            break;
        }
    }
    printf("client read over\n");

    // 5) 关闭套接字
    if (close(sockfd) != 0) {
        perror("close error");
        exit(EXIT_FAILURE);
    }

    return 0;
}
