/*
 * ws2812b.h
 *
 *  Created on: Aug 5, 2015
 *      Author: B52932
 */

#ifndef WS2812B_H_
#define WS2812B_H_

#define LED_STRIP_PIN PTS_PTS2	/* Pin used to send the signal to the LEDs */
#define TOTAL_LED_NUMBER	30			/* Number of LEDs on the strip */

/**	Sends a 0 or a 1 depending on the received value
 * 	
 * 	@param bit Value to be sent 
 * */
void set_bit(unsigned char bit);
/** Sends the latch signal to the LEDs
 * 
 * Sends a latch signal (set LED_STRIP_PIN to zero) of approximately 10us
 * */
void latch(void);
/** Sends a frame of 8 bits through the LED_STRIP_PIN
 * 
 * 	@param color Frame of 8 bits to send
 * */
void send_color(unsigned char color);
/** Sends a 24 bit frame with the desired values of the LED
 * 
 * 	@param red   Desired 8 bit value for the red LED
 * 	@param green Desired 8 bit value for the green LED
 * 	@param blue  Desired 8 bit value for the blue LED
 * */
void set_LED(unsigned char red, unsigned char green, unsigned char blue);

/**	Sets the complete LED strip to the desired RGB color
 * 
 * 	@param red   Desired 8 bit value for the red LED
 * 	@param green Desired 8 bit value for the green LED
 * 	@param blue  Desired 8 bit value for the blue LED
 * */
void set_LEDSTRIP(unsigned char red, unsigned char green, unsigned char blue);

#endif /* WS2812B_H_ */
