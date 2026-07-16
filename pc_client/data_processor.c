//this module takes a 2 byte array, merges the 2 bytes into a 10 bit integers and writes the number on a file
#include "data_processor.h"

int write_to_dest(int fd, uint8_t * array){

    /*
    merging together the splitted 10 bit integer: in the first cell we have the upper value that has the upper bit set to 1 
    and 3 lowewr bits to keep, so we get rid of the first bit and keep the last three shifting them up
    then we or the upper part with the lower part, the second cell of the array has the upper bit set to 0 and 7 lower bits 
    we have to keep, so we "get rid" (we don't actually do anything we just keep the lowe 7 bit, the & is for security) of the flag and we merge everything
    */
    uint16_t value = ((array[0] & 0x07) << 7) | (array[1] & 0x7F); 
    char buf[6];
    int len = sprintf(buf, "%u\n", value);
    if(write(fd, buf, len) < 0){
        printf("error %d writing to dest file", errno);
        return -1;
    }
    return 0;

}