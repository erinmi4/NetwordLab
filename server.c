#include "server.h"
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_buff 255
#define PORT 6666
#define HOST "0.0.0.0"


int main()
{
    char rbuf[MAX_buff] ={0} ;
    char wbuf[MAX_buff] = "I've received";
    // 1) 创建一个套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket create fail");
        exit(EXIT_FAILURE);
    }
    printf("socket create success\n");

    // 允许端口复用，避免 "Address already in use" 错误
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 2) 设置IPV4网络地址
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    if (inet_aton(HOST, &(addr.sin_addr)) == 0) {
        perror("Invalid IP address");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // 3) 绑定服务器的网络地址
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
        perror("bind error");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("bind success\n");

    // 4) 进入监听模式
    if (listen(sockfd, 5) != 0) {
        perror("listen error");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("listen success\n");
    while(1) //确保当一个客户端如果断开了连接,那么还可以等待下一次客户端的连接
    {// 5) 等待连接
        int link_socket = accept(sockfd, NULL, NULL);
        if (link_socket < 0) {
            perror("accept error");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        printf("已经有客户端连接成功\n");

        // 6) 数据的发送
        while(1)//保障本次连接的通信会一直持续
        {
            //write写给客户端
            int write_len = write(link_socket, wbuf, strlen(wbuf));
            if (write_len == -1) {
                perror("write error");
                close(link_socket);
                close(sockfd);
                exit(EXIT_FAILURE);
            }
            printf("write success\n");

            //使用read来接受客户端的信息
            memset(rbuf,0,sizeof(rbuf));
            int rsize = read(link_socket,rbuf,sizeof(rbuf));//接受客户端的信息
            if(rsize <= 0)
            {
                printf("read fail\n");
                close(link_socket);
                close(sockfd);
                return 0;
            }
            printf("client:%s\n",rbuf);

            //如果客户端发送一个bye过来,那么连接就结束了
            if(strcmp(rbuf,"bye") == 0)
            {
                close(link_socket);
                break;
            }
        }
    }

    // 7) 关闭套接字
    close(sockfd);

    return 0;
}
