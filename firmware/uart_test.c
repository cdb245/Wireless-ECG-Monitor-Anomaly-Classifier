#include "uart.h"

/*
pt 1 -> things are sent through serial !! done
pt 2 -> now we have to successfully send a 10 bit integer through serial, maybe a 2 int array? but how can I store it in them?
*/


int main(){
    cli();
    uart_init(19200); //set baudrate 
    sei();

    uint16_t mock_ADC = 835; //fix a value to send for testing

    uint8_t upper = 0x80 | (mock_ADC >> 7); //this sets the first bit of upper to 1 and takes the first 3 bits of my 10 bits int
    uint8_t lower = mock_ADC & 0x7F; //this takes the remaining 7 bits from mock_ADC leaving the high bit set to 0

    //why? I need a flag that tells me if what I'm reading is the upper half or the lower half, this way I'm sure that the upper half will always have
    //a value >= 128 (first bit is forced to 1) and the lower half will be < 128 (first bit is forced to 0) -> easy check!

    uint8_t array[2] = {upper, lower};
    uint8_t len = 2;


    while(1){
        uart_send_array(array, len);
    }
}