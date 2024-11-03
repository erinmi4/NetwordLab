//
// Created by 25115 on 2024/11/3.
//

#include "server.h"
#include <arpa/inet.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_buff 10*1024
#define PORT 6666 // 根据你服务器进程绑定的端口号修改
#define HOST "192.168.28.137"
int main()
{
    // 1)socket 创建一个套接字
     int sockfd = socket(AF_INET,SOCK_STREAM,0);
     if(sockfd == -1){
         printf("socket create fail\n");
         exit(sockfd);
     }
     printf("socket create success\n");
     //IP协议地址结构体
    struct sockaddr_in{
        sa_family_t sin_family; //指定协议族
        u_int16_t sin_port; //端口
        struct in_addr sin_addr;    //ip地址
    };
    //设置IPV4网络地址 // assign IP, PORT
     struct sockaddr_in addr;    //定义IPV4结构体变量
     addr.sin_family = AF_INET;
     addr.sin_port = htons(PORT);    //指定端口 转为网络字节序
     inet_aton(HOST,&(addr.sin_addr));//十分地址转换。

    // 2)bind 绑定服务器的本身的网络地址
    int ret = bind(sockfd,(struct sockaddr *)&addr,sizeof(addr));
    if(ret != 0){
        printf("bind error\n");
        exit(ret);
    }
    printf("bind success\n");
    // 3)listen 进入监听模式
    int lis = listen(sockfd,5);//backlog:同时处理的个数,超过等待队列的个数都会被直接拒绝
    if(lis != 0){
        printf("listen error\n");
        exit(lis);
    }
    printf("listen success\n");
    // 4)accept 等待连接 使用while(1)
    int link_socket;
    while (!link_socket){
        link_socket = accept(sockfd,NULL,NULL);//设置为NULL不想得到该值
    }
    printf("accept success\n");
    // 5)read/write 数据的收发
    char buf[MAX_buff] = "Hello world";
    int write_len = write(sockfd,buf,sizeof(buf));
    if(write_len == -1){
        printf("write error\n");
        exit(write_len);
    }
    printf("write success\n");
    // 6)close     关闭服务器桃姐字的描述符
    int clo = close(sockfd);
    if(clo != 0){
        printf("close error\n");
        exit(clo);
    }
    return 0;
}