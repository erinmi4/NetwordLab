//
// Created by 25115 on 2024/11/8.
//

#ifndef PROJECT_LED_H
#define PROJECT_LED_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "System.h"

#define TEST_MAGIC 'x'                           //定义幻数
#define TEST_MAX_NR 2                            //定义命令的最大序数

//定义LED的魔幻数
#define LED1 _IO(TEST_MAGIC, 0)
#define LED2 _IO(TEST_MAGIC, 1)
#define LED3 _IO(TEST_MAGIC, 2)
#define LED4 _IO(TEST_MAGIC, 3)

void LED_CONT_ON(void);//控制开启4个LED
void LED_CONT_OFF(void);//控制关闭4个LED
void BEEP_Test(void);//控制蜂鸣器响三声

#endif //PROJECT_LED_H
