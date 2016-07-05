#ifndef SIMRECEIVER_H
#define SIMRECEIVER_H

#include "including.h"
#include <unistd.h>

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
    int read_some_value(void);

protected:
    void timerEvent(QTimerEvent *event);
    int timer_id[2];

private:
    int some_value = 0;
    QMutex* some_value_mutex;

signals:
    void something_need_to_announce(const char*);
};


#endif // SIMRECEIVER_H

