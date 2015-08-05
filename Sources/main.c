#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "cpmu.h"
#include "ws2812b.h"

unsigned char red, blue, green, state;

void main(void) {
	
  EnableInterrupts;
  /* include your code here */
  DDRS_DDRS2 = 1;

  clock_init(32000000); 
  for(;;) {
	  set_LEDSTRIP(red, green, blue);
  } /* loop forever */
  /* please make sure that you never leave main */

}
