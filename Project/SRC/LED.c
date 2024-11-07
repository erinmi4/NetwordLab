//
// Created by 25115 on 2024/11/8.
//

#include "../INC/LED.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>

/*
    函 数 名：LED_CONT_ON
    作    用：控制开发板的4个LED显示
    输入参数：无
    返    回：无
*/
void LED_CONT_ON() {
    int fd = open("/dev/Led", O_RDWR);  // 打开设备下的LED
    if (fd < 0) {
        perror("无法打开 /dev/LED");
        return;
    }
    ioctl(fd, LED1, 0);  // 打开 LED1
    ioctl(fd, LED2, 0);  // 打开 LED2
    ioctl(fd, LED3, 0);  // 打开 LED3
    ioctl(fd, LED4, 0);  // 打开 LED4
    close(fd);           // 关闭文件描述符
}

/*
    函 数 名：LED_CONT_OFF
    作    用：控制开发板的4个LED关闭
    输入参数：无
    返    回：无
*/
void LED_CONT_OFF() {
    int fd = open("/dev/Led", O_RDWR);  // 打开设备下的LED
    if (fd < 0) {
        perror("无法打开 /dev/LED");
        return;
    }
    ioctl(fd, LED1, 1);  // 关闭 LED1
    ioctl(fd, LED2, 1);  // 关闭 LED2
    ioctl(fd, LED3, 1);  // 关闭 LED3
    ioctl(fd, LED4, 1);  // 关闭 LED4
    close(fd);           // 关闭文件描述符
}

/*
    函 数 名：BEEP_Test
    作    用：测试蜂鸣器，让蜂鸣器响一声
    输入参数：无
    返    回：无
*/
void BEEP_Test() {
    int fd = open("/dev/beep", O_RDWR);
    if (fd < 0) {
        perror("无法打开 /dev/beep");
        return;
    }
    ioctl(fd, 0, 1);  // 打开蜂鸣器
    usleep(65535);
    ioctl(fd, 1, 1);  // 关闭蜂鸣器
    usleep(65535);
    close(fd);        // 关闭文件描述符
}

