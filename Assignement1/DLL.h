#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>
#include <unistd.h>


#define BAUDRATE B38400
#define MODEMDEVICE "/dev/ttyS1"
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1


#define FLAG 0x7E
#define A_T 0x03
#define C_T 0x03
#define A_R 0x01
#define C_R 0x07
#define BCC_T 0x00
#define BCC_R 0x04

#define RR0 0x05
#define RR1 0x85
#define REJ0 0x01
#define REJ1 0x81

#define UA 0x07
#define SET 0x03
#define DISC 0x0B
#define START 0x01
#define END 0x02


int LLOPEN(int fd, int com_mode);
