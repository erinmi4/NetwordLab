//
// Created by 25115 on 2024/11/8.
//

#include "../INC/Filedir.h"

/*
    函数名  ：Read_Dir
    作  用  ：根据需要的文件类型，读取目录下相应的文件名返回路径
    输入参数：
                File      在主函数中存储目录的结构体指针
                url       需要检索的路径
                type      需要检索的文件类型
    返 回 值：无
*/
void Read_Dir(struct Filedir *File, char *url, char *type) {
    File->FileNum = 0;  // 初始化输入结构体的文件数量值
    DIR *pDir = opendir(url);  // 打开路径

    if (pDir == NULL) {
        perror("opendir is NULL!\n");  // 打印错误信息
        return;
    }

    struct dirent *pEnt;
    while ((pEnt = readdir(pDir)) != NULL) {
        if (pEnt->d_type == DT_REG) {  // 确认是普通文件
        //将目录路径和文件名组合成完整的文件路径,并存储在 File->FilePath[File->FileNum] 中
            snprintf(File->FilePath[File->FileNum], sizeof(File->FilePath[File->FileNum]), "%s%s", url, pEnt->d_name);

            if (strstr(File->FilePath[File->FileNum], type) != NULL) {  // 判断文件类型
                printf("%s\n", File->FilePath[File->FileNum]);  // 打印文件路径
                File->FileNum++;//如果满足文件路径要求，计数器加1，并且保留改地址。否则跳过。

                if (File->FileNum >= max_FileNum) {
                    printf("The number of files in the directory exceeds the maximum number that can be read initially\n");
                    break;
                }
            }
        }
    }
    closedir(pDir);
}

/*
    对于系统文件的修改，需要在此处进行同步
    函数名  ：Read_SystemDir
    作  用  ：读取系统目录下的文件并对特定文件进行排序
    输入参数：
                File      在主函数中存储目录的结构体指针
                url       需要检索的路径
    返 回 值：无
*/
void Read_SystemDir(struct Filedir *File, char *url) {
    char *files[] = {
        "background", "music_play", "music_stop", "Photo_tip",
        "Gua_tip", "Guaground", "AVI_play", "AVI_stop",
        "game_lose", "game_win", 
        "Camera_Pho", "Camera_Play", "Camera_Stop", "Camera_Tip_AVI"
    };

    File->FileNum = 0;  // 初始化输入结构体的文件数量值
    DIR *pDir = opendir(url);

    if (pDir == NULL) {
        perror("opendir is NULL!\n");  // 打印错误信息
        return;
    }

    struct dirent *pEnt;
    char Check_FileName[100];
    while ((pEnt = readdir(pDir)) != NULL) {
        if (pEnt->d_type == DT_REG) {  // 确认是普通文件
            snprintf(Check_FileName, sizeof(Check_FileName), "%s", pEnt->d_name);

            for (int i = 0; i < sizeof(files) / sizeof(files[0]); i++) {
                if (strstr(Check_FileName, files[i]) != NULL) {
                    snprintf(File->FilePath[i], sizeof(File->FilePath[i]), "%s%s", url, pEnt->d_name);
                    File->FileNum++;
                    break;
                }
            }
        }
    }
    closedir(pDir);

    printf("System File:\n");
    for (int i = 0; i < File->FileNum; i++) {
        printf("%s\n", File->FilePath[i]);
    }
    printf("Other File:\n");
}
