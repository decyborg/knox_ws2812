#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "cpmu.h"
#include "ws2812b.h"

unsigned char red, blue, green, state;

void main(void) {
	
	
  EnableInterrupts;
  /* include your code here */
  DDRS_DDRS2 = 1;
  
  red = 0;
  blue = 0;
  green = 0;
  state = 0;
  clock_init(32000000); 
  for(;;) {
	  int i;
	  switch(state){
		  case 0: red++; 	if(red==255){state++;} 	break;
		  case 1: green++; 	if(green==255){state++;}break;
		  case 2: blue++; 	if(blue==255){state++;} break;
		  case 3: red--; 	if(red==0){state++;} 	break;
		  case 4: green--; 	if(green==0){state++;} 	break;
		  case 5: blue--; 	if(blue==0){state++;} 	break;
		  case 6: state = 0; 						break;
	  }
	  for(i = 0; i < LED_NUMBER; ++i)
		  set_LED(red, green, blue);
	  latch();
  } /* loop forever */
  /* please make sure that you never leave main */

}
