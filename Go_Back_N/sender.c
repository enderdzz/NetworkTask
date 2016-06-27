#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
#define P2 10
#define Mod 16

char act[10];               // 伪帧
char bad[20] = "Time-out "; // 伪超时标志
int s, total;								// total 帧总数 s socket描述符
int begin, end, debug, cur; // begin与end均为现存计时器的标号 debug为窗口内第一个超时的计时器标号 cur为待发送帧指针
void int2char(int);			 /*发送的文本字符串*/
void timer_on(int);      /*打开计时器(标号)*/
void setTimer(int, int); /*设定计时器(时限, 标号)*/
void timeout();          /*计时器的唯一操作*/
void process();          /*运行计时器*/
void reset_process(int); /*重启计时器(标号)*/
int judge(int, int);     /*判断窗口内超时的第一个帧(窗口左,窗口右)*/

struct sockaddr_in ser;  // 代表server
struct Timer {
	int left_time;         // 剩余时间
}myTimer[TimerNum];      // 计时器个数上限50

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
				  // printf("cur = %d, random = %d\n", cur, random);
					if(random < P2){
						send(s, bad, sizeof(bad), 0);
					}
					else send(s, act, sizeof(act), 0);

					// 打开标号为cur的timer
					timer_on(cur);

				} // 不能发的话处理timer的问题
				else break;

				//停一秒
				sleep(1);

				// 这里虽然显示发出,但有可能是丢包
				if(cur < total) {
					printf("Frame %d Sent\n",cur % Mod);
					cur++;
				}
			}

			// 接受ACK的过程
			int left = cur - WindowSize, right = cur;
			int lleft = left;
			int origin_left = left;
			if(cur == total) left = total - total%WindowSize;
			// cur = left;
			// 每次最多进行WindowSize次操作
			for(i = 0; i < WindowSize; i++) {
				// 维持timer工作
				process();

				if(recv(s, act, sizeof(act), MSG_DONTWAIT) < 0){sleep(1);};
				// 我想查看下是否收到东西
				// puts(act);
				int now = atoi(act);

				// printf("left = %d right = %d\n", left, right);

				// 判断当前窗口内的第一个超时帧,无则返回-1
				int debug = judge(left, right);

				// printf("origin_left = %d debug = %d\n", origin_left, debug);
				if(debug != -1 && debug > origin_left){
					printf("Time-out on # %d, resent\n", debug % Mod);
					// 待确认帧
					cur = debug;
					break;
				}
				else {
					if(now >= left && now < right) {
						// 累计应答
						printf("The %d frame got ACK.\n", now % Mod);

						// 窗口移动
						int delta = now - origin_left + 1;
						left += delta;
						right += delta;
						if(right > total) right = total;
						if(left >= total) cur = total;
						// 待确认帧
						else origin_left = now+1;
					}

				}
				if(left - origin_left >= WindowSize) break; // 如果非正常顺序到达,已在循环结束之前将窗口跑完则直接退出

				//printf("待确认帧origin_left = %d cur = %d\n", origin_left, cur);
				if(cur >= total) break;
			}
			if(origin_left < cur){ // 如果此时待确认帧还没到cur,说明在循环内没进行完确认
				printf("Time-out on # %d, resent\n", origin_left % Mod);
				cur = origin_left;
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
	setTimer(5, cur); // 最多减6次

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

		//printf("Timer[%d] = %d\n", j, myTimer[j].left_time);
	}

}

void process(){

	if(signal(SIGALRM, timeout) == SIG_ERR){
		puts("error");
	}
	kill(getpid(), SIGALRM);
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
