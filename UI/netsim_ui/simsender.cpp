#include "simsender.h"

void SimSender::run(){

    sender.windowSize = 7;
    sender.error_rate = 0.10;
    sender.total_frame = 16;


    s = socket(AF_INET, SOCK_STREAM, 0); /* use TCP protocol */
    if(s == -1){
        puts("Building a socket failed!");
        return ;
    }

    ser.sin_family = AF_INET;
    ser.sin_port = htons(6500);
    ser.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(s, (struct sockaddr *) &ser, sizeof(ser));
    puts("TCP Connection Established.");

    sseed=(unsigned int) time(NULL);
    srand(sseed);

    printf("Total %d frame will send sooner and the WindowSize is %d.\n", sender.total_frame, sender.windowSize);
    total = sender.total_frame;
    WindowSize = sender.windowSize;
    P1 = 100;
    P2 = sender.error_rate * P1;
    int2char(total);
    send(s, act, sizeof(act), 0);
    printf("P1 = %d, P2 = %d\n", P1, P2);

    while(1){
        go_back_n();
    }
}

/*****************************************************
 * go_back_n()
 * return: void
 * purpose: run the go_back_n protocol
 ******************************************************/
void SimSender::go_back_n(){

    // while(1) {
        if(cur < total) {
            origin_cur = cur;
            /* 每次循环窗口大小全部发送 */
            for(i = 0; i < WindowSize; i++) {
                int random = rand() % P1;

                /* 若还能继续发就发 */
                if(cur < total) {
                    /* 封包 */
                    int2char(cur);
                    /* 一定概率丢包 */
                    // printf("cur = %d, random = %d\n", cur, random);
                    if(random < P2)
                        send(s, bad, sizeof(bad), 0);
                    else
                        send(s, act, sizeof(act), 0);

                    /* 打开标号为cur的timer */
                    timer_on(cur);

                }
                /* 不能发直接退 */
                else break;

                /* 停一秒,可以进行速率模拟 */
                sleep(1);

                /* 这里虽然显示发出,但有可能是丢包 */
                if(cur < total) {
                    printf("Frame %d Sent\n",cur % Mod);
                    /* 标号加1,表示下一待发帧 */
                    cur++;
                }
            }

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

            /* 每次最多进行WindowSize次操作 */
            for(i = 0; i < WindowSize; i++) {
                // 维持timer工作
                process();

                if(recv(s, act, sizeof(act), MSG_DONTWAIT) < 0) {
                    sleep(1);
                    recv(s, act, sizeof(act), MSG_DONTWAIT);

                }
                /* 我想查看下是否收到东西 */
                // puts(act);
                int now = atoi(act);

                // printf("left = %d right = %d\n", left, right);

                /* 判断当前窗口内的第一个超时帧,无则返回-1 */
                int debug = judge(left, right);

                // printf("origin_left = %d debug = %d\n", origin_left, debug);
                if(debug != -1 && debug > origin_left){
                    printf("Time-out on # %d, resent\n", debug % Mod);
                    // 待确认帧
                    cur = debug;
                    return ;
                }
                else {
                    if(now >= left && now < right && now >= origin_left) { // add && now >= origin_left
                        /* 累计应答 */
                        printf("The %d frame got ACK.\n", now % Mod);

                        /* 窗口移动 */
                        int delta = now - origin_left + 1;
                        left += delta;
                        right += delta;
                        if(right > total) right = total;
                        if(left >= total) {
                            cur = total;
                            origin_left = now + 1;
                        }

                        /* 待确认帧更新 */
                        else origin_left = now + 1;
                    }

                }
                /* 如果非正常顺序到达,已在循环结束之前将窗口跑完则直接退出 */
                if(left - lleft >= WindowSize) break;

                //printf("待确认帧origin_left = %d cur = %d\n", origin_left, cur);
                if(cur >= total) break;
            }
            /* 如果此时待确认帧还没到cur,说明在循环内没进行完确认 */
            if(origin_left < cur){
                printf("Time-out on # %d, resent\n", origin_left % Mod);
                cur = origin_left;
            }
            if(cur >= total) return ;
            /* 重置窗口所有timer */
            reset_process(cur);
        }
        else if(origin_left == total){

            return ;
        }
        //TODO use emit
        query();
    // }

}

/*****************************************************
 * int2char()
 * return: void
 * purpose: turn the int z into a char[](act)
 ******************************************************/
void SimSender::int2char(int z)
{
    memset(act, 0, sizeof(act));
    sprintf(act, "%d", z);
}

/*****************************************************
 * timer_on(int cur)
 * return: void
 * purpose: turn on a timer indexed cur
 ******************************************************/
void SimSender::timer_on(int cur){
    /* 时限为5 */
    setTimer(5, cur);

    //等信号(异步),捎带处理timeout()函数
    if(signal(SIGALRM, timeout) == SIG_ERR){
        puts("error");
    }

    //发信号
    kill(getpid(), SIGALRM);

}

/*****************************************************
 * setTimer(int stime, int cur)
 * return: void
 * purpose: set a timer
 ******************************************************/
void SimSender::setTimer(int stime, int cur) {
    /* 这是标号为cur的timer所对应的初始时长 */
    myTimer[cur].left_time = stime;
    /* 这是开的timer个数的上界 */
    end++;
}

/*****************************************************
 * timeout()
 * return: void
 * purpose: 计时器处理
 ******************************************************/
void SimSender::timeout() {
    int j;
    for(j = begin; j < end; j++) {
        /* 从第一个设置的timer开始,循环使各个timer减1s */
        if(myTimer[j].left_time != 1) {
            myTimer[j].left_time--;
        }
        //printf("Timer[%d] = %d\n", j, myTimer[j].left_time);
    }

}

/*****************************************************
 * process()
 * return: void
 * purpose: 使计时器正常工作
 ******************************************************/
void SimSender::process(){
    if(signal(SIGALRM, timeout) == SIG_ERR){
        puts("error");
    }
    kill(getpid(), SIGALRM);
}

/*****************************************************
 * reset_process(cur)
 * return: void
 * purpose: 重置从cur开始的计时器组
 ******************************************************/
void SimSender::reset_process(int cur){
    begin = cur;
    end = begin;
}

/*****************************************************
 * judge(int left, int right)
 * return: int
 * purpose: 检查窗口内是否有计时器超时,若有则返回第一个超时的下标
 ******************************************************/
int SimSender::judge(int left, int right){
    int i;
    for(i = left; i < right; i++){
        if(myTimer[i].left_time == 1){
            return i;
        }
    }
    return -1;
}
