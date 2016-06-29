#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <time.h>     /* random value */
#include <ctype.h>    /* atoi function */

/*************************************************/
// #include "gbnstruct.h"
#define Mod 8

char act[10];
char bad[20] = "Time-out ";
int s, err, sock, total, i, cur;
unsigned int sseed;
int P1, P2;     		// 从宏定义转过来开成了全局变量

struct sockaddr_in ser, cli;
struct Initial {
	int windowSize;     // 窗口大小
	int total_frame;    // 总帧数
	double error_rate;     // 差错率,为一个[0,1]之间的小数,必须保留两位小数.
	int sim_speed;      // 模拟发送速率
}Initial;
/* 定义状态结构体 */
struct RecvState{
	int cur;
}State;

void init(struct Initial);
void go_back_n(struct RecvState (*)());
struct RecvState query();
void int2char(int);

/* main function */
int
main()
{
	struct Initial test;
	// 暂不设计发送速率的问题
	// test.windowSize = 3;
	test.error_rate = 0.10;
	// test.total_frame = 31;

	init(test);



	close(sock);
	close(s);
	return 0;
}

/*****************************************************
 * init()
 * return: void
 * purpose: Initialise the state, including:
 *			1. Build the connection using the TCP socket.
 *			2. Receive the total_frame to Receiver.
 *
 ******************************************************/
void
init(struct Initial receiver){
	s = socket(AF_INET, SOCK_STREAM, 0); /* use TCP protocol */
	if(s == -1){
		puts("Building a socket failed!");
		return ;
	}

	ser.sin_family = AF_INET;
	ser.sin_port = htons(6500);
	ser.sin_addr.s_addr = inet_addr("127.0.0.1");

	err = bind(s, (struct sockaddr *) &ser, sizeof(ser));
	if(err != 0){
		puts("Binding a socket failed!");
		return ;
	}

	listen(s, 1);
	int len = sizeof(cli);
	sock = accept(s, (struct sockaddr *) &cli, &len);
	puts("TCP Connection Established.");

	// sseed=(unsigned int) time(NULL);
	// srand(sseed);
	recv(sock, act, sizeof(act), 0);
	total = atoi(act);
	printf("Recv from the sender: total frame is %d.\n", total);
	receiver.total_frame = total;
	P1 = 100;
	P2 = receiver.error_rate * P1;
	printf("P1 = %d, P2 = %d\n", P1, P2);

	while(1){
		go_back_n( query );
	}
}

/*****************************************************
 * go_back_n()
 * return: void
 * purpose: run the go_back_n protocol
 ******************************************************/
void
go_back_n(struct RecvState (* query)()){

	// while(1) {

		recv(sock,act,sizeof(act), MSG_DONTWAIT);
		//recv(sock,act,sizeof(act), 0);
		sleep(1);
		if(strcmp(act, bad) == 0){
			/* if sender send bad, then receiver do nothing. */
			return ;
		}

		int check = atoi(act);
		int random = rand() % P1;
		//printf("check = %d, random = %d\n", check, random);
		if(random < P2 && check == cur && cur < total){

			printf("Frame %d Received \n", check % Mod);
			cur++;
		}
		if(check == cur && cur < total){
			send(sock, act, sizeof(act), 0);
			printf("Frame %d Received \n", check % Mod);
			cur++;
		}
		if(cur >= total) {
			int2char(cur-1);
			send(sock, act, sizeof(act), 0);
			sleep(1);
			send(sock, act, sizeof(act), 0);
			sleep(1);
			send(sock, act, sizeof(act), 0);

		}
		query();
	// }

}

/*****************************************************
 * int2char()
 * return: void
 * purpose: turn the int z into a char[](act)
 ******************************************************/
void
int2char(int z)
{
	memset(act, 0, sizeof(act));
	sprintf(act, "%d", z);
}

/*****************************************************
 * query()
 * return: struct RecvState
 * purpose: 获得当前状态
 ******************************************************/
 struct RecvState query(){
	 struct RecvState temp;
	 /* 当前待接收帧的标号 */
	 temp.cur = cur;
	 return temp;
 }

/********************** end ***************************/
