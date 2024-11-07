#include "Album.h"

int AUTO_CON = 0; // 自动播放控制标志位
void *auto_exit;

/*------------------- Album_Start 函数 ---------------
   开启相册功能
   输入参数：
        Touch       触摸屏结构体指针，获取坐标值和操作状态
        LCD         LCD结构体指针，用于操作LCD显示
        File_Photo  显示图片的文件目录指针
        File_System 系统文件目录结构体指针，打开界面相关图片
        count       获取网络通信控制数字指针
   返 回 值：无
*/
void Album_Start(struct Touch_val *Touch, struct Lcd_Init *LCD, struct Filedir *File_Photo, 
                 struct Filedir *File_System, int *count, int *Control_Num)
{
    LCD_bmp_X_Y(LCD, File_System->FilePath[BMPPHOTO_TIP], Touch->x, Touch->y); // 显示相册操作提示图
    Clear_Touch_States(Touch); // 清除所有标志位
    *Control_Num = CONT_INIT; // 清除控制标志位

    // 等待触摸屏操作，触摸后退出提示界面
    Wait_For_Touch_Release(Touch, Control_Num);

    LCD_BMPDisplay(LCD, File_Photo->FilePath[*count], DISPLAY_NODIR, NO_SPEED); // 显示当前图片

    // 相册功能主循环
    while (1)
    {
        usleep(2000); // 延时一小会

        // 处理上一张图片
        if ((Touch->move_dir == TOUCH_RIGHT && Touch->Touch_leave == 1) || (*Control_Num) == MUSIC_PREV)
        {
            Clear_Touch_States(Touch);
            *Control_Num = CONT_INIT;
            (*count)--;

            if (*count < 0) // 如果已经到第一张了，则去到最后一张
                *count = File_Photo->FileNum - 1;

            printf("Last Photo\n");
            printf("now the PhotoNum is %d\n", *count);
            printf("now the Photo's url is :%s\n", File_Photo->FilePath[*count]);
            LCD_BMPDisplay(LCD, File_Photo->FilePath[*count], DISPLAY_LEFT, VERY_FAST); // 显示当前图片
        }
        // 处理下一张图片
        else if ((Touch->move_dir == TOUCH_LEFT && Touch->Touch_leave == 1) || (*Control_Num) == MUSIC_NEXT)
        {
            Clear_Touch_States(Touch);
            *Control_Num = CONT_INIT;
            (*count)++;

            if (*count > File_Photo->FileNum - 1) // 如果已经到最后一张了，则回到第一张
                *count = 0;

            printf("Next Photo\n");
            printf("now the PhotoNum is %d\n", *count);
            printf("now the Photo's url is :%s\n", File_Photo->FilePath[*count]);
            LCD_BMPDisplay(LCD, File_Photo->FilePath[*count], DISPLAY_RIGHT, VERY_FAST); // 显示当前图片
        }
        // 进入自动播放模式
        else if ((Touch->move_dir == TOUCH_DOWN && Touch->Touch_leave == 1) || (*Control_Num) == MUSIC_STOP_CONT)
        {
            *Control_Num = CONT_INIT;
            struct AUTO_ON_OFF *AUTO = calloc(1, sizeof(struct AUTO_ON_OFF)); // 创建自动播放记录结构体
            AUTO->FileNum = File_Photo->FileNum; 
            AUTO->count = count;
            Clear_Touch_States(Touch);
            printf("Auto Play mode\n");

            AUTO_CON = 1; // 设置为自动播放模式
            if (AUTO_CON == 1)
            {
                pthread_t AUTO_pid; // 创建自动播放计数线程
                pthread_create(&AUTO_pid, NULL, Auto_Num, (void *)AUTO);
            }

            // 自动播放的图片显示循环
            while (1)
            {
                LCD_BMPDisplay(LCD, File_Photo->FilePath[*count], DISPLAY_RIGHT, VERY_FAST); // 显示当前图片
                if ((Touch->move_dir == TOUCH_DOWN && Touch->Touch_leave == 1) || (*Control_Num) == MUSIC_STOP_CONT)
                {
                    Clear_Touch_States(Touch);
                    *Control_Num = CONT_INIT;
                    printf("Out of Auto Play mode\n");
                    AUTO_CON = 0; // 退出自动播放模式
                    break;
                }
                else if (Touch->move_dir != TOUCH_INIT && Touch->Touch_leave == 1)
                {
                    Clear_Touch_States(Touch); // 清除多余的操作
                }
            }
        }
        // 返回主菜单
        else if ((Touch->move_dir == TOUCH_UP && Touch->Touch_leave == 1) || (*Control_Num) == BACK)
        {
            *Control_Num = CONT_INIT;
            Clear_Touch_States(Touch);
            printf("Quit\n");
            LCD_BMPDisplay(LCD, File_System->FilePath[BACKGROUND_NUM], DISPLAY_DOWN, FAST); // 返回主菜单
            break;
        }
        // 错误操作处理
        else if (Touch->move_dir != TOUCH_INIT && Touch->Touch_leave == 1)
        {
            Clear_Touch_States(Touch); // 清除所有标志位
        }
    }
}

/*------------------- Auto_Num 函数 -------------------
   自动播放模式下的数字自加线程
   输入参数：
        arg - 对应结构体指针 AUTO_ON_OFF，包含图片数量和当前播放到的图片
   返回值：无
*/
void *Auto_Num(void *arg)
{
    struct AUTO_ON_OFF *AUTO = arg;
    while (1)
    {
        if (AUTO_CON == 0) // 如果收到退出信号
        {
            break;
        }
        sleep(3);
        (*(AUTO->count))++; // 增加播放图片的索引
        if (*(AUTO->count) > (AUTO->FileNum - 1)) // 如果已经到最后一张，回到第一张
        {
            (*(AUTO->count)) = 0;
        }
    }
    pthread_exit(auto_exit); // 退出线程
}

/*------------------- Start_System 函数 -------------------
   开机显示动画
   输入参数：
        LCD - LCD结构体指针，用于操作LCD的显示
   返回值：无
*/
void Start_System(struct Lcd_Init *LCD)
{
    int Display_Num = 1;
    char StartPath[45];
    while (Display_Num <= 34)
    {
        usleep(13000);
        sprintf(StartPath, "%sb%d.bmp", START_URL, Display_Num++);
        LCD_BMPDisplay(LCD, StartPath, DISPLAY_NODIR, NO_SPEED); // 显示启动动画
    }
}

/*------------------- 清除触摸状态的辅助函数 -------------------*/
void Clear_Touch_States(struct Touch_val *Touch)
{
    Touch->move_dir = Touch->x = Touch->y = Touch->Touch_leave = TOUCH_INIT; // 清除触摸屏所有标志位
}

/*------------------- 等待触摸操作释放的辅助函数 -------------------*/
void Wait_For_Touch_Release(struct Touch_val *Touch, int *Control_Num)
{
    while (1)
    {
        if ((Touch->x != 0 && Touch->y != 0 && Touch->Touch_leave == 1) || (*Control_Num) != CONT_INIT)
        {
            Touch->x = Touch->y = Touch->Touch_leave = 0; // 清除标志位
            *Control_Num = CONT_INIT; // 清除控制标志位
            break;
        }
    }
}
