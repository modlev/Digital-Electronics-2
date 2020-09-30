/*
 * GccApplication1.c
 *
 * Created: 2020-09-30 09:52:17
 * Author : Modestas
 */ 
/* Defines -----------------------------------------------------------*/
#define LED_1  PB1     // AVR pin where LED is connected
#define LED_2  PB5 
#define LED_3  PC0 
#define LED_4  PC2
#define LED_5  PC5 
#define BLINK_DELAY 200 //delay time in milliseconds
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions

/* Functions ---------------------------------------------------------*/
/**
 * Make a Knight Rider with 5 LEDs
 */
int main(void)
{
    // Set pin as output in Data Direction Register...
    DDRB = DDRB | (1<<LED_1);
	DDRB = DDRB | (1<<LED_2);
	DDRC = DDRC | (1<<LED_3);
	DDRC = DDRC | (1<<LED_4);
	DDRC = DDRC | (1<<LED_5);
    // ...and turn LED off in Data Register
    PORTB = PORTB & ~(1<<LED_1);
	PORTB = PORTB & ~(1<<LED_2);
	PORTC = PORTC & ~(1<<LED_3);
	PORTC = PORTC & ~(1<<LED_4);
	PORTC = PORTC & ~(1<<LED_5);

    // Infinite loop
    while (1)
    {
		PORTB = PORTB^(1<<LED_1);  
		_delay_ms(BLINK_DELAY);
		PORTB = PORTB^(1<<LED_1);  
		PORTB = PORTB^(1<<LED_2);  
		_delay_ms(BLINK_DELAY);
		PORTB = PORTB^(1<<LED_2);
		PORTC = PORTC^(1<<LED_3);
		_delay_ms(BLINK_DELAY);
		PORTC = PORTC^(1<<LED_3);
		PORTC = PORTC^(1<<LED_4);
		_delay_ms(BLINK_DELAY);
		PORTC = PORTC^(1<<LED_4);
		PORTC = PORTC^(1<<LED_5);
		_delay_ms(BLINK_DELAY);
		PORTC = PORTC^(1<<LED_5);
		PORTC = PORTC^(1<<LED_4);
		_delay_ms(BLINK_DELAY);
		PORTC = PORTC^(1<<LED_4);
		PORTC = PORTC^(1<<LED_3);
		_delay_ms(BLINK_DELAY);
		PORTC = PORTC^(1<<LED_3);
		PORTB = PORTB^(1<<LED_2);
		_delay_ms(BLINK_DELAY);
		PORTB = PORTB^(1<<LED_2);
    }

    // Will never reach this
    return 0;
}

