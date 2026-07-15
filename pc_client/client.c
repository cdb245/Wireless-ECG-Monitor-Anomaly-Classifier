#include <termios.h>
#include <fcntl.h>
#include <errno.h>

//rn this is a prototype: most of the code is from the course's slides but I have to analyze it and understand it
//this is just the scheleton of what it will be
//I have to decide also the TYPE of file i'll write to (.txt?.csv??)


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

    tty.c_cflag &=  ~(PARENB | PARODD);
    tty.c_cflag |= parity;
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;

    if(tcsetattr(fd, TCSANOW, &tty) != 0){

        printf("error %d from tcsetattr", errno);
        return -1;

    }
    return 0;
}


int main(){

    int fd_arduino = open("dev/tty/USB0", O_RDONLY | O_NOCTTY | O_SYNC );
    if(fd_arduino < 0){
        printf("error %d, cannot open serial", errno);
    }

    int fd_dest = open("Wireless-ECG-Monitor-Anomaly-Classifier/pc_client", O_RDWR);
    if(fd_dest < 0){
        printf("error %d, cannot open dest file", errno);
    }

    if(set_serial_attribs(fd_arduino, BAUDRATE, 0) < 0){
        _exit(-1);
    }

    //read from arduino and write on another file
    //TO DO:
    /*
        read two bytes from serial
        reconstruct 10 bit integer
        write integer in file
        
        think of a way to stop reading and writing -> condition in while loop (depends on firmware?? we'll see)
    */

}