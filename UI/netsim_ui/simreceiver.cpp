#include "simreceiver.h"

SimReceiver::SimReceiver(int allframe, void (*callback)())
{
    this->allframe = allframe;
    curframe = 0;
    this->callback = callback;
}

void SimReceiver::run(void){
    //on something changed
   QMutexLocker lock(&locker);
   lock.unlock();
   for ( int i = 0 ; i < allframe ; i++){
       lock.relock();
       curframe++;
       lock.unlock();
       sleep(1);
   }
}

int SimReceiver::query(void){
    QMutexLocker lock(&locker);
    return curframe;
}

void SimReceiver::flush(void){
    QMutexLocker lock(&locker);
    curframe=-1;
}
