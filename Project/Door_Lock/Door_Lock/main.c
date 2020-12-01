/*
 * Door_Lock.c
 *
 * Created: 2020-11-30 17:24:45
 * Author : Modestas
 */ 

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#define F_CPU 16000000
#include <util/delay.h> // Functions for busy-wait delay loops 
#include <avr/io.h> // AVR device-specific IO definitions
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function

#define COLUMN1 PORTC4
#define COLUMN2 PORTC5
#define COLUMN3 PORTC6
#define ROW1 PINB0
#define ROW2 PINB1
#define ROW3 PINB2
#define ROW4 PINB3

#define LED_RED  PD1
#define LED_GREEN  PD0
#include <stdint.h>
/* Function definitions ----------------------------------------------*/
uint8_t scanKeyboard();
int determineKey(uint8_t scannedKey);
int ArrayComparison(int a[2][4], int b[], int size)
{
	int cor=0;
	for(int j = 0; j < 2;j++)
	{
		for(int i = 0; i<4;i++)
		{
			if(a[j][i] == b[i])
			{
				cor++;
				if(cor == 4)
				return 1;
			}
		}
		cor=0;
	}

	return 0;
}
void setup(){
	//LED's
	DDRD = DDRD | (1<<LED_RED);
	DDRD = DDRD | (1<<LED_GREEN);
	
	PORTD = PORTD & ~(1<<LED_RED);
	PORTD = PORTD & ~(1<<LED_GREEN);
	
	//Columns
	DDRC |= (1<< COLUMN1) | (1<<COLUMN2) | (1<< COLUMN3);
	
	//Set all columns to high 0b10101000
	PORTC  |= (1<< COLUMN1) | (1<<COLUMN2) | (1<< COLUMN3);
	
	//Rows implicitly defined as inputs
	//Turn on internal pull ups for the rows
	DDRB = 0x00;
	PORTB |= (1<<ROW1) | (1 << ROW2) | (1 << ROW3) | (1 << ROW4);
}
int main(void)
{
	// Initialize LCD display
	lcd_init(LCD_DISP_ON);

	// Set pointer to beginning of CGRAM memory
	lcd_command(1 << LCD_CGRAM);
	
	// Set DDRAM address
	lcd_command(1 << LCD_DDRAM);
	
	// Display first custom character
	lcd_gotoxy(0,0);
	lcd_puts("Enter password:");
	
	 setup();
    // Configure 8-bit Timer/Counter2 for Stopwatch
    // Set prescaler and enable overflow interrupt every 16 ms
	/*TIM2_overflow_16ms();
	TIM2_overflow_interrupt_enable();
	TIM0_overflow_4ms();
	TIM0_overflow_interrupt_enable();
    // Enables interrupts by setting the global interrupt mask
    sei();
	*/
    // Infinite loop
	int key;
	static int quantity = 0;
	int correct_num[2][4] ={{1, 2, 3, 4}, {5, 6, 7, 8}};
	int entered_num[4];
    while(1)
    {
		 key = determineKey(scanKeyboard());
		  _delay_ms(100);
		  entered_num[quantity]=key;
		 if(key != 15)
		 {
			 quantity++;
			 if(quantity==4)
			 {
				 quantity = 0;
				 lcd_gotoxy(0,1);
				 if(ArrayComparison(correct_num,entered_num,(sizeof(correct_num))/4))
				 {
					  lcd_puts("Correct code");
					  PORTD= PORTD^(1<<LED_GREEN);
					  _delay_ms(1000);
					  lcd_gotoxy(0,1);
					  lcd_puts("                                      ");
					  PORTD= PORTD^(1<<LED_GREEN);
				 }
				 else
				 {
					 lcd_puts("Inccorect code, try again in 10 seconds");
					 PORTD= PORTD^(1<<LED_RED);
					 _delay_ms(1000);
					 lcd_gotoxy(0,1);
					 lcd_puts("                                      ");
					 PORTD= PORTD^(1<<LED_RED);
				 }
				 
				 
			 }
		 }
	}
}

uint8_t scanKeyboard()
{
	
	
	PORTC  |= (1<< COLUMN1) | (1<<COLUMN2) | (1<< COLUMN3);

	
	//variable that will store the state of the row pins
	uint8_t rowState = PORTB;
	uint8_t masker = 0b00001111;
	for(int i = 4; i < 7; i++)
	{
		PORTC &= ~(1 << i);
		
		//Read all rows simultaneously and record the data to be used in if statements later for indicating the specific key pressed
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
	
int determineKey(uint8_t scannedKey)
{
		static int possition = 0;
		if (scannedKey == 0b01101110)
		{
			//Do something that indicates 1 has been pressed
			lcd_gotoxy(possition,1);
			lcd_puts("*");
			possition++;
			if(possition==4)
			possition = 0;
			return 1;
		} 
		else if (scannedKey == 0b01011110)
		{
			//Do something that indicates 2 has been pressed
			lcd_gotoxy(possition,1);
			lcd_puts("*");
			possition++;
			if(possition==4)
			possition = 0;
			return 2;
		} 
		else if (scannedKey == 0b00111110)
		{
			//Do something that indicates 3 has been pressed
			lcd_gotoxy(possition,1);
			lcd_puts("*");
			possition++;
			if(possition==4)
			possition = 0;
			return 3;
		} 
		else if (scannedKey == 0b01101101)
		{
			//Do something that indicates 4 has been pressed
			lcd_gotoxy(possition,1);
			lcd_puts("*");
			possition++;
			if(possition==4)
			possition = 0;
			return 4;
		} 
		else if (scannedKey == 0b01011101)
		{
			//Do something that indicates 5 has been pressed
			lcd_gotoxy(possition,1);
			lcd_puts("*");
			possition++;
			if(possition==4)
			possition = 0;
			return 5;
		} 
		else if (scannedKey == 0b00111101)
		{
			//Do something that indicates 6 has been pressed
			lcd_gotoxy(possition,1);
			lcd_puts("*");
			possition++;
			if(possition==4)
			possition = 0;
			return 6;
		} 
		else if (scannedKey == 0b01101011)
		{
			//Do something that indicates 7 has been pressed
			lcd_gotoxy(possition,1);
			lcd_puts("*");
			possition++;
			if(possition==4)
			possition = 0;
			return 7;
		} 
		else if (scannedKey == 0b01011011)
		{
			//Do something that indicates 8 has been pressed
			lcd_gotoxy(possition,1);
			lcd_puts("*");
			possition++;
			if(possition==4)
			possition = 0;
			return 8;
		} 
		else if (scannedKey == 0b00111011)
		{
			//Do something that indicates 9 has been pressed
			lcd_gotoxy(possition,1);
			lcd_puts("*");
			possition++;
			if(possition==4)
			possition = 0;
			return 9;
		} 
		else if (scannedKey == 0b01100111)
		{
			//Do something that indicates * has been pressed
			lcd_gotoxy(possition,1);
			lcd_puts("*");
			possition++;
			if(possition==4)
			possition = 0;
			return 10;
		} 
		else if (scannedKey == 0b01010111)
		{
			//Do something that indicates 0 has been pressed
			lcd_gotoxy(possition,1);
			lcd_puts("*");
			possition++;
			if(possition==4)
			possition = 0;
			return 11;
		} 
		else if (scannedKey == 0b00110111)
		{
			//Do something that indicates # has been pressed
			lcd_gotoxy(possition,1);
			lcd_puts("*");
			possition++;
			if(possition==4)
			possition = 0;
			return 12;
		} 
		else 
		{
			return 15;
		}
}
