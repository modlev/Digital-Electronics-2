/*
 * function.c
 *
 * Created: 2020-12-11 16:18:52
 *  Author: Modestas
 */ 
#define F_CPU 16000000
#include <util/delay.h> 

#define COLUMN1 PORTC4
#define COLUMN2 PORTC5
#define COLUMN3 PORTC6
#define ROW1 PINB0
#define ROW2 PINB1
#define ROW3 PINB2
#define ROW4 PINB3

#define LED_RED  PD1
#define LED_GREEN  PD0

#define Lock  PC0
#define Buzzer  PC1
#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "gpio.h"
#include "function.h"
	void Unlock()
	{
		// Output to the lock is high
		GPIO_write_high(&PORTC,Lock);
		_delay_ms(100);
		// Output is set low again
		GPIO_write_low(&PORTC,Lock);
	}
	void Buzzer_sound()
	{
		// Output to the buzzes is set to high
		GPIO_write_high(&PORTC,Buzzer);
		_delay_ms(300);
		// Output is set low again
		GPIO_write_low(&PORTC,Buzzer);
	}
	void RedBlink()
	{
		// RED LED is turned on
		GPIO_toggle(&PORTD,LED_RED);
		// Short delay
		_delay_us(1);
		// The text is cleaned in the 2nd line
		lcd_gotoxy(0,1);
		lcd_puts("                                      ");
		// RED LED is turned off
		GPIO_toggle(&PORTD,LED_RED);
	}
	void GreenBlink()
	{
		// GREEN led is turned on
		GPIO_toggle(&PORTD,LED_GREEN);
		// Short delay
		_delay_us(1);
		// The text in the 2nd line is deleted
		lcd_gotoxy(0,1);
		lcd_puts("                                      ");
		// GREEN LED is tunred off
		GPIO_toggle(&PORTD,LED_GREEN);
	}
	uint8_t scanKeyboard()
	{
		
		
		PORTC  |= (1<< COLUMN1) | (1<<COLUMN2) | (1<< COLUMN3);

		
		//variable that will store the state of the row pins
		uint8_t rowState = PORTB;
		// A mask for the variable
		uint8_t masker = 0b00001111;
		// Reading 4, 5, 6 ports of PORTC
		for(int i = 4; i < 7; i++)
		{
			PORTC &= ~(1 << i);
			
			/*Read all rows simultaneously and record 
			  the data to be used in if statements later
			  for indicating the specific key pressed*/
			rowState = (masker & PINB);
			
			if(rowState != PORTB)
			{
				return PORTC | rowState;
			}
			else {}


			//Reset
			PORTC |= (1<< COLUMN1) | (1<<COLUMN2) | (1<< COLUMN3);
			rowState = PORTB;
		}
		return 0;
	}
	uint8_t determineKey(uint8_t scannedKey, uint8_t possition)
	{
		
		if (scannedKey == 0b01101110)
		{
			//Do something that indicates 1 has been pressed
			lcd_gotoxy(possition,1);
			lcd_puts("*");
			return 1;
		}
		else if (scannedKey == 0b01011110)
		{
			//Do something that indicates 2 has been pressed
			lcd_gotoxy(possition,1);
			lcd_puts("*");
			return 2;
		}
		else if (scannedKey == 0b00111110)
		{
			//Do something that indicates 3 has been pressed
			lcd_gotoxy(possition,1);
			lcd_puts("*");
			return 3;
		}
		else if (scannedKey == 0b01101101)
		{
			//Do something that indicates 4 has been pressed
			lcd_gotoxy(possition,1);
			lcd_puts("*");
			return 4;
		}
		else if (scannedKey == 0b01011101)
		{
			//Do something that indicates 5 has been pressed
			lcd_gotoxy(possition,1);
			lcd_puts("*");
			return 5;
		}
		else if (scannedKey == 0b00111101)
		{
			//Do something that indicates 6 has been pressed
			lcd_gotoxy(possition,1);
			lcd_puts("*");
			return 6;
		}
		else if (scannedKey == 0b01101011)
		{
			//Do something that indicates 7 has been pressed
			lcd_gotoxy(possition,1);
			lcd_puts("*");
			return 7;
		}
		else if (scannedKey == 0b01011011)
		{
			//Do something that indicates 8 has been pressed
			lcd_gotoxy(possition,1);
			lcd_puts("*");
			return 8;
		}
		else if (scannedKey == 0b00111011)
		{
			//Do something that indicates 9 has been pressed
			lcd_gotoxy(possition,1);
			lcd_puts("*");
			return 9;
		}
		else if (scannedKey == 0b01100111)
		{
			//Do something that indicates * has been pressed
			lcd_gotoxy(possition,1);
			lcd_puts("*");
			return 10;
		}
		else if (scannedKey == 0b01010111)
		{
			//Do something that indicates 0 has been pressed
			lcd_gotoxy(possition,1);
			lcd_puts("*");
			return 11;
		}
		else if (scannedKey == 0b00110111)
		{
			//Do something that indicates # has been pressed
			lcd_gotoxy(possition,1);
			lcd_puts("*");
			return 12;
		}
		else
		{
			// when none of the keys are pressed
			return 15;
		}
	}
	uint8_t ArrayComparison(uint8_t a[2][4], uint8_t b[])
	{
		 // Shows how many matching numbers there are
		int cor=0;
		/* Takes matrix lines one by one*/
		for(int j = 0; j < 2;j++)
		{
			/* Checks the line if it is matching the
			   entered massive*/
			for(int i = 0; i<4;i++)
			{
				if(a[j][i] == b[i])
				{
					/* if it is matching than returns 
					   1 as true*/
					cor++;
					if(cor == 4)
					return 1;
				}
			}
			cor=0;
		}
		// If not matching returns 0 as false
		return 0;
	}
	void setup()
	{
		// LED's
		GPIO_config_output(&DDRD,LED_RED);
		GPIO_config_output(&DDRD,LED_GREEN);
		
		// Lock
		GPIO_config_output(&DDRC,Lock);
		// Lock set low
		GPIO_write_low(&PORTC,Lock);
		
		// Buzzer
		GPIO_config_output(&DDRC,Buzzer);
		// Buzzer set low
		GPIO_write_low(&PORTC,Buzzer);
		
		// Columns
		DDRC |= (1<< COLUMN1) | (1<<COLUMN2) | (1<< COLUMN3);
	
		// Set all columns to high
		PORTC  |= (1<< COLUMN1) | (1<<COLUMN2) | (1<< COLUMN3);
	
		// Rows implicitly defined as inputs
		// Turn on internal pull ups for the rows
		DDRB = 0x00;
		PORTB |= (1<<ROW1) | (1 << ROW2) | (1 << ROW3) | (1 << ROW4);
	}