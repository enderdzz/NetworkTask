#ifndef SIMRECEIVER_H
#define SIMRECEIVER_H

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

class SimReceiver : public QObject
{
    Q_OBJECT

public slots:
    void work();

public:
    int get_status(int &current_window);
    SimReceiver(int frame_count, int window_size, int timer_delay);
    ~SimReceiver();

protected:
    void timerEvent(QTimerEvent *event);
    int timer_id;

private:


    int s, err, sock, total, i, cur;
    struct sockaddr_in ser, cli;
    char ack[20]={};
    int WindowSize = 0, P1 = 0, P2 = 0;

    int current_frame = 0;
    int frame_count = 0;
    int window_size = 0;
    int timer_delay = 0;

    void int2char(int z);
    QMutex* read_mutex;

signals:
    void status_update(int current_window, int window_size);
};


#endif // SIMRECEIVER_H

