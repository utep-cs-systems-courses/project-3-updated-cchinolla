//Alternate LEDs from Off, Green, and red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"

int main(void){
  configureClocks();/*setuup master oscillator, CPU & peripheeral clocks*/
  led_init();
  switch_init();
  buzzer_init();
  enableWDTInterrupts();
  or_sr(0x18);
}
