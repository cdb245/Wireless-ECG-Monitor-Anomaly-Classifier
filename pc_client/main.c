#include <stdlib.h>
#include "client.h"
#include "data_processor.h"


int main(){

    /*
    in here we have to orchestrate everything: so we open the serial, we allocate the array
    and we populate it, then we open the dest file and call data_processor
    */

    //manage while loop
    /*
    
    the frequence is 250HZ so we will set a time interval in which the measurement will be done
    the time slot will depend on the waves we want to capture, for now we will measure a 20 seconds signal
    just to test if everything works

    if the frequence is 250HZ we will read 250 samples per second for a total of 250 * 20 = 5000 samples (10.000 bytes)

    */

    int arduino_fd = open_serial(PORT);
    uint8_t * array = (uint8_t*)malloc(2);
    int dest_file = open("ECGdata.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
    int samples_collected = 0;

    while(samples_collected < 5000){

        if(populate_array(arduino_fd, array) < 0){
            _exit(-1);
        }

        if(write_to_dest(dest_file, array) < 0){
            _exit(-1);
        }

        samples_collected ++;


    }

    close(arduino_fd);
    close(dest_file);
    return 0;

}