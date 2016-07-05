#include "simsender.h"

void SimSender::work(){
    some_value_mutex = new QMutex;
    //Here you should write your code in the new thread
    for ( int i = 0 ; i < 10 ; i++ ){
        qDebug("In new thread Sender\n");
        //and if you need, just send me something
        if (i==4)
            emit something_need_to_announce("Sender Notice!");
        else if (i==5)//and if you want to write some var, lock it in case of I'm reading it at the same time!
        {
            QMutexLocker locker(some_value_mutex);
            some_value = 233;
            locker.unlock();
        }
    }

    //This is a example of how to use timer
    timer_id[0] = startTimer(1000);//trigger after 1s
    timer_id[1] = startTimer(2000);
    //if you need, just record this timer in somewhere else

    qDebug("Still in the new thread Sender\n");

}

int SimSender::read_some_value(void){
    QMutexLocker locker(some_value_mutex);
    return some_value;
}

void SimSender::timerEvent(QTimerEvent *event){
    //When a timer triggered, get its id
    if (event->timerId() == this->timer_id[0]){
        qDebug("0s Sender reached\n");
        //kill it if you need
        killTimer(timer_id[0]);
        //clear old id for safe
        timer_id[0]=NULL;
    }else if (event->timerId() == this->timer_id[1]){
        qDebug("1s Sender reached\n");
        //kill it if you need
        killTimer(timer_id[1]);
        //for your safety
        timer_id[1]=NULL;
    }

}
