#ifndef __VIDEO_H__
#define __VIDEO_H__


// 暂停视频播放
void video_stop();
void video_continue();
void video_cancel();

// 从 (0, 0) 开始播放宽 800 高 480 的视频
void video_play(char *path);
// 循环播放视频
void video_loop(char *path);
// 播放上一个视频
void video_previous(char *path);
//播放下一个视频
void video_next(char *path);


#endif