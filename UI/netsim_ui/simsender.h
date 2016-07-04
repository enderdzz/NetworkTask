#ifndef SIMSENDER_H
#define SIMSENDER_H

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <csignal>
#include <cctype>
#include <ctime>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



#include "including.h"
#include <unistd.h>
#include <QMutex>
#include <QThread>
#include <QTimer>


class SimSender : public QThread
{
    Q_OBJECT

private:
    void run();
    int s, total;				// total 帧总数 s socket描述符
    int begin, end, debug, cur; // begin与end均为现存计时器的标号 debug为窗口内第一个超时的计时器标号 cur为待发送帧标号
    int WindowSize, P1, P2;     // 从宏定义转过来开成了全局变量
    unsigned int sseed;
    int i, left, right, lleft, origin_left, origin_cur;

    struct sockaddr_in ser;  // 代表server
    struct Initial sender;
    QTimer* myTimer[TimerNum];
    /*
    struct Timer {
        int left_time;       // 剩余时间
    }myTimer[TimerNum];      // 计时器个数上限50*/

    void go_back_n();
    void int2char(int);
    void timer_on(int);      /*打开计时器(标号)*/
//    void setTimer(int, int); /*设定计时器(时限, 标号)*/
//    void timeout();          /*计时器的唯一操作*/
//    void process();          /*运行计时器*/
    void reset_process(int); /*重启计时器(标号)*/
    int judge(int, int);     /*判断窗口内超时的第一个帧(窗口左,窗口右)*/

    char ss_act[10];
    char ss_bad[20] = "Time-out ";
signals:
    void query();



};

#endif // SIMSENDER_H
