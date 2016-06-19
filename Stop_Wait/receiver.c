#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <time.h>     /* random value */
#include <ctype.h>    /* atoi function */

#define P1 50       /* denominator */
#define P2 10				/* numerator */

char act[10];
char bad[20] = "Time Out ";
void int2char(int);

struct sockaddr_in ser,cli;   /* server & client */
int s, err, sock, total;
unsigned int sseed;

int main()
{

	s = socket(AF_INET,SOCK_STREAM,0); /* use TCP protocol */
	if(s == -1){
		puts("Building a socket failed!");
		return 0;
	}

	ser.sin_family = AF_INET;
	ser.sin_port = htons(6500);
	ser.sin_addr.s_addr = inet_addr("127.0.0.1");

	err = bind(s, (struct sockaddr *) &ser, sizeof(ser));
	if(err != 0){
		puts("Binding a socket failed!");
		return 0;
	}

	listen(s,1);
	int len = sizeof(cli);
	sock = accept(s, (struct sockaddr *)&cli, &len);
	puts("TCP Connection Established.");

	sseed = (unsigned int)time(NULL); /* initial the random value */
	srand(sseed);

	recv(sock, act, sizeof(act), 0);
	total = atoi(act);
	printf("total frame = %d\n", total);

/************************* stop and wait *****************************/
int cur = 1;
	while(1){
		recv(sock, act, sizeof(act), 0);
		/// printf("recv act = %s \n", act);
		if(strcmp(act, bad) != 0 && strlen(act) != 0){    /* if not time-out */
			int random = rand() % P1;       /* have a certain probability to send the ACK with the time-out */
			int check = atoi(act);
			if(random < P2){						    /* 20% */
				send(sock, bad, sizeof(bad), 0);
			}
			else if(check == cur){						/* 80% */
				printf("Frame %s Received \n", act);
				send(sock, act, sizeof(act), 0);  /* send the ACK */
				cur++;
			}
		}
		else if(strcmp(act, bad) == 0){
			send(sock, bad, sizeof(bad), 0);
		}
	}
	close(sock);
	close(s);
	return 0;
}

void int2char(int z)
{
	memset(act, 0, sizeof(act));
	sprintf(act, "%d", z);
}
