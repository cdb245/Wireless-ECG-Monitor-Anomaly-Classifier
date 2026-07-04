#ifndef UART_HAL_H_
#define UART_HAL_H_

#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>

void uart_unit(uint32_t baud, uint8_t high_speed);
void uart_send_byte(uint8_t c);
void uart_send_array(uint8_t *c,uint16_t len );