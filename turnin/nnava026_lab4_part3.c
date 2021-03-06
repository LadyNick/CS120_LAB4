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

enum lock_states{start = 1, button = 2, hash_p = 3, hash_r = 4, unlocky_p = 5, unlocky_r = 6} lock_state;

void Tick_Lock(){
	
	switch(lock_state){
		case start:
			PORTB = 0x00;
			lock_state = button;
			break;
		case button:
			if(PINA == 0x80){
				PORTB = 0x00;
			}
			if(PINA == 0x04){
				lock_state = hash_p;
			}
			else{
				lock_state = button;
			}
			break;
		case hash_p:
			if(PINA == 0x04){
				lock_state = hash_p;
			}
			else if(PINA == 0x00){
				lock_state = hash_r;
			}
			else{
				lock_state = button;
			}
			break;
		case hash_r:
			if(PINA == 0x80){
                                PORTB = 0x00;
				lock_state = button;
                        }
			if(PINA == 0x02){
				lock_state = unlocky_p;
			}
			else if( PINA == 0x00){
				lock_state = hash_r;
			}
			else if( PINA == 0x04){
				lock_state = hash_p;
			}
			else{
				lock_state = button;
			}
			break;
		case unlocky_p:
			if(PINA == 0x00){
				lock_state = unlocky_r;
			}
			else if(PINA == 0x02){
				lock_state = unlocky_p;
			}
			else{
				lock_state = button;
			}
			break;
		case unlocky_r:
			if(PINA == 0x80){
                                PORTB = 0x00;
				lock_state = button;
                        }
			lock_state = button;
			break;
		default:
			lock_state = start;
			break;
	}

	switch(lock_state){
		case unlocky_p:
			PORTB = 0x01;
			break;
		default:
			break;
	
	}

}



int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRA = 0x00; PINA = 0xFF;

    /* Insert your solution below */

	lock_state = start;

    while (1){
	PORTC = lock_state;
	Tick_Lock();
    }
    return 1;
}
