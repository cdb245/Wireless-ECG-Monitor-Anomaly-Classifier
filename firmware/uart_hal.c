#include "uart_hal.h"

 //add interrupts

volatile static uint8_t uart_tx_busy = 1;

ISR(USART_TX_vect){
    uart_tx_busy = 1;
}


void uart_unit(uint32_t baud, uint8_t high_speed){

    uint8_t speed = 16;

    if(high_speed != 0){
        speed = high_speed;
        UCSR0A |= MASK(U2X0); //enable high speed
    }

    baud = (DF_CPU / (spped * baud)) - 1; //we need uint32_t bc with uint16_t the value trunkates and we get the wrong value

    UBRR0H = (baud & 0x0F00) >> 8; //masking the four bits in the pos of the baud rate and then shifting down so they fit in a 8 bit value
    UBRR0L = (baud & 0x00FF); //so we have the lower 4 bits

    //only set TX bits because we do not need to receive anything
    UCSR0B |= MASK(TXEN0) | MASK(TXCIE0); 

}

void uart_send_byte(uint8_t c){
    while(uart_tx_busy == 0); //wait until there's something to read
    uart_tx_busy = 0; //means that we're going to send something
    UDR0 = c; //write character on UDR0
}

void uart_send_array(uint8_t *c,uint16_t len ){ //so we can send any binary data over!
    for(uint16_t i = 0; i < len; ++i){
        uart_send_byte(c[i])
    }
}
