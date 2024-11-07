//
// Created by 25115 on 2024/11/7.
//

#include "../INC/draw.h"

/*
    函数名  ：LCD_Init
    作  用  ：初始化打开LCD相关文件
    输入参数：LCD结构体指针
    返 回 值：无
*/
void LCD_Init(struct Lcd_Init * LCD)
{
    LCD->fd_lcd = open(LCD_PATH , O_RDWR);//打开LCD设备文件
    if (-1 == LCD->fd_lcd)
    {
        perror("open LCD error"); //无法打开就报错
    }
    //2、 内存映射
    LCD->p_lcd = (int *)mmap(NULL,	//需要内存映射的起始地址(通常设为 NULL, 代表让系统自动选定地址)
					LCD_SIZE,  //需要多大的一片内存(一字节为单位) LCD显示屏800*480个像素点 每个像素点占4字节
					PROT_READ | PROT_WRITE,  //映射区域可被读取 映射区域可被写入
					MAP_SHARED,					//对应射区域的写入数据会复制回文件内
					LCD->fd_lcd, 		//需要内存映射的文件的文件描述符
					0);			//参数offset为文件映射的偏移量, 通常设置为0
    if ( MAP_FAILED == LCD->p_lcd )
    {
        perror("mmap error"); //无法配置就报错
    }
}

/*
    函 数 名：LCD_BMPDisplay
    作    用：在LCD上根据输入的方向和速度进行显示
    输入参数：
                LCD             结构体指针
                PhotoPath       图片路径
                Display_Type    显示模式
                Display_Speed   显示速度
    返    回：无
*/
void LCD_BMPDisplay(struct Lcd_Init * LCD, char * PhotoPath, int Display_Type, int Display_Speed) {
    // 1. 打开图片文件并跳过头部信息
    int fd_bmp = open(PhotoPath, O_RDONLY); // 打开图片，获取文件描述符
    if (fd_bmp == -1) {
        perror("open BMP error"); // 打开失败，输出错误信息
        return;
    }
    lseek(fd_bmp, 54, SEEK_SET); // 跳过BMP头信息

    // 2. 读取图像中的 BGR 颜色数据
    char buf_bmp[BMP_SIZE];
    int ret_val = read(fd_bmp, buf_bmp, BMP_SIZE);
    if (ret_val == -1) {
        perror("read BMP error"); // 读取失败，输出错误信息
        close(fd_bmp);
        return;
    }

    // 3. 将 BGR 数据转换为 ARGB 格式并存储到 buf_lcd
    int buf_lcd[H][W];
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            buf_lcd[y][x] = buf_bmp[(x + y * W) * 3 + 0] << 0 |
                            buf_bmp[(x + y * W) * 3 + 1] << 8 |
                            buf_bmp[(x + y * W) * 3 + 2] << 16;
        }
    }

    // 4. 显示图片数据到 LCD，根据不同的显示模式和速度进行操作
    int change, max_change;//change表示显示进度，max_change表示显示的最大进度值
    int direction_x = 0, direction_y = 0;

    switch (Display_Type) {
        case DISPLAY_LEFT:  // 从左至右显示
            max_change = W / Display_Speed;
            direction_x = 1;
            break;
        case DISPLAY_RIGHT: // 从右至左显示
            max_change = W / Display_Speed;
            direction_x = -1;
            change = max_change;
            break;
        case DISPLAY_UP:    // 从上至下显示
            max_change = H / Display_Speed;
            direction_y = 1;
            break;
        case DISPLAY_DOWN:  // 从下至上显示
            max_change = H / Display_Speed;
            direction_y = -1;
            change = max_change;
            break;
        case DISPLAY_NODIR: // 直接显示
            max_change = 1;
            direction_x = 0;
            direction_y = 0;
            break;
    }

    for (change = 0; change <= max_change; change += 1) {
        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W; x++) {
                if ((Display_Type == DISPLAY_LEFT || Display_Type == DISPLAY_RIGHT) &&
                    (x <= (Display_Speed * (change + 1)) && x >= (Display_Speed * change))) {
                    *(LCD->p_lcd + x + y * W) = buf_lcd[H - y][x];
                }
                else if ((Display_Type == DISPLAY_UP || Display_Type == DISPLAY_DOWN) &&
                         (y <= (Display_Speed * (change + 1)) && y >= (Display_Speed * change))) {
                    *(LCD->p_lcd + x + y * W) = buf_lcd[H - y][x];
                }
                else if (Display_Type == DISPLAY_NODIR) {
                    *(LCD->p_lcd + x + y * W) = buf_lcd[H - y][x];
                }
            }
        }
        if (direction_x != 0)
        {
            change += direction_x;
        }
        else if (direction_y != 0)
        {
            change += direction_y;
        }
    }

    // 5. 关闭图片文件，释放资源
    close(fd_bmp);
}


/*
    函数名  ：LCD_bmp_X_Y
    功   能：在触摸点处逐步扩散显示图片，用于触摸功能触发界面切换
    输入参数：LCD - LCD参数结构体指针
             PhotoPath - 要显示的图片路径
             Touch_x, Touch_y - 触摸屏的坐标
    返回值：成功返回0，失败返回-1
*/
void LCD_bmp_X_Y(struct Lcd_Init* LCD, char *PhotoPath, int Touch_x, int Touch_y)
{
    // 1. 打开图片文件
    int fd_bmp = open(PhotoPath, O_RDONLY);
    if (fd_bmp == -1) {
        perror("open BMP error");
        return;
    }
    lseek(fd_bmp, 54, SEEK_SET); // 跳过 BMP 头信息的 54 字节

    // 2. 读取图像中的 BGR 颜色数据
    char buf_bmp[BMP_SIZE];
    int ret_val = read(fd_bmp, buf_bmp, BMP_SIZE);

    // 3. 将 BGR 数据转换为 ARGB 格式（24位到32位）
    int buf_lcd[H][W];
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            buf_lcd[y][x] = buf_bmp[(x + y * W) * 3 + 0] << 0 |
                            buf_bmp[(x + y * W) * 3 + 1] << 8 |
                            buf_bmp[(x + y * W) * 3 + 2] << 16;
        }
    }

    // 4. 在 LCD 上扩散显示图片
    int change_x = Touch_x, change_x_ = Touch_x;
    int change_y = Touch_y, change_y_ = Touch_y;
    // 扩展的显示边界，用于逐步扩展显示范围
    int count_1 = 1, count_2 = 1, count_3 = 1, count_4 = 1;

    while (1) {
        // 更新扩展的显示边界
        if (change_x_ > 0) {
            change_x_ = Touch_x - (VERY_FAST * count_1++);
            if (change_x_ < 0) change_x_ = 0;
        }
        if (change_x < W) {
            change_x = Touch_x + (VERY_FAST * count_2++);
            if (change_x > W) change_x = W;
        }
        if (change_y_ > 0) {
            change_y_ = Touch_y - (FAST * count_3++);
            if (change_y_ < 0) change_y_ = 0;
        }
        if (change_y < H) {
            change_y = Touch_y + (FAST * count_4++);
            if (change_y > H) change_y = H;
        }

        // 将当前扩展区域的像素数据显示到 LCD
        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W; x++) {
                if (y <= change_y && y >= change_y_ && x <= change_x && x >= change_x_) {
                    *(LCD->p_lcd + x + y * W) = buf_lcd[H - y][x];
                }
            }
        }

        // 判断是否完成显示整个图片
        if (change_x_ <= 0 && change_x >= W && change_y_ <= 0 && change_y >= H) {
            break;
        }
    }

    // 5. 关闭文件，释放资源
    close(fd_bmp);
}

/*
    函数名  ：LCD_X_Y
    作  用  ：让图片在触摸部分扩散显示，主要用于点击功能时的界面切换
    输入参数：LCD         输入LCD参数相关结构体指针
              PhotoPath   输入需要显示的图片路径
              Touch_x，Touch_y  输入触摸屏的坐标
    返 回 值：成功操作返回0，失败返回-1
*/
int LCD_X_Y(struct Lcd_Init* LCD, char *PhotoPath, int Touch_x, int Touch_y) {
    // 1. 打开图片文件
    int fd_bmp = open(PhotoPath, O_RDONLY);
    if (fd_bmp == -1) {
        perror("open BMP error");
        return -1;
    }

    // 跳过BMP文件头（54字节）
    lseek(fd_bmp, 54, SEEK_SET);

    // 2. 读取图像中的BGR颜色数据
    char buf_bmp[BMP_SIZE];
    int ret_val = read(fd_bmp, buf_bmp, BMP_SIZE);
    if (ret_val == -1) {
        perror("read BMP error");
        close(fd_bmp);
        return -1;
    }

    // 3. 将图像中的BGR数据转换为ARGB格式（24位转32位）
    int buf_lcd[H][W];
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            buf_lcd[y][x] = (buf_bmp[(x + y * W) * 3 + 0] << 0)  |
                            (buf_bmp[(x + y * W) * 3 + 1] << 8)  |
                            (buf_bmp[(x + y * W) * 3 + 2] << 16);
        }
    }

    // 4. 将转换后的数据显示到LCD，带触摸扩散效果
    srand((int)time(0));  // 使用当前时间来初始化随机数生成器
    int rand_num = (rand() % 25 + 20);  // 最终 rand_num 的值会在 20 到 44 之间，用于控制触摸扩散区域的大小

    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            if ((y <= Touch_y + rand_num && y >= Touch_y - rand_num) &&
                (x <= Touch_x + rand_num && x >= Touch_x - rand_num)) {
                *(LCD->p_lcd + x + y * W) = buf_lcd[H - y][x];
            }
        }
    }

    // 5. 关闭文件并释放资源
    close(fd_bmp);
    return 0;
}

