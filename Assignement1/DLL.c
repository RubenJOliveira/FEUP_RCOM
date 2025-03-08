#include "DLL.h"


int alarmEnabled = FALSE;
int time_outs = 0;

void timeOut(int signal){
    alarmEnabled = TRUE;
    time_outs++;
}


int LLOPEN(int fd, int com_mode){

    if(com_mode) (void)signal(SIGALRM, timeOut);
}