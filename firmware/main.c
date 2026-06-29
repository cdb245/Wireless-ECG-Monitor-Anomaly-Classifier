#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

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
#define analog_reference 1
#define adc_pin 0 //A0 -> we are referring to the physical pin

volatile uint16_t value = 0;

ISR(TIMER1_COMPA_vect){
    ADCSRA |= MASK(ADSC);
    while(ADCSRA & MASK(ADSC));
    value = ADC;
}


int main(void){

    TCCR1A = 0;
    TCCR1B = TCCRB_MASK;

    const int timer_duration_ms = 4; 
    uint16_t ocrval = (uint16_t)(2000 * timer_duration_ms);
    OCR1A = ocrval - 1; //f ocna =  FclkI/O / (2*N*(1 + OCRnA)) -> 1 + OCR1A = total cycles 

    //clear int
    cli();
    TIMSK1 |= (1 << OCIE1A); //enable the timer int
    sei();

    //ADC - Initialization
    
    ADMUX = (analog_reference << 6) | (adc_pin & 0x07); //set REFS0 to 1 and sets MUX3:0 bits to 0
    //ADC frequency must be less than 200khz or we lose precision. At 16MHz system vlovk, we must use the full prescale value of 128 to get an ADC clock of 125khz
    ADCSRA = MASK(ADEN) | MASK(ADPS2) | MASK(ADPS1) | MASK(ADPS0);

    while(1){
        
    }
}
