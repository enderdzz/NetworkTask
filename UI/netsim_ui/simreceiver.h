#ifndef SIMRECEIVER_H
#define SIMRECEIVER_H

#include <unistd.h>
#include <QMutex>

class SimReceiver
{
private:
    int curframe = 0;
    void (*callback)() = nullptr;
    QMutex locker;
    int allframe = 0;

public:
    SimReceiver(int allframe, void (*callback)());
    void run(void);
    int query(void);
    void flush(void);
};

#endif // SIMRECEIVER_H
