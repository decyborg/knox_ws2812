/*
 * ws2812b.c
 *
 *  Created on: Aug 5, 2015
 *      Author: B52932
 */
#include "ws2812b.h"
#include "derivative.h"
#include <hidef.h> /* for EnableInterrupts macro */

/**	Sends a 0 or a 1 depending on the received value
 * 	
 * 	@param bit Value to be sent 
 * */
void set_bit(unsigned char bit){
	if(bit){			/* Send a 1 */
		LED_STRIP_PIN = 1;	/* Set to 1  */
		asm(NOP);			/* Wait to assert a "1" */
		asm(NOP);
		asm(NOP);
		asm(NOP);
		asm(NOP);
		asm(NOP);
		asm(NOP);
		asm(NOP);
		asm(NOP);
		asm(NOP);
		asm(NOP);
		asm(NOP);
		asm(NOP);
		asm(NOP);
		asm(NOP);
		asm(NOP);
		LED_STRIP_PIN = 0;	/* Set to 0 */
	} else {			/* Send a 0 */
		DisableInterrupts;	/* Disable interrupts since this routine is extremely time dependent */
		LED_STRIP_PIN = 1;	/* Set to 1 */
		LED_STRIP_PIN = 0;	/* Set to 0 */
		EnableInterrupts;
	}
}

/** Sends the latch signal to the LEDs
 * 
 * Sends a latch signal (set LED_STRIP_PIN to zero) of approximately 10us
 * */
void latch(void){
	unsigned char delay;
	PTS_PTS2 = 0;						/* Set to 0 */
	for(delay = 0; delay < 10; ++delay)	/* Wait for approximately 10us to issue a "reset" */
		asm(NOP);
}

/** Sends a frame of 8 bits through the LED_STRIP_PIN
 * 
 * 	@param color Frame of 8 bits to send
 * */
void send_color(unsigned char color){
	unsigned char i;
	for(i = 0; i < 8; ++i){			/* Go through 8 bits */
		set_bit(color & 0x80);		/* Send MSB */	
		color = color << 1;			/* Shift adjacent bit to the MSB position */
	}
}

/** Sends a 24 bit frame with the desired values of the LED
 * 
 * 	@param red   Desired 8 bit value for the red LED
 * 	@param green Desired 8 bit value for the green LED
 * 	@param blue  Desired 8 bit value for the blue LED
 * */
void set_LED(unsigned char red, unsigned char green, unsigned char blue){
	send_color(green);				/* Send colors in the WS2812B format GRB */
	send_color(red);
	send_color(blue);
}

/**	Sets the complete LED strip to the desired RGB color
 * 
 * 	@param red   Desired 8 bit value for the red LED
 * 	@param green Desired 8 bit value for the green LED
 * 	@param blue  Desired 8 bit value for the blue LED
 * */
void set_LEDSTRIP(unsigned char red, unsigned char green, unsigned char blue){
	unsigned int LED_number;
	for(LED_number = 0; LED_number < TOTAL_LED_NUMBER; ++LED_number){	/* Update every LED on the strip */
		send_color(green);				/* Send colors in the WS2812B format GRB */
		send_color(red);
		send_color(blue);
	}
	latch();	/* Reset LED values */
}
