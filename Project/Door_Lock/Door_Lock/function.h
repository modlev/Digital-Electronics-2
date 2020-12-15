/*
 * function.h
 *
 * Created: 2020-12-11 16:19:26
 *  Author: Modestas
 */ 


#ifndef FUNCTION_H_
#define FUNCTION_H_
// function to scan the keyboard for the pressed key
uint8_t scanKeyboard();
/* Using the scanKeyboard function, this function 
   determine the pressed key */
uint8_t determineKey(uint8_t scannedKey, uint8_t possition);
/* Function meant for comparing the matrix array of 
   correct passwords and the inserted password to
   the keypad*/
uint8_t ArrayComparison(uint8_t a[2][4], uint8_t b[]);
// Setting all the I/O ports
void setup();
// Function for the red LED blink
void RedBlink();
// Function for the green LED blink
void GreenBlink();
// Function to unlock the doors
void Unlock();
// Function for the buzzer to make sound
void Buzzer_sound();

#endif /* FUNCTION_H_ */