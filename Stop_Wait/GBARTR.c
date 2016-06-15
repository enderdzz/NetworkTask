#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <ctype.h>

#define P1 50
#define P2 10

char act[10];
char bad[20] = "Time Out ";
void alpha9(int);

struct sockaddr_in ser,cli;   /* server & client */
int s, err, sock, total;
unsigned int sseed;

int main()
{
	int i,j,c=1,n;

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
	n=sizeof(cli);
	sock = accept(s, (struct sockaddr *)&cli, &n);
	puts("TCP Connection Established.");

	sseed = (unsigned int)time(NULL); /* initial the random value */
	srand(sseed);

	recv(sock, act, sizeof(act), 0);
	total = atoi(act);
	printf("total = %d\n", total);
	while(1){
		recv(sock, act, sizeof(act), 0);
		//printf("act = %s\n", act);
		if(strcmp(act, bad) != 0 && c <= total){	
			j = rand() % P1;
			if(j < P2){
				send(sock, bad, sizeof(bad), 0);
			}
			else {
				printf("\nFrame %s Received \n",act);
				send(sock, act, sizeof(act), 0);
			}
		}
		//if(c == f)break;
	}
	close(sock);
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
