#ifndef __MUSIC_H
#define __MUSIC_H


//播放制定列表下的音频
void music_loop(char *path);
void music_stop();
void music_continue();
void music_cancel();

#endif