#ifndef SIMRECEIVER_H
#define SIMRECEIVER_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <time.h>     /* random value */
#include <ctype.h>    /* atoi function */

#include "including.h"
#include <unistd.h>
#include <QMutex>
#include <QThread>

#define Mod 8

struct Initial {
    int windowSize;     // 窗口大小
    int total_frame;    // 总帧数
    double error_rate;     // 差错率,为一个[0,1]之间的小数,必须保留两位小数.
    int sim_speed;      // 模拟发送速率
};

/* 定义状态结构体 */
struct RecvState{
    int cur;
}State;


class SimReceiver : public QThread
{
    Q_OBJECT
private:
    struct sockaddr_in ser, cli;
    unsigned int sseed;
    int P1, P2;     		// 从宏定义转过来开成了全局变量
    int s, err, sock, total, i, cur;
    void run();
    struct Initial receiver;
    void go_back_n();
    void int2char(int z);


};

#endif // SIMRECEIVER_H





/*************************************************/
// #include "gbnstruct.h"

/* main function
int
main()
{
    struct Initial test;
    // 暂不设计发送速率的问题
    // test.windowSize = 3;
    test.error_rate = 0.10;
    // test.total_frame = 31;

    init(test);

    return 0;
}
 struct RecvState query(){
     struct RecvState temp;
     ///* 当前待接收帧的标号
     temp.cur = cur;
     return temp;
 }

/********************** end ***************************/
