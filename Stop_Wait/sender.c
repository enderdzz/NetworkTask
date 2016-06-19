#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <time.h>
#include <ctype.h>

#define P1 50       /* denominator */
#define P2 10				/* numerator */

char act[10];
char bad[10] = "Time Out ";
void int2char(int);

struct sockaddr_in ser;                  /* define the server */
int s, total;
unsigned int sseed;

int main()
{
	s = socket(AF_INET, SOCK_STREAM, 0);
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
	scanf("%d",&total);

	sseed = (unsigned int)time(NULL); /* initial the random value */
	srand(sseed);

	int2char(total);
	send(s, act, sizeof(act),0);
/************************ stop and wait ****************************/
	int cur = 1, canSend = 1;
	while(1)
	{
		if(canSend){
			int random = rand() % P1;
			if(random < P2){						    /* 20% */
				printf("Frame %d Sent\n", cur);
				send(s, bad, sizeof(bad), 0);
				canSend = 0;
			}
			else {						/* 80% */
				int2char(cur);
				send(s, act, sizeof(act), 0);
				printf("Frame %d Sent\n", cur);
				canSend = 0;
			}
		}

		recv(s, act, sizeof(act), 0);
		if(strlen(act) != 0){
			if(strcmp(act, bad) == 0){
				printf("Time Out, Resent Frame %d onwards\n", cur);
				canSend = 1;
			}
			else {
				int check = atoi(act);
				if(check == cur){
					printf("recv from receiver as ACK act = %s\n", act);
					cur++;
					if(cur > total) canSend = 0;
					else canSend = 1;
				}
			}
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
