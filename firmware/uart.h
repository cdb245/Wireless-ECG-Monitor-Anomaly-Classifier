#define F_CPU 16000000UL

#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>


#define MASK(PIN) (1 << (PIN))
void uart_init(uint32_t baud);
void uart_send_byte(uint8_t c);
void uart_send_array(uint8_t *c,uint16_t len );