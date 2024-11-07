#include "Touch.h"

/*
    函数名  ：dif_absolute
    作  用  ：获得a，b之间差值的绝对值
    输入参数：需要相减的两个参数
    返 回 值：两个数相减后的绝对值
*/
int dif_absolute(int a, int b)
{
    int result;
    if (a > b)
    { 
        result = a - b; 
    }
    if (a < b)
    { 
        result = b - a; 
    }
    return result;
}

/*
    函数名  ：Touch_Init
    作  用  ：初始化触摸屏
    输入参数：触摸屏结构体指针，因为是直接操作指针所以不需要返回值
    返 回 值：返回触摸屏文件的文件编号
*/
void Touch_Init(struct Touch_val *Touch)
{
    Touch->ts_fd = open(TOUCH_PATH, O_RDWR);  // 打开触摸屏
    if (Touch->ts_fd == -1)
    {
        perror("open ts failed");  // 打开失败时输出错误信息
        return;
    }
    return;
}

/*
    函数名  ：Touch_Scan
    作  用  ：扫描触摸屏的触摸情况
    输入参数：触摸屏结构体指针
    返 回 值：无
*/
void Touch_Scan(struct Touch_val *Touch)
{
    struct input_event buf; // 定义一个关于输入的结构体

    int Touch_x_before, Touch_x_dif, Touch_y_before, Touch_y_dif;
    
    // 初始化X、Y的初值和差值变量
    Touch_x_before = Touch_x_dif = Touch_y_before = Touch_y_dif = 0;

    while (1)  // 循环获取事件内容
    {
        bzero(&buf, sizeof(buf));  // 将缓冲区清零
        read(Touch->ts_fd, &buf, sizeof(buf));  // 读取触摸屏内容

        // 处理X轴坐标
        if (buf.type == EV_ABS && buf.code == ABS_X) 
        { 
            Touch->x = buf.value; 
        }

        // 处理Y轴坐标
        if (buf.type == EV_ABS && buf.code == ABS_Y) 
        { 
            Touch->y = buf.value; 
        }

        // 获取第一次按下时的坐标值
        if (buf.type == EV_KEY && buf.code == BTN_TOUCH && buf.value == 1)
        {
            Touch_x_before = Touch->x;  // 记录按下时的X坐标
            Touch_y_before = Touch->y;  // 记录按下时的Y坐标
        }

        // 判断是否发生移动
        if (Touch_x_before != 0 && Touch_y_before != 0)
        {
            // 计算X、Y轴上的坐标差值
            Touch_x_dif = dif_absolute(Touch->x, Touch_x_before);
            Touch_y_dif = dif_absolute(Touch->y, Touch_y_before);

            // 判断X轴滑动方向
            if (Touch_x_dif > 300 && Touch_y_dif < 200)
            {
                if (Touch_x_before > Touch->x)  
                { 
                    Touch->move_dir = TOUCH_LEFT;  // 左滑
                }
                if (Touch_x_before < Touch->x)  
                { 
                    Touch->move_dir = TOUCH_RIGHT;  // 右滑
                }
            }
            // 判断Y轴滑动方向
            else if (Touch_y_dif > 250 && Touch_x_dif < 200)
            {
                if (Touch_y_before > Touch->y)  
                { 
                    Touch->move_dir = TOUCH_UP;  // 上滑
                }
                if (Touch_y_before < Touch->y)  
                { 
                    Touch->move_dir = TOUCH_DOWN;  // 下滑
                }
            }
            // 未检测到滑动，判定为单点触摸
            else
            { 
                Touch->move_dir = TOUCH_NOMV;  
            }
        }

        // 松手检测，结束循环
        if (buf.type == EV_KEY && buf.code == BTN_TOUCH && buf.value == 0)
        { 
            break; 
        }
    }
    Touch->Touch_leave = 1;  // 标记触摸离开
}

/*
    函数名  ：Touch_SCAN
    作  用  ：作为触摸屏线程的执行函数
    输入参数：结构体指针
    返 回 值：无
*/
void* Touch_SCAN(void* Touch)
{
    while (1)
    {
        Touch_Scan((struct Touch_val *)Touch);  // 扫描并获取当前触摸位置
    }
}
