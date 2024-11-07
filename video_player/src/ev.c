#include "ev.h"
#include "bmp.h"
#include "game.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <linux/input.h>

int Get_ev(int *x, int *y)
{
    int touch_active = 0;     // ????????
    int gesture_state = 3;    // ???????1????2????3???
    int fd = open("/dev/input/event0", O_RDONLY);

    if (fd == -1)
    {
        perror("????????");
        return -1;
    }

    struct input_event ev;
    int x1 = 0, y1 = 0; // ???????????

    while (1)
    {
        ssize_t read_bytes = read(fd, &ev, sizeof(ev));
        if (read_bytes != sizeof(ev)) {
            perror("??????");
            close(fd);
            return -1;
        }

        printf("???? = %d, ?? = %d, ? = %d\n", ev.type, ev.code, ev.value);

        // ????????????
        if (ev.type == EV_ABS)
        {
            if (ev.code == ABS_X) // X ???
            {
                x1 = ev.value * 800 / 1024; // ???????
            }
            else if (ev.code == ABS_Y) // Y ???
            {
                y1 = ev.value * 480 / 600;  // ???????
            }
        }

        // ??????
        if (ev.type == EV_KEY && ev.code == BTN_TOUCH)
        {
            if (ev.value == 1) // ????
            {
                *x = x1;
                *y = y1;
                touch_active = 1;
            }
            else if (ev.value == 0 && touch_active) // ????
            {
                // ????
                if (*x == x1 && *y == y1)
                {
                    printf("??\n");
                    if (gesture_state == 1)
                        Game_Change(x1, y1);
                    else
                    {
                        Dis_pan(); // ????????
                        gesture_state = 1;
                    }
                }
                // ??
                else if (x1 > *x)
                {
                    printf("??\n");
                    gesture_state = 2;
                }
                // ??
                else if (x1 < *x)
                {
                    printf("??\n");
                    gesture_state = 3;
                }

                touch_active = 0; // ??????
                Game_Over();       // ????????
            }
        }
    }

    close(fd); // ??????
    return 0;
}
