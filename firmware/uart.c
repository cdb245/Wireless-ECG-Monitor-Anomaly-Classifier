#include "uart.h"


/*

what is this code doing:
uart_init() computes the UBRR value from F_CPU and the desired baud rate,
splits it acrosso UBRR0H/UBRR0L and enables the transmitter plus the transmit complete interrupt (TCXCIE0)

uart_tx_ready is a volatile flag shared between main context and the USART_TX_vect ISR -> without it being volatile the computer could cache it
and never see the ISR's update

uart_send_byte() blocks until the flag says it's safe to write UDR0, then writes it and flips the flag to indicate "busy"

uart_send_array() just calls uart_send_byte() in a loop for binary safe transmission

uart_send_string() works the same as uart_send_array() but instead of relying on a known length it waits for the terminator


*/ 



/*ANALYSIS: 
trace the value of uart_tx_ready through a whole send cycle1. 
    USART_TX_vect(TCX) fires when a transmission has FINISHED!! it means that UDR0 is empty and
    the shift register has pushed the last bit out

    before anything has been sent out uart_tx_ready should be 1, representing the fact that the transmission is ready to start
    then when transmission starts the bit is set 0 and when the transmission ends and the ISR is triggered the bit is set to 1


*/
volatile static uint8_t uart_tx_ready = 1;

ISR(USART_TX_vect){
    uart_tx_ready = 1; 
}


void uart_init(uint32_t baud){

    uint8_t speed = 16;
    baud = (F_CPU / (speed * baud)) - 1; //we need uint32_t bc with uint16_t the value trunkates and we get the wrong value

    UBRR0H = (baud & 0x0F00) >> 8; //masking the four bits in the pos of the baud rate and then shifting down so they fit in a 8 bit value
    UBRR0L = (baud & 0x00FF); //so we have the lower 4 bits

    //only set TX bits because we do not need to receive anything
    UCSR0B |= MASK(TXEN0) | MASK(TXCIE0); 

}

void uart_send_byte(uint8_t c){
    while(uart_tx_ready == 0); //wait until you can send something
    uart_tx_ready = 0; //means that we're going to send something
    UDR0 = c; //write character on UDR0
}

void uart_send_array(uint8_t *c,uint16_t len ){ //so we can send any binary data over!
    for(uint16_t i = 0; i < len; ++i){
        uart_send_byte(c[i]);
    }
}
