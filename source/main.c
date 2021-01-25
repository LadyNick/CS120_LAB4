/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "RIMS.h"
#endif

enum LED_states{LED_start, on_off, off_on, change_1, change_2} LED_state;

void Tick_LED(){
	switch (LED_state){
		case LED_start:
			LED_state = on_off;
			break;
		case on_off:
			LED_state = PA0 ? change_1 : on_off;
			break;
		case off_on:
			LED_state = PA0 ? change_2 : off_on;
			break;
		case change_1:
			LED_state = PA0 ? change_1 : off_on;
			break;
		case change_2: 
			LED_state = PA0 ? change_2 : on_off;
			break;
		default:
			LED_state = LED_start;
			break;
	}

	switch (LED_state){
		case LED_start:
			PB0 = 1;
			PB1 = 0;
			break;
		case change_1:
			PB0 = 0;
			PB1 = 1;
			break;
		case change_2:
			PB0 = 1;
			PB1 = 0;
	}
}



int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0x00; PINA = 0xFF;
	
	unsigned char PA0;

    //every PB0 is represented by PORTB = PORTB | (0x01 << 0) for on, PORTB = PORTB & ~(0x01 << 0) for off
    //every PB1 is represented by PORTB = PORTB | (0x01 << 1) for on, PORTB = PORTB & ~(0x01 << 1)	

    /* Insert your solution below */
	LED_state = LED_start;

    while (1) {
	PA0 = (PINA & 0x01) > 0;
	Tick_LED();
    }
    return 1;
}
