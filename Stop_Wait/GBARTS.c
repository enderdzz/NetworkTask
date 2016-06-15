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
void alpha9(int);

struct sockaddr_in ser;
int s, c = 1, total;

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

	alpha9(total);
	send(s, act, sizeof(act),0);
	int i = 0;
	while(1)
	{
		if(c <= total){
			alpha9(c);
			send(s, act, sizeof(act), 0);
			printf("\nFrame %d Sent\n", c);
		}

		recv(s, act, sizeof(act), 0);
		printf("act = %s\n", act);
		if(strcmp(act, bad) == 0){
			printf("\nTime Out, Resent Frame %d onwards\n",c);	
		}
		else if (c <= total){
			i++;
			c++;	
		}
	}
	close(s);
	return 0;
}

void alpha9(int z)
{
	int k,i=0,j,g;
	k=z;
	while(k>0)
	{
		i++;
		k=k/10;
	}
	g=i;
	i--;
	while(z>0)
	{
		k=z%10;
		act[i]=k+48;
		i--;
		z=z/10;
	}
	act[g]='\0';
}

