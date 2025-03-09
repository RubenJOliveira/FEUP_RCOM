#include "DLL.h"


int alarmEnabled = FALSE;
int time_outs = 0;

void timeOut(int signal){
    alarmEnabled = FALSE;
    time_outs++;
}


int LLOPEN(int fd, int com_mode){

    if(com_mode) (void)signal(SIGALRM, timeOut);

    char byte[5];
    int state = 0;
    

    while(time_outs < 4){
        
        if(com_mode){
            transmit_SET(fd);
            alarm(1);
            alarmEnabled = TRUE;
        }
        else
            alarmEnabled = TRUE;           // For the receiver, the alarm is not needed
                                           // But it has to be ON so that it enters the state machine

        while( (state != 5) && alarmEnabled){
            read(fd, &byte[state], 1);

            switch (state)
            {
            case 0:
                if(byte[state] == FLAG)
                    state++;

                break;
            
            case 1:
                if(com_mode)
                    byte[state] = A_T;
                
                else if(com_mode == 0)
                    byte[state] = A_R;

                if(byte[state] == byte[1])
                    state++;

                else
                    state = 0;

                break;
            
            case 2:
            if(com_mode)
                byte[state] = UA;
        
            else if(com_mode == 0)
                byte[state] = SET;

            if(byte[state] == byte[2])
                state++;

            else if(byte[state] == FLAG)
                state = 1;

            else
                state = 0;

                break;

            case 3:
                if(byte[state] == byte[1]^byte[2])
                    state++;

                else if(byte[state] == FLAG)
                    state = 1;
                
                else
                    state = 0;

                break;
            
            case 4:
                if(byte[state] == FLAG){
                    state++;

                    if(com_mode == 0)
                        transmit_UA(fd, com_mode);
                    
                    printf("Connection established!\n");
                    
                    return 1;
                }
                
                else
                    state = 0;
                
                break;
            
            }
        }
    }

    printf("Connection failed: timeout\n");
    return -1;
}


void transmit_SET(int fd){

    unsigned char BCC = SET^C_T;
    unsigned char SET_frame[5] = {FLAG, SET, C_T, BCC, FLAG};

    write(fd, SET_frame, 5);
}

void transmit_UA(int fd, int com_mode){

    unsigned char UA_frame[5] = {0};
    UA_frame[0] = FLAG;

    if(com_mode)
        UA_frame[1] = A_R;
    else
        UA_frame[1] = A_T;
    
    UA_frame[2] = UA;
    UA_frame[3] = UA_frame[1]^UA_frame[2];
    UA_frame[4] = FLAG;

    write(fd, UA_frame, 5);
}