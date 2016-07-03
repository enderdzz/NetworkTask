#include "simreceiver.h"

void SimReceiver::int2char(int z)
{
    memset(act, 0, sizeof(act));
    sprintf(act, "%d", z);
}

void SimReceiver::run(){
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
    sock = accept(s, (struct sockaddr *) &cli, (socklen_t*)&len);
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
        go_back_n();
    }

    close(sock);
    close(s);
}

void SimReceiver::go_back_n(){
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
        //TODO: change to emit
        query();
}
