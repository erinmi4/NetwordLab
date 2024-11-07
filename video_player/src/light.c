#include "light.h"
#include "ev.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>

unsigned int *plcd = NULL; // LCD???????

// ?????(x, y)????
int Display(int color, int x, int y)
{
    if (x >= 0 && x <= 800 && y >= 0 && y <= 480)
    {
        *(plcd + y * 800 + x) = color;
    }
    return 0;
}

// ???LCD
int Lcd_Init()
{
    int fd = open("/dev/fb0", O_RDWR);
    if (fd == -1)
    {
        perror("open error");
        return -1;
    }
    plcd = mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (plcd == MAP_FAILED)
    {
        perror("mmap error");
        close(fd);
        return -1;
    }
    return 0;
}

// ??????
void Dis_wh()
{
    for (int i = 0; i < 480; i++)
    {
        for (int j = 0; j < 800; j++)
        {
            Display(0xffffff, j, i);
        }
    }
}

// ????
void Dis_qu()
{
    for (int i = 100; i < 300; i++)
    {
        for (int j = 100; j < 600; j++)
        {
            Display(0xffffff, j, i);
        }
    }
}

// ??????
void Dis_cir()
{
    for (int i = 100; i < 480; i++)
    {
        for (int j = 100; j < 800; j++)
        {
            if ((j - 350)*(j - 350) + (i - 200)*(i - 200) <= 100 * 100)
                Display(0x00ffff, j, i);
            if ((j - 400)*(j - 400) + (i - 275)*(i - 275) <= 100 * 100)
                Display(0xff00ff, j, i);
            if ((j - 450)*(j - 450) + (i - 200)*(i - 200) <= 100 * 100)
                Display(0xffff00, j, i);
            if (((j - 350)*(j - 350) + (i - 200)*(i - 200) <= 100 * 100) && 
                ((j - 400)*(j - 400) + (i - 275)*(i - 275) <= 100 * 100) && 
                ((j - 450)*(j - 450) + (i - 200)*(i - 200) <= 100 * 100))
                Display(0xff0000, j, i);
        }
    }
}

// ?????
void Dis_tri()
{
    for (int i = 0; i < 480; i++)
    {
        for (int j = 0; j < 800; j++)
        {
            if (i + j <= 400)
                Display(0xff00ff, j, i);
        }
    }
}

// ???????????????
// int main()
// {
//     Lcd_Init();
//     Dis_wh();
//     //Dis_qu();
//     //Dis_cir();
//     Dis_tri();
//     return 0;
// }
