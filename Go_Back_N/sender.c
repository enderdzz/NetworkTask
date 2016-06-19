#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <time.h>     /* random value */
#include <ctype.h>    /* atoi function */

#define W 5

char act[10];
char bad[20] = "Time-out ";

void int2char(int);

struct sockaddr_in ser;
int s, total;

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

    connect(s, (struct sockaddr *) &ser, sizeof(ser));
    puts("TCP Connection Established.");

    puts("Enter the number of Frames: ");
    scanf("%d", &total);
    int2char(total);
    send(s, act, sizeof(act), 0);

/************************* go back n **************************/
    int w_tmp, cur = 1, i, j, p = 0, e = 0;
    while(1) {
        for(i = 0; i < W; i++) {
            int2char(cur);
            send(s, act, sizeof(act), 0);
            if(cur <= total) {
                printf("Frame %d Sent\n",cur);
                cur++;
            }
        }
        i = 0;
        w_tmp = W;
        while(i < W)
        {
            recv(s, act, sizeof(act), 0);
            p = atoi(act);
            if(strcmp(act,bad) == 0) {
                e = cur - w_tmp;
		            if(e < total) {
		                printf("Time Out, Resent Frame %d onwards.\n", e);
		            }
		            break;
            }
            else {
                if(p <= total) {
                    printf("Frame %s Acknowledged\n", act);
                    w_tmp--;
                }
                else {
                    break;
                }
            }
            if(p > total) {
                break;
            }
            i++;
        }
        if(w_tmp == 0 && cur > total) {
            send(s, bad, sizeof(bad), 0);
            break;
        }
        else {
            cur = cur - w_tmp;
            w_tmp = W;
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
