#include <termios.h>
#include <fcntl.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


#define PORT "/dev/ttyUSB0"

int set_serial_attribs(int fd, int speed, int parity);
int open_serial(char* port);
int populate_array(int fd, uint8_t* dest);