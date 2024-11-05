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
    int mq2_fd = open(CON3, O_RDWR);
    if (mq2_fd == -1) {
        printf("open mq2 fail\n");
        return;
    }
    //串口初始化
    init_tty(mq2_fd);
    
    char smoke_buf[9] = {0xff, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
    char smok_rbuf[9] = {0};
    
    if (write(mq2_fd, smoke_buf, 9) != 9) {
        printf("write to mq2 failed\n");
        close(mq2_fd);
        return;
    }
    
    if (read(mq2_fd, smok_rbuf, 9) != 9) {
        printf("read from mq2 failed\n");
        close(mq2_fd);
        return;
    }
    
    if (smok_rbuf[0] != 0xff) {
        close(mq2_fd);
        return;
    }

    int smoke = (smok_rbuf[2] << 8) | smok_rbuf[3];
    printf("smoke ====== %d\n", smoke);

    //close(mq2_fd);  // 关闭文件描述符
}

//US-100超声波测距模块可实现2cm~4.5m的非接触测距功能
void us100_getdata()
{
    int us100_fd = open(CON3, O_RDWR);
    //串口初始化
    init_tty(us100_fd);
    if (us100_fd == -1) {
        printf("open us100 fail\n");
        return;
    }
    //输入0x55,系统会发出8个超声波脉冲，检测回波信号
    printf("Begin detect distance:\n");
    char data[1] = {0x55};
    int i = write(us100_fd, &data, 1);
    if (i != 1) {
        printf("write to us100 failed\n");
        close(us100_fd);
        return;
    }
    printf("%d\n",__LINE__);
    char distance_data[2] = {0};
    int j = read(us100_fd, distance_data, 2);
    if (j != 2) {
        printf("read from us100 failed\n");
        close(us100_fd);
        return;
    }
    
    printf("%d\n",__LINE__);

    int distance = distance_data[0] << 8 | distance_data[1]; //mm
    distance = distance / 1000;//转为米

    printf("distance:%d\n", distance);

    //获取温度
    char temdata[1] = {0x50};
    int m = write(us100_fd, &temdata, 1);
    if (m != 1) {
        printf("write to us100 failed\n");
        close(us100_fd);
        return;
    }
    char temperature_data[1] = {0};
    int n = read(us100_fd, temperature_data, 1);
    if (n != 1) {
        printf("read from us100 failed\n");
        close(us100_fd);
        return;
    }
    int temperature = temperature_data[0] - 45;
    printf("temperature:%d\n", temperature);
}

int main()
{
    while(1)
    {
        gy39_getlux();
        //MQ2_getdata();
        //us100_getdata();
        sleep(1);
    }
    return 0;
}