/*
 * GccApplication1.c
 *
 * Created: 2020-09-30 09:52:17
 * Author : Modestas
 */ 
/* Defines -----------------------------------------------------------*/
#define LED_BLUE   PB5     // AVR pin where blue LED is connected
#define LED_RED    PC0     // AVR pin where red LED is connected
#define BTN		   PD0		//Button
#define BLINK_DELAY 1000
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions

/* Functions ---------------------------------------------------------*/
/**
 * Main function where the program execution begins. Toggle two LEDs 
 * when a push button is pressed.
 */
int main(void)
{
    /* GREEN LED */
    // Set pin as output in Data Direction Register...
    DDRB = DDRB | (1<<LED_BLUE);
    // ...and turn LED off in Data Register
    PORTB = PORTB & ~(1<<LED_BLUE);

    /* second LED */
    // WRITE YOUR CODE HERE
	DDRC = DDRC | (1<<LED_RED);
	PORTC = PORTC & ~(1<<LED_RED);//Turn off
	
	//Push button
	DDRD = DDRD & ~(1<<BTN); //input
	PORTD = PORTD |(1<<BTN);//enable internal pull-up
	
    // Infinite loop
    while (1)
    {
        // Pause several milliseconds
        _delay_ms(BLINK_DELAY);

        // WRITE YOUR CODE HERE
		if(bit_is_clear(PIND,BTN))
		{
			PORTB = PORTB^(1<<LED_BLUE); //Invert
			PORTC = PORTC^(1<<LED_RED);  //Invert
		}
		
    }

    // Will never reach this
    return 0;
}

