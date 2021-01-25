/*	Author: Nicole Navarro
 *  Partner(s) Name: 
 *	Lab Section:21
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum LED_states{LED_start, on_off, off_on, change_1, change_2} LED_state;

void Tick_LED(){
	switch (LED_state){
		case LED_start:
			LED_state = on_off;
			break;
		case on_off:
			if((PINA & 0x01) > 0){
				LED_state = change_1;
			}
			else{
				LED_state = on_off;
			}
			break;
		case off_on:
			if((PINA & 0x01) > 0){
				LED_state = change_2;
			}
			else{
				LED_state = off_on;
			}
			break;
		case change_1:
			if((PINA & 0x01) > 0){
				LED_state = change_1;
			}
			else{
				LED_state = off_on;
			}
			break;
		case change_2: 
			if((PINA & 0x01) > 0){
				LED_state = change_2;
			}
			else{
				LED_state = on_off;
			}
			break;
		default:
			LED_state = LED_start;
			break;
	}

	switch (LED_state){
		case LED_start:
			PORTB = PORTB | (0x01);
			PORTB = PORTB & ~(0x01 << 1);
			break;
		case change_1:
			PORTB = PORTB & ~(0x01);
			PORTB = PORTB | (0x01 << 1);
			break;
		case change_2:
			PORTB = PORTB | (0x01);
                        PORTB = PORTB & ~(0x01 << 1);
                        break;
		default:
			break;
	}
}



int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0x00; PINA = 0xFF;
	

    //every PA0 is represented by (PINA & 0x01) > 0; 
    //every PB0 is represented by PORTB = PORTB | (0x01 << 0) for on, PORTB = PORTB & ~(0x01 << 0) for off
    //every PB1 is represented by PORTB = PORTB | (0x01 << 1) for on, PORTB = PORTB & ~(0x01 << 1) for off	

    /* Insert your solution below */
	PORTB = 0x01;
	LED_state = LED_start;

    while (1){
	Tick_LED();
    }
    return 1;
}
