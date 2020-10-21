/*
 * 04-interupts.c
 *
 * Created: 2020-10-14 09:27:24
 * Author : Modestas
 */ 
/* Defines -----------------------------------------------------------*/
#define LED_D1  PB5
#define LED_D2  PB4
#define LED_D3  PB3

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "gpio.h"           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC

/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Toggle three LEDs
 * on Multi-function shield with internal 8- and 16-bit timer modules.
 */
int main(void)
{
    /* Configuration of three LEDs */
	GPIO_config_output(&DDRB, LED_D1);
    GPIO_write_low(&PORTB, LED_D1);
    GPIO_config_output(&DDRB, LED_D2);
    GPIO_write_low(&PORTB, LED_D2);
	GPIO_config_output(&DDRB, LED_D3);
	GPIO_write_low(&PORTB, LED_D3);
    /* Configuration of 8-bit Timer/Counter0 */
    // WRITE YOUR CODE HERE
	TIM0_overflow_1s();
	TIM0_overflow_interrupt_enable();
    /* Configuration of 16-bit Timer/Counter1
     * Set prescaler and enable overflow interrupt */
    TIM1_overflow_1s();
    TIM1_overflow_interrupt_enable();
    /* Configuration of 8-bit Timer/Counter2 */
    // WRITE YOUR CODE HERE
	TIM2_overflow_1s();
	TIM2_overflow_interrupt_enable();
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
 * ISR starts when Timer/Counter1 overflows. Toggle LED D2 on 
 * Multi-function shield. */
ISR(TIMER0_OVF_vect)
{
    // WRITE YOUR CODE HERE
	GPIO_toggle(&PORTB, LED_D1);
}

ISR(TIMER1_OVF_vect)
{
	// WRITE YOUR CODE HERE
	GPIO_toggle(&PORTB, LED_D2);
}

ISR(TIMER2_OVF_vect)
{
	// WRITE YOUR CODE HERE
	GPIO_toggle(&PORTB, LED_D3);
}