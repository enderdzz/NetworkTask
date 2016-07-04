#ifndef SIMRECEIVER_H
#define SIMRECEIVER_H



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

    char ss_act[10];
    char ss_bad[20] = "Time-out ";
signals:
    void query();

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
