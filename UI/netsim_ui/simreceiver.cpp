#include "simreceiver.h"



void SimReceiver::work(){
    this->current_frame = 0;
    timer_id = startTimer(timer_delay);
}

int SimReceiver::get_status(int &current_window)
{
    QMutexLocker locker(read_mutex);
    current_window = current_frame;
    return current_frame;
}

SimReceiver::SimReceiver(int frame_count, int window_size, int timer_delay)
{
    this->frame_count = frame_count;
    this->window_size = window_size;
    this->timer_delay = timer_delay;
    this->current_frame = 0;
    read_mutex = new QMutex;
}

SimReceiver::~SimReceiver()
{
    delete read_mutex;
}

void SimReceiver::timerEvent(QTimerEvent *event){
    //When a timer triggered, get its id
    QMutexLocker locker(read_mutex);
    if (event->timerId() == timer_id ){

        emit status_update(current_frame, window_size);
        if (current_frame < frame_count )
        {
            current_frame++;
            if (window_size + current_frame > frame_count)
                window_size = frame_count - current_frame;
        }else{
            killTimer(timer_id);
        }

    }
}
