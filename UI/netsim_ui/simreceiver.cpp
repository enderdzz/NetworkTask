#include "simreceiver.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// struct Initial receiver cannot be used as parameter
void SimReceiver::work(){
    cur = 0;
    this->current_frame = 0;
    /*************************************/
    s = socket(AF_INET, SOCK_STREAM, 0); /* use TCP protocol */
    if(s == -1){
        qDebug("Building a socket failed!");
        return ;
    }

    ser.sin_family = AF_INET;
    ser.sin_port = htons(6500);
    ser.sin_addr.s_addr = inet_addr("127.0.0.1");

    err = bind(s, (struct sockaddr *) &ser, sizeof(ser));
    if(err != 0){
        qDebug("Binding a socket failed!");
        return ;
    }

    listen(s, 1);
    socklen_t len = sizeof(cli);
    sock = accept(s, (struct sockaddr *) &cli, &len);
    // Socket

    qDebug("Recv TCP Connection Established. ");
    recv(sock, ack, sizeof(ack), 0);
    total = atoi(ack);
    qDebug("Recv from the sender: total frame is %d.\n", total);

    P1 = 100;
    P2 = error_rate * P1;
    qDebug("P1 = %d, P2 = %d\n", P1, P2);

    while(1){
        if (need_stop)
            break;
        // go_back_n( query );
        recv(sock,ack,sizeof(ack), MSG_DONTWAIT);
        //recv(sock,ack,sizeof(ack), 0);
       // sleep(1);

        int check = atoi(ack);
        int random = rand() % P1;
        //printf("check = %d, random = %d\n", check, random);
        if(random < P2 && check == cur && cur < total){
            qDebug("Frame %d Received \n", check % Mod);
            if(window_size != 1) cur++;
            // care
            this->current_frame = cur;
            emit sent_failed();
            emit receiver_status_update(this->current_frame);
        }
        if(check == cur && cur < total){

            QTimer *tim = new QTimer;
            tim->setInterval(200);
            tim->setSingleShot(true);
            tim->start();
            while(tim->remainingTime()>1);
            delete tim;
            tim=NULL;

            qDebug("Frame %d Received \n", check % Mod);
            cur++;
            // care
            this->current_frame = cur;
            emit receiver_status_update(this->current_frame);
            emit sent_succeed();
            send(sock, ack, sizeof(ack), 0);
        }
        if(cur == total) { // make sure the last frame's ack is sended successfully!
            int2char(cur-1);
            send(sock, ack, sizeof(ack), MSG_NOSIGNAL);
            sleep(1);
            send(sock, ack, sizeof(ack), MSG_NOSIGNAL);
            sleep(1);
            send(sock, ack, sizeof(ack), MSG_NOSIGNAL);

            break;
        }
    }
    close(sock);
    close(s);
    /*************************************/
}

int SimReceiver::get_status(int &current_window)
{

    current_window = current_frame;
    return current_frame;
}

SimReceiver::SimReceiver(int frame_count, int window_size, int timer_delay, double error_rate)
{
    this->frame_count = frame_count;
    this->window_size = window_size;
    this->timer_delay = timer_delay;
    this->current_frame = 0;
    this->error_rate = error_rate;

    need_stop = false;
}

void SimReceiver::request_stop()
{
    need_stop = true;
}

SimReceiver::~SimReceiver()
{

}

// receiver needn't to use the timer!
void SimReceiver::timerEvent(QTimerEvent *event){
    //When a timer triggered, get its id

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

void SimReceiver::int2char(int z)
{
    memset(ack, 0, sizeof(ack));
    sprintf(ack, "%d", z);
}
