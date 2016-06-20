#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <time.h>     /* random value */
#include <ctype.h>    /* atoi function */

#define WindowSize 15
#define P1 50
#define P2 10

char act[10];
char bad[20] = "Time-out ";

void int2char(int);

struct sockaddr_in ser;
int s, total;

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

/************************* go back n **************************/
    int i, cur = 1, origin = 1;
    while(1) {
        if(cur <= total){
          for(i = 0; i < WindowSize; i++) {
              int random = rand() % P1;
              if(random < P2){
                send(s, bad, sizeof(bad), 0);
              }
              else {
                int2char(cur);
                send(s, act, sizeof(act), 0);
              }

              if(cur <= total) {
                  printf("Frame %d Sent\n",cur);
                  cur++;
              }
          }

          for(i = 0; i < WindowSize; i++){
            recv(s, act, sizeof(act), 0);
            if(strcmp(act, bad) == 0){
              printf("Time out. Resent the %d Frame\n", origin);
              cur = origin;
              break;
            }
            else {
              int now = atoi(act);
              int left = cur - WindowSize, right = cur;
              //printf("l = %d, r = %d\n", left, right);
              if(now >= left && now < right){
                printf("The %d frame got ACK.\n", now);
                origin++;
              }
            }
            if(origin > total) break;
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
