/*
 * ws2812b.c
 *
 *  Created on: Aug 5, 2015
 *      Author: B52932
 */
#include "ws2812b.h"
#include "derivative.h"
#include <hidef.h> /* for EnableInterrupts macro */


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

void latch(void){
	unsigned char delay;
	PTS_PTS2 = 0;						/* Set to 0 */
	for(delay = 0; delay < 10; ++delay)	/* Wait for approximately 10us to issue a "reset" */
		asm(NOP);
}

void send_color(unsigned char color){
	unsigned char i;
	for(i = 0; i < 8; ++i){			/* Go through 8 bits */
		set_bit(color & 0x80);		/* Send MSB */	
		color = color << 1;			/* Shift adjacent bit to the MSB position */
	}
}

void set_LED(unsigned char red, unsigned char green, unsigned char blue){
	send_color(green);				/* Send colors in the WS2812B format GRB */
	send_color(red);
	send_color(blue);
}
