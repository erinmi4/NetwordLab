#include <sys/types.h>          /* See NOTES */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <math.h>

#define CON2 "/dev/ttySAC1"
#define CON3 "/dev/ttySAC2"
#define CON4 "/dev/ttySAC3"

#define V_THRESHOLD 2000  // 设定门槛值，单位为ADC值

//串口初始化的函数 参数是串口设备的文件描述符
void init_tty(int fd)
{    
    //声明设置串口的结构体
    struct termios termios_new;
    //先清空该结构体
    bzero( &termios_new, sizeof(termios_new));
    //	cfmakeraw()设置终端属性，就是设置termios结构中的各个参数。
    cfmakeraw(&termios_new);
    //设置波特率
    //termios_new.c_cflag=(B9600);
    cfsetispeed(&termios_new, B9600);
    cfsetospeed(&termios_new, B9600);
    //CLOCAL和CREAD分别用于本地连接和接受使能，因此，首先要通过位掩码的方式激活这两个选项。    
    termios_new.c_cflag |= CLOCAL | CREAD;
    //通过掩码设置数据位为8位
    termios_new.c_cflag &= ~CSIZE;
    termios_new.c_cflag |= CS8; 
    //设置无奇偶校验
    termios_new.c_cflag &= ~PARENB;
    //一位停止位
    termios_new.c_cflag &= ~CSTOPB;
    tcflush(fd,TCIFLUSH);
    // 可设置接收字符和等待时间，无特殊要求可以将其设置为0
    termios_new.c_cc[VTIME] = 10;
    termios_new.c_cc[VMIN] = 1;
    // 用于清空输入/输出缓冲区
        tcflush (fd, TCIFLUSH);
    //完成配置后，可以使用以下函数激活串口设置
    if(tcsetattr(fd,TCSANOW,&termios_new) )
        printf("Setting the serial1 failed!\n");
}

void gy39_getlux()
{
    //打开GY39的文件描述符
    int gy39_fd = open(CON3,O_RDWR);
    if(gy39_fd == -1)
    {
        printf("open gy39 fail\n");
        return;
    }
    //串口初始化
    init_tty(gy39_fd);

    //GY39的配置
    unsigned char wbuf[3] = {0xa5,0x81,0x26};

    //发送指令给GY39
    int ret = write(gy39_fd,wbuf,3);
    if(ret != 3)
    {
        sleep(1);
    }

    //接受数据
    unsigned char rbuf[9] = {0};
    ret = read(gy39_fd,rbuf,9);
    if(ret != 9)
    {
        printf("read data error\n");
    }
    int lux = 0;

    //获取数据
    //判断数据格式是否正确
    if(rbuf[2] == 0x15 && rbuf[0] == 0x5a && rbuf[1] == 0x5a)
    {
        lux = rbuf[4]<<24|rbuf[5]<<16|rbuf[6]<<8|rbuf[7];
        lux = lux/100;
        printf("lux ====== %d\n",lux);
    }

}

void MQ2_getdata()
{
    int mq2_fd = open(CON4,O_RDWR);
    if(mq2_fd == -1){
        printf("open mq2 fail\n");
    }
    char smoke_buf[9] = {0xff,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
    char smok_rbuf[9];
    write(mq2_fd,smoke_buf,9);
    read(mq2_fd,smok_rbuf,9);
    if(smok_rbuf[0] != 0xff) return;
    
    int smoke = smok_rbuf[2]<<8|smok_rbuf[3];
    printf("smoke ====== %d\n",smoke);
}

int main()
{
    while(1)
    {
        MQ2_getdata();
        sleep(1);
    }
    return 0;
}