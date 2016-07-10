#include "simsender.h"



void SimSender::work(){
    /**********************************************/
    s = socket(AF_INET, SOCK_STREAM, 0); /* use TCP protocol */
    if(s ==  -1){
        qDebug("Building a socket failed!");
        return ;
    }

    ser.sin_family = AF_INET;
    ser.sin_port = htons(6500);
    ser.sin_addr.s_addr = inet_addr("127.0.0.1");

    ::connect(s, (struct sockaddr *) &ser, sizeof(ser));
    // Socket
    qDebug("Sender TCP Connection Established.");
    sseed=(unsigned int) time(NULL);
    srand(sseed);
    qDebug("Total %d frame will send sooner and the WindowSize is %d.\n", this->frame_count, this->window_size);

    total = this->frame_count;
    WindowSize = this->window_size;
    P1 = 100;
    P2 = 0.00 * P1;
    int2char(total);
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
                    if(random < P2){ }//do nothing
                    else send(s, ack, sizeof(ack), 0);

                }
                /* 不能发直接退 */
                else break;

                /* 停一秒,可以进行速率模拟 */
                sleep(1);

                /* 这里虽然显示发出,但有可能是丢包 */
                if(cur < total) {
                    qDebug("Frame %d Sent\n",cur % Mod);
                    cur++;

                    // care here, cur is the next frame to be sended !!
                    // emit send_status(cur);
                }
            }

            /* 打开标号为cur的timer */
            timer_send = startTimer(5000);

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
            emit send_status(0);

            while(1){   //  for(i = 0; i < WindowSize; i++) {

                // recv twice!!
                if(recv(s, ack, sizeof(ack), MSG_DONTWAIT) < 0) {
                    // sleep(1);
                    // recv(s, ack, sizeof(ack), MSG_DONTWAIT);
                    if (timer_send != -1)
                        continue;
                    else{
                        cur = origin_left;
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

                        emit send_status(origin_left);

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
    /**********************************************/

    //    some_value_mutex = new QMutex;
    //    //Here you should write your code in the new thread
    //    for ( int i = 0 ; i < 10 ; i++ ){
    //        qDebug("In new thread Sender\n");
    //        //and if you need, just send me something
    //        if (i==4)
    //            emit something_need_to_announce("Sender Notice!");
    //        else if (i==5)//and if you want to write some var, lock it in case of I'm reading it at the same time!
    //        {
    //            QMutexLocker locker(some_value_mutex);
    //            some_value = 233;
    //            locker.unlock();
    //        }
    //    }

    //    //This is a example of how to use timer
    //    timer_id[0] = startTimer(1000);//trigger after 1s
    //    timer_id[1] = startTimer(2000);
    //    //if you need, just record this timer in somewhere else

    //    qDebug("Still in the new thread Sender\n");

}

SimSender::~SimSender()
{
    delete some_value_mutex;
}

void SimSender::request_stop()
{
    need_stop = true;
}

int SimSender::read_some_value(void){
    QMutexLocker locker(some_value_mutex);
    return some_value;
}

void SimSender::timerEvent(QTimerEvent *event){
    //When a timer triggered, get its id
    if (event->timerId() == this->timer_send){
        qDebug("- Sender reached\n");
        //kill it if you need
        killTimer(timer_send);
        // startTimer()
        //clear old id for safe
        timer_send = -1;
    }
}

SimSender::SimSender(int frame_count, int window_size, int timer_delay)
{
    this->frame_count = frame_count;
    this->window_size = window_size;
    this->timer_delay = timer_delay;

    some_value_mutex = new QMutex;
    need_stop = false;
}

void SimSender::int2char(int z)
{
    memset(ack, 0, sizeof(ack));
    sprintf(ack, "%d", z);
}
