#ifndef INCLUDING_H
#define INCLUDING_H

#include <QMessageBox>
#include "simreceiver.h"
#include "simsender.h"



struct Initial {
    int windowSize;          // 窗口大小
    int total_frame;          // 总帧数
    double error_rate;     // 差错率,为一个[0,1]之间的小数,必须保留两位小数.
    int sim_speed;            // 模拟发送速率
};

/* 定义状态结构体 */
struct RecvState{
    int cur;
};

struct SendState{
    int left, right;    // 窗口位置
    int cur;			  // 待接收帧标号
};

#define TimerNum 50
#define Mod 8


#endif // INCLUDING_H
