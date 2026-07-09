#include "uart.h"

int main(){
    cli();
    uart_init(19200, 0);
    sei();

    int byte = 23;

    while(1){
        uart_send_byte(byte);
    }
}