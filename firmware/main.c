#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>
#include "../avr_common/uart.h"

//TO DO
/*write code that has to be uploaded to the arduino: the objective is to sample the analog signal
exactly at 4ms, we'll have main.c that holds the core logic of the microcontroller 
    1. calculate registers values for Timer1, we have to configure it to trigger an ISR every 4ms
    2. ADC config -> search infos about this
    3. ISR logic -> write actual ISR, inside this the ADC will be commanded to read the voltage and store the value
*/

#define MASK(PIN) (1 << PIN)

//USING TIMER 1
#define TCCRB_MASK ((1 << WGM12) | (1 << CS11)) //prescaler set to 8 (CS11 bit set to 1) and CTC mode enabled by setting WGM12 to 1, this ensures that the timer resets when it hits the compare value
#define adc_pin 0 //A0 -> we are referring to the physical pin

volatile uint8_t adc_ready = 0; //no conversion started
volatile uint16_t value = 0;

static void adc_init(void){
    //ADMUX: AVCC ref, ADC0
    ADMUX = MASK(REFS0) | (adc_pin & 0x07);
    ADMUX &= ~MASK(REFS1);

    //channel A0

    ADMUX &= ~MASK(MUX0);
    ADMUX &= ~MASK(MUX1);
    ADMUX &= ~MASK(MUX2);
    ADMUX &= ~MASK(MUX3);
    

    //ADCSRA: enable ADC(ADEN), enable ADC interrupt (ADIE),
    //ADC frequency must be less than 200khz or we lose precision(ADPS2-0). 
    //At 16MHz system vlovk, we must use the full prescale value of 128 to get an ADC clock of 125khz
    ADCSRA = MASK(ADEN) | MASK(ADIE) | MASK(ADPS2) | MASK(ADPS1) | MASK(ADPS0);

    DIDR0 |= (1 << adc_pin);
}


static inline void adc_start_conversion(void) {
    ADMUX = (ADMUX & 0xF0) | 0x00; //keep ref bits, select channel 0
    ADCSRA |= (1 << ADSC); //start conversion
}

static void timer1_init(void){

    TCCR1A = 0;
    TCCR1B = TCCRB_MASK;

    const int timer_duration_ms = 4; //250Hz frequency
    uint16_t ocrval = (uint16_t)(2000 * timer_duration_ms); 
    OCR1A = ocrval - 1; //f ocna =  FclkI/O / (N*(1 + OCRnA)) -> 1 + OCR1A = total cycles 

    TIMSK1 |= (1 << OCIE1A); //enable the timer int

}

ISR(TIMER1_COMPA_vect){
    adc_start_conversion();
}

ISR(ADC_vect){
    value = ADC; //10 bit value so we use 16bit int
    adc_ready = 1;
}


int main(void){
    printf_init();

    cli(); //disable global interrupts during init
    timer1_init();
    adc_init();
    sei(); //enable global interrupts

    adc_start_conversion();
    int buffer[100];
    int len = 0;
    while(1){
        uint16_t sample;
        uint8_t ready;

         /* what does this do:
            the atomic block is a cojncept that's used to disable and then enable again interrupts
            ATOMIC_RESTORESTATE means that the interrupts will be enabled by restoring previously saved values of status register.
            In this case the next ISR of any pending interrupt can be started immediately after this statement, in contrast of 
            sei() function where the next instruction after sei is executed before any pending input
        */
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            ready = adc_ready;
            sample = value;
            if(ready){
                adc_ready = 0;
            }
        }

        if(ready){
            buffer[(len + 1) % 100] = sample; //used for testing
            len++;
        }else{
            _delay_ms(1);
        }

    }
}
