//this module is used to communicate with the serial. This takes the bytes and saves them into the array
#include "client.h"

//rn this is a prototype: most of the code is from the course's slides but I have to analyze it and understand it
//this is just the scheleton of what it will be
//I have to decide also the TYPE of file i'll write to (.txt?.csv??)
//also make the makefile


#define BAUDRATE 19200

int set_serial_attribs(int fd, int speed, int parity){

    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if(tcgetattr(fd, &tty) != 0) {
        printf("error %d from tcgetattr", errno);
        return -1;
    }
    if(speed == BAUDRATE){
        speed = B19200;
    }else{
        printf("invalid speed %d", speed);
        return -1;
    }

    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);
    cfmakeraw(&tty);
    //c_cflags describes the hardware control of the terminal
    tty.c_cflag &=  ~(PARENB | PARODD); //PARENB enables parity, PARODD specifies odd parity (we get rid of these)
    tty.c_cflag |= parity;
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; //set character size to 8 bits

    if(tcsetattr(fd, TCSANOW, &tty) != 0){ //TCSANOW sets parameters associated with the terminal from the reference termios structure

        printf("error %d from tcsetattr", errno);
        return -1;

    }
    return 0;
}

int open_serial(char* port){
    int fd_arduino = open(port, O_RDONLY | O_NOCTTY | O_SYNC ); //O_NOCTTY makes sure that the terminal won't become the process's controlling terminal even if the process does not have one
    //O_SYNC write op in the file will complete according to the requirements of the synchronized I/O file integrity completion
    if(fd_arduino < 0){
        printf("error %d, cannot open serial", errno);
    }

    if(set_serial_attribs(fd_arduino, BAUDRATE, 0) < 0){
        _exit(-1);
    }

    return fd_arduino;
}


int populate_array(int fd, uint8_t* dest){
    //TO DO:
    /*
        read two bytes from serial and put them in an array -> CHEK that the first element is actually the right first element 
    */

    int bytes_read = 0;
    int read_val;
    uint8_t temp = 0;
    uint8_t is_first_byte = 0;
    while(bytes_read < 2){
        read_val = read(fd, &temp, 1);
        if(read_val < 0){
            printf("error %d reading from serial", errno);
            return -1;
        }
        if(temp >= 128){
            is_first_byte = 1;
        }
        if(is_first_byte){
            dest[bytes_read] = temp;
            bytes_read += 1;
        }
    }

    return 0;

}
