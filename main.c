//
// Created by 25115 on 2024/10/29.
//

#include <sys/mman.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "draw.h"
#include <stdlib.h>
#include <linux/input.h>
#include "touch.h"
int main(){

    int fsdf = Init_touch();

    Get_touch_direction(fsdf);

    touch_close(fsdf);
}