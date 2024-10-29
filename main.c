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

int main(){
    init_lcd();
    draw_circle(400, 240, 100, RED_COLOR);
    close_lcd();
}