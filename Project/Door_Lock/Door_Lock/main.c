/*
 * Door_Lock.c
 *
 * Created: 2020-11-30 17:24:45
 * Author : Modestas
 */ 

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#ifndef F_CPU
#define F_CPU 16000000
#endif
#include <util/delay.h>		// Functions for busy-wait delay loops 
#include <avr/io.h>			// AVR device-specific IO definitions
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function
#include "function.h"		// Library of my functions
#include "uart.h"
#include <stdint.h>

int main(void)
{
	// Configure ADC to convert PC0[A0] analog value
	// Set ADC reference to AVcc
	ADMUX |= (1 << REFS0);
	// Set input channet to ADC0
	ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0));
	// Enable ADC module
	ADCSRA |=  (1 << ADEN);
	// Enable conversion complete interrupt
	ADCSRA |= (1 << ADIE);
	// Set clock prescaler to 128
	ADCSRA |= ((1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2));

	// Initialize LCD display
	lcd_init(LCD_DISP_ON);

	// Set pointer to beginning of CGRAM memory
	lcd_command(1 << LCD_CGRAM);
	
	// Set DDRAM address
	lcd_command(1 << LCD_DDRAM);
	
	// Display first custom character
	lcd_gotoxy(0,0);
	lcd_puts("Enter password:");
	setup();		// Setting up all the I/O ports
	
	
	// 
	TIM0_overflow_interrupt_enable();
	TIM0_overflow_16ms();
	 
	// Initiate uart
	uart_init(UART_BAUD_SELECT(9600,F_CPU));
    
	// Enable interrupts
	sei();
    // Infinite loop
    while(1)
    {
	}
}
ISR(TIMER0_OVF_vect)
{
	// Start ADC conversion
	ADCSRA |= (1 << ADSC);
}
ISR(ADC_vect)
{	
	// Time dedicated to insert a password
	static uint8_t time = 0; 
	// Time is always amplified by 1
	time++;					
	// Pressed key
	static uint8_t key;	
	// Quantity of keys pressed
	static uint8_t quantity = 0; 
	/* Correct number matrix (if changed, need 
	   to change the function ArrayComparison  */
	static uint8_t correct_num[2][4] =
	{
		{1, 2, 3, 4},// first password
		{5, 6, 7, 8} // second password
	};
	// Massive of entered number
	static uint8_t entered_num[4];
	/* How many attempt did the user 
	   did to write the password */
	static uint8_t tries = 0;
	/* If the number of tries are not exceeding 4
	   and the time is not more than 5 seconds 
	   the code for entering password is executed */
	if(tries < 4 && time < 48)
	{
		/* Finding the pressed key and
		   saving in key variable */
		key = determineKey(scanKeyboard(),quantity);
		/*
		 Delay is required so that the keystroke
		 wouldn't be scanned multiple times
		*/
		_delay_ms(100);
		/* Pressed key is added to the required 
		   place in the massive */
		entered_num[quantity]=key;
		/* If the key is not pressed this step 
		   is gonna be skipped*/
		if(key != 15) 
		{
			/* Quantity of keystrokes are amplified 
		       after every keystroke */
			quantity++; 
			/* If quantity reaches 4 = the maximum
			   number of password code this part of 
			   the code is executed */
			if(quantity==4 ) 
			{
				/* since the quantity is already
				   at the max */
				quantity = 0;
				// Go to LCD second line
				lcd_gotoxy(0,1);
				/* If the entered number is in the 
				   correct number matrix than this 
				   part of the code is executed 
				   and the doors unlock */
				if(ArrayComparison(correct_num,entered_num))
				{
					// text is written in uart 
					uart_puts("Correct password\n\r");
					// text is written in LCD
					lcd_puts("Correct password");
					/* Delay so that the written 
					   text would be seen */
					_delay_ms(200);
					// Green LED blinks 
					GreenBlink();
					// Doors are unlocked 
					Unlock();
					// Time is returned to 0 
					time = 0;
					/* The correct password was 
					   inserted so number of 
					   tried attempts to write the
					   password are reduced to 0 */
					tries = 0;
				}
				/* If the wrong password is inserted
				   than this part of code is executed */
				else
				{
					// In uart this text is written
					uart_puts("Incorrect password\n\r");
					/* LCD show that the password was 
					incorrect */
					lcd_puts("Incorrect");
					// Delay to show text
					_delay_ms(200);
					RedBlink(); // Red LED blinks
					/* Buzzer sound to show that the
					   inserted code was wrong */ 
					Buzzer_sound();
					// Times reduced to 0
					time = 0;
					// Attempt number is increased by 1
					tries++;
				}
			}
		}
	}
	/* if the attempts to write the password exceeds 
	   4 times than this part of the code is 
	   executed */
	else if(tries >3)
	{
		// tries are used as a time variable
		tries++;
		/* time reduced to 0 so that the code
		   would not jump between code */
		time = 0;
		lcd_gotoxy(0,1);
		lcd_puts("Too much attempts");
		/* When the LCD is read then the 
		   words change*/
		if(tries == 192)
		{
			lcd_gotoxy(0,1);
			lcd_puts("You may enter the code");
		}
		/* Again do the same as before*/
		else if(tries == 232)
		{
			uart_puts("Exceeded 4 times limit\n\r");
			/* Except this time tries are reduced
			   to 0 and becomes the number of 
			   attempts again, because it is the 
			   last code part of waiting after 
			   4 wrong attempts and it clears the 
			   LCD second line*/
			tries = 0;
			lcd_gotoxy(0,1);
			lcd_puts("                       ");
		}
	}
	/* when attempt time reaches 5 seconds
	   the LCD shows that the attempt time
	   has ended and shows the text written 
	   below, time is used for the delay,
	   so that the user could see the code*/
	else if(time > 47 && time < 101)
	{
		lcd_gotoxy(0,1);
		lcd_puts("Took to much time");
		time++;
	}
	else if(time > 100 && time < 170)
	{
		lcd_gotoxy(0,1);
		lcd_puts("Try again              ");
		time++;
	}
	else if(time > 169)
	{
		uart_puts("Time limit is over\n\r");
		lcd_gotoxy(0,1);
		lcd_puts("                       ");
		time =0;
		quantity=0;
	}
}