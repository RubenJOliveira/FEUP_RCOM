#include "DLL.h"


int alarmEnabled = FALSE;
int time_outs = 0;

void timeOut(int signal){
    alarmEnabled = TRUE;
    time_outs++;
}


int LLOPEN(int fd, int com_mode){

    if(com_mode) (void)signal(SIGALRM, timeOut);

    char byte;
    int state = 0;

    while(time_outs < 4){
        
    }



void transmit_SET(int fd){

    char BCC = SET^C_T;
    char SET_frame[5] = {FLAG, SET, C_T, BCC, FLAG};

    write(fd, SET_frame, 5);
}

void transmit_UA(int fd, int com_mode){

    char UA_frame[5] = {0};
    UA_frame[0] = FLAG;

    if(com_mode)
        UA_frame[1] = A_R;
    else
        UA_frame[1] = A_T;

    write(fd, UA_frame, 5);
}