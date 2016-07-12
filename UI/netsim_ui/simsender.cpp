#include "simsender.h"

#include <QTimer>

void SimSender::work(){
    memset(ack,0,sizeof(ack));
    QTimer* tim;
    /**********************************************/
    s = socket(AF_INET, SOCK_STREAM, 0); /* use TCP protocol */
    if(s == -1){
        qDebug("Building a socket failed!");
        return ;
    }

    ser.sin_family = AF_INET;
    ser.sin_port = htons(6500);
    ser.sin_addr.s_addr = inet_addr("127.0.0.1");


    // Socket
    qDebug("Sender TCP Connection Established.");
    sseed=(unsigned int) time(NULL);
    srand(sseed);
    qDebug("Total %d frame will send sooner and the WindowSize is %d.\n", this->frame_count, this->window_size);

    total = this->frame_count;
    WindowSize = this->window_size;
    P1 = 100;
    P2 = error_rate * P1;
    int2char(total);

    ::connect(s,(struct sockaddr*)&ser, sizeof(ser));
    send(s, ack, sizeof(ack), 0);

    while(1){
continue_send:
        if (need_stop)
            break;

        if(cur < total) {
            origin_cur = cur;

            // care !!
            emit sendwindow_status(left);

            for(i = 0; i < WindowSize; i++) {
                int random = rand() % P1;
                if(cur < total) {
                    /* 封包 */
                    int2char(cur);
                    /* 一定概率丢包 */
                    //qDebug("cur = %d, random = %d\n", cur, random);
                    if(random < P2){
                        emit send_failed();
                    }//do nothing
                    else
                        send(s, ack, sizeof(ack), MSG_NOSIGNAL);
                        emit send_succeed();
                }
                /* 不能发直接退 */
                else break;

                /* 停一秒,可以进行速率模拟 */
                //  sleep(1);

                /* 这里虽然显示发出,但有可能是丢包 */
                if(cur < total) {
                    qDebug("Frame %d Sent\n",cur % Mod);
                    cur++;

                    // care here, cur is the next frame to be sended !!
                    // emit send_status(cur);
                }
            }

            /* 打开标号为cur的timer */
            tim = new QTimer;
            tim->setInterval(1300);
            tim->setSingleShot(true);
            tim->start();

            /* 接受ACK的过程 */
            // 定义实时窗口的左右墙
            left = cur - WindowSize, right = cur;
            // 保存一个左墙的备份,一会有用
            lleft = left;
            // 定义待接收ACK的帧标号
            origin_left = left;
            // 如果已经全部发送完,最后一个窗口可能会是残缺的.

            if(cur == total) {
                left = origin_cur;
                lleft = origin_cur;
                origin_left = origin_cur;
            }

            // the frame that needs to be ack !
            //emit send_status(0);

            while(1){
                if(recv(s, ack, sizeof(ack), MSG_DONTWAIT) < 0) {

                    if (tim->remainingTime()>0)
                    {
                        continue;
                    }
                    else{
                        cur = origin_left;

                        // care !!
                        emit timeout_send(cur);
                        emit send_failed();
                        qDebug("RELOAD!!!!!");



                        tim->stop();
                        delete tim;
                        tim=NULL;
                        goto continue_send;
                    }
                } else {
                    int now = atoi(ack);
                    if(now >= left && now < right && now >= origin_left) { // add && now >= origin_left
                        /* 累计应答 */
                        qDebug("The %d frame got ACK.\n", now % Mod);
                        /* 窗口移动 */
                        int delta = now - origin_left + 1;
                        left += delta;
                        right += delta;
                        if(right > total) right = total;
                        if(left >= total)  cur = total;
                        /* 待确认帧更新 */
                        origin_left = now + 1;

                        // care !!
                        emit send_status(origin_left);
                        emit send_succeed();
                    }

                    /* 如果非正常顺序到达,已在循环结束之前将窗口跑完则直接退出 */
                    if(left - lleft >= WindowSize) break;

                    if(cur >= total) break;

                    if (origin_left >= cur)
                        goto continue_send;
                    else
                        continue;

                }

            }
            /* 如果此时待确认帧还没到cur,说明在循环内没进行完确认 */
            if(origin_left < cur){
                qDebug("Time-out on # %d, resent\n", origin_left % Mod);
                cur = origin_left;
            }
            if(cur >= total) break ;
            /* 重置窗口所有timer */

        }
        else if(origin_left == total){

            break;
        }
    }
    close(s);
    qDebug("Should have stopped.");

    // care !!
    emit finish_send();

}


SimSender::~SimSender()
{

}

void SimSender::request_stop()
{
    need_stop = true;
}



SimSender::SimSender(int frame_count, int window_size, int timer_delay, double error_rate)
{
    this->frame_count = frame_count;
    this->window_size = window_size;
    this->timer_delay = timer_delay;
    this->error_rate = error_rate;

    need_stop = false;
}

void SimSender::int2char(int z)
{
    memset(ack, 0, sizeof(ack));
    sprintf(ack, "%d", z);
}
