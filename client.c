//
// Created by 25115 on 2024/11/3.
//

#include "client.h"
#include <arpa/inet.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define BUFFER_SIZ (4 * 1024) // 4k 的数据区域
#define PORT 6666 // 根据你服务器进程绑定的端口号修改
#define HOST "127.0.0.1"
int main()
{
    // 1)socket 创建一个套接字
     int sockfd = socket(AF_INET,SOCK_STREAM,0);
     if(sockfd == -1){
         printf("socket create fail\n");
         exit(sockfd);
     }
     printf("socket create success\n");
    //先定义一个结构体来设置服务器的IP地址,再进行绑定,就是跟服务器代码中的那个设置一样
     //IP协议地址结构体
    struct sockaddr_in{
        sa_family_t sin_family; //指定协议族
        u_int16_t sin_port; //端口
        struct in_addr sin_addr;    //ip地址
    };
    //设置IPV4网络地址
     struct sockaddr_in addr;    //定义IPV4结构体变量
     addr.sin_family = AF_INET;
     addr.sin_port = htons(PORT);    //指定端口 转为网络字节序
     inet_aton(HOST,&(addr.sin_addr));//十分地址转换。

    // 3)connect 连接服务器进行通信
    ret = connect(sockfd,(struct sockaddr *)&addr,sizeof(addr));
    if(ret != 0){
        printf("connect error\n");
        exit(ret);
    }

    printf("connect server success...\n");


    // 4)read/write 数据的收发 while(1)
    char buffer[BUFFER_SIZ]; //用于保存输入的文本
    while(1){
        int len = read(sockfd,buffer,1024);
        if(len > 0){
            printf("server say: %s\n",buffer);
        }
        else{
            printf("server exit\n");
            break;
        }
    }
    printf("client read over    \n");

    // 5)close
    int clo = close(sockfd);
    if(clo != 0){
        printf("close error\n");
        exit(clo);
    }
}


