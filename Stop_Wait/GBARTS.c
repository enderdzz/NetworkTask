#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <time.h>
#include <ctype.h>

char act[10];
char bad[10] = "Time Out ";
void int2char(int);

struct sockaddr_in ser;                  /* define the server */
int s, total;

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

	int2char(total);
	send(s, act, sizeof(act),0);

	int cur = 1;
/************************ stop and wait ****************************/
	while(1)
	{
		if(cur <= total){
			int2char(cur);
			send(s, act, sizeof(act), 0);
			printf("Frame %d Sent\n", cur);

			recv(s, act, sizeof(act), 0);
			if(strlen(act) != 0){
				if(strcmp(act, bad) == 0){
					printf("Time Out, Resent Frame %d onwards\n", cur);
				}
				else {
					int check = atoi(act);
					if(check == cur){
						printf("recv from receiver AS ACK act = %s\n", act);
						cur++;
					}
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
