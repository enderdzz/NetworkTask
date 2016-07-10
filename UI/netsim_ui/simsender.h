#ifndef SIMSENDER_H
#define SIMSENDER_H

#include "including.h"
#include <unistd.h>

/**************************************/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
/**************************************/

#include <QMutex>
#include <QThread>
#include <QTimer>
#include <QTimerEvent>

class SimSender : public QObject
{
    Q_OBJECT

public slots:
    void work();

public:
    ~SimSender();
    int read_some_value(void);

    SimSender(int frame_count, int window_size, int timer_delay);

protected:
    void timerEvent(QTimerEvent *event);
    int timer_id[2];

private:
    /****************************************/
    struct sockaddr_in ser;
    unsigned int sseed = 0;
    int i = 0, left = 0, right = 0, lleft = 0, origin_left = 0, origin_cur = 0;
    int s = 0, total = 0;				// total 帧总数 s socket描述符
    int begin = 0, end = 0, debug = 0, cur = 0; // begin与end均为现存计时器的标号 debug为窗口内第一个超时的计时器标号 cur为待发送帧标号
    int WindowSize = 0, P1 = 0, P2 = 0;     // 从宏定义转过来开成了全局变量
    char ack[20]={};
    int current_frame = 0;
    int frame_count = 0;
    int window_size = 0;
    int timer_delay = 0;

    void int2char(int z);
    /****************************************/
    int some_value = 0;
    QMutex* some_value_mutex;
    // QMutex* read_mutex;

signals:
    void something_need_to_announce(const char*);
};

#endif // SIMSENDER_H
