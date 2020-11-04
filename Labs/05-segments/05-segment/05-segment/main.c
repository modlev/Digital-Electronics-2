/*
 * 05-segment.c
 *
 * Created: 2020-10-21 09:22:30
 * Author : Modestas
 */ 

/* Includes ----------------------------------------------------------*/

#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "segment.h"        // Seven-segment display library for AVR-GCC
#define F_CPU 16000000
#include <util/delay.h>

/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Display decimal 
 * counter values on SSD (Seven-segment display) when 16-bit 
 * Timer/Counter1 overflows.
 */
int main(void)
{
    // Configure SSD signals
    SEG_init();

    // Test of SSD: display number '3' at position 0
	
    SEG_update_shift_regs(3, 0);
	SEG_clear(); // This function turns off the LEDs
	_delay_ms(1000);
	
    /* Configure 16-bit Timer/Counter1
     * Set prescaler and enable overflow interrupt */
	
	TIM1_overflow_4ms();
	TIM1_overflow_interrupt_enable();
	
    // Enables interrupts by setting the global interrupt mask
	sei();
	
    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**
 * ISR starts when Timer/Counter1 overflows. Increment decimal counter
 * value and display it on SSD.
 */
ISR(TIMER1_OVF_vect)
{
    // WRITE YOUR CODE HERE
	int poss = 0; // variable to know the possition
	
	//loop for counting to 60 digit
	for(int i = 0; i < 60; i++)
	{
		//sets the first digit number
		SEG_update_shift_regs(i%10, poss); 
		_delay_ms(50);
		//sets the seconnd digit number
		SEG_update_shift_regs(i/10, poss+1);
		_delay_ms(50);
	}
	
	// Snake program
	/*
	for(int i =0;; i++)
	{
		if(i%6==0)
		{
			SEG_update_shift_regs(0,poss);
			_delay_ms(200);
		}
		else 
		{
			SEG_update_shift_regs(i%6,poss);
			_delay_ms(200);
		}
	}
	
	// Snake trough all 4 digits
	SEG_update_shift_regs(0,0);
	_delay_ms(200);
	SEG_update_shift_regs(1,0);
	_delay_ms(200);
	SEG_update_shift_regs(2,0);
	_delay_ms(200);
	SEG_update_shift_regs(3,0);
	_delay_ms(200);
	SEG_update_shift_regs(3,1);
	_delay_ms(200);
	SEG_update_shift_regs(3,2);
	_delay_ms(200);
	SEG_update_shift_regs(3,3);
	_delay_ms(200);
	SEG_update_shift_regs(4,3);
	_delay_ms(200);
	SEG_update_shift_regs(5,3);
	_delay_ms(200);
	SEG_update_shift_regs(0,3);
	_delay_ms(200);
	SEG_update_shift_regs(0,2);
	_delay_ms(200);
	SEG_update_shift_regs(0,1);
	_delay_ms(200);
	*/
}
