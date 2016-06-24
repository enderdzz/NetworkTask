#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <time.h>     /* random value */
#include <ctype.h>    /* atoi function */

#define WindowSize 3
#define TimerNum 50
#define P1 50
#define P2 5

char act[10];
char bad[20] = "Time-out ";
int s, total;
int begin, end, debug, cur;
void int2char(int);
void timer_on(int);
void setTimer(int, int);
void timeout();
void process();
void reset_process(int);
int judge(int, int);

struct sockaddr_in ser;
struct Timer {
  int left_time;
}myTimer[TimerNum];

int main()
{
    s = socket(AF_INET, SOCK_STREAM, 0); /* use TCP protocol */
  	if(s == -1){
  		puts("Building a socket failed!");
  		return 0;
  	}

    ser.sin_family = AF_INET;
    ser.sin_port = htons(6500);
    ser.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(s, (struct sockaddr *) &ser, sizeof(ser));
    puts("TCP Connection Established.");

    puts("Enter the number of Frames: ");
    scanf("%d", &total);
    int2char(total);
    send(s, act, sizeof(act), 0);

/* Issue: 1. No. of the frame need to begin with 0.
 *        2. Multi-thread needed
 *
/************************* go back n **************************/
    int i;
    while(1) {
        if(cur < total) {

          for(i = 0; i < WindowSize; i++) {
              int random = rand() % P1;

              // 若还能继续发就发
              if(cur < total) {
                // 封包
                int2char(cur);
                // 一定概率丢包
                if(random < P2){
                  send(s, bad, sizeof(bad), 0);
                }
                else send(s, act, sizeof(act), 0);

                // 打开标号为cur的timer
                timer_on(cur);

              } // 不能发的话处理timer的问题
              else process();

              //停一秒
              sleep(1);

              // 这里虽然显示发出,但有可能是丢包
              if(cur < total) {
                  printf("Frame %d Sent\n",cur);
                  cur++;
              }
          }

          // 接受ACK的过程
          int left = cur - WindowSize, right = cur;
          int origin_left = left;
          if(cur == total) left = total - total%WindowSize;
          cur = left;
          for(i = 0; i < WindowSize; i++) {
            // 维持timer工作
            process();

            recv(s, act, sizeof(act), 0);
            int now = atoi(act);

            //printf("left = %d right = %d\n", left, right);

            // 判断当前窗口内的第一个超时帧,无则返回-1
            int debug = judge(left, right);

            printf("cur = %d debug = %d\n", cur, debug);
            if(debug != -1 && debug > cur){
              printf("Time-out on # %d, resent\n", debug);
              // 待确认帧
              cur = debug;
              break;
            }
            else {

              //if(now >= left && now < right) {
                // 累计应答
                printf("The %d frame got ACK.\n", now);

                // 窗口移动
                int delta = now - cur + 1;
                left += delta;
                right += delta;
                if(right > total) right = total;
                if(left >= total) cur = total;
                // 待确认帧
                else cur = now+1;
              //}

            }
            if(left - origin_left >= WindowSize) break;
            printf("cur = %d\n", cur);
            if(cur >= total) break;
          }
          if(cur >= total) break;
          // 重置所有timer
          reset_process(cur);
        }
        else {
          //sleep();
        }
    }
    close(s);
    return 0;
}

void int2char(int z)
{
	memset(act, 0, sizeof(act));
	sprintf(act, "%d", z);
}

void timer_on(int cur){
  setTimer(5, cur);

  //等信号(异步)
  if(signal(SIGALRM, timeout) == SIG_ERR){
    puts("error");
  }

  //发信号
  kill(getpid(), SIGALRM);

}
// 需要设置时长stime,标号;
void setTimer(int stime, int cur) {

  struct Timer a;
  a.left_time = stime;
  myTimer[cur] = a;    // 这是标号为cur的timer所对应的初始时长
  end++;      // 这是开的timer个数的上界

}

void timeout() {

  int j;
  for(j = begin; j < end; j++) { // 从第一个设置的timer开始,每次循环使各个timer减1s
    if(myTimer[j].left_time != 1) {
      myTimer[j].left_time--;
    }

    printf("Timer[%d] = %d\n", j, myTimer[j].left_time);
  }

}

void process(){
    //sleep(1);
    kill(getpid(), SIGALRM);
    if(signal(SIGALRM, timeout) == SIG_ERR){
      puts("error");
    }
}

void reset_process(int cur){
  begin = cur;
  end = begin;
}

int judge(int left, int right){
  int i;
  for(i = left; i < right; i++){
    if(myTimer[i].left_time == 1){
      return i;
    }
  }
  return -1;
}
