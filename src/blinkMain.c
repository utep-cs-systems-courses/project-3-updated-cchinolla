//Alternate LEDs from Off, Green, and red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "StateMachine.h"



short redrawScreen = 1;
u_int fontFgColor = COLOR_BLUE;
long COLOR1;
long COLOR2;

static int prev = 0;

//void drawCircle(intxc, int yc, int x, int y){
  // putpixel (xc+x, yc+y, RED)

u_char centerWidth = (screenWidth/2) + 1;
u_char centerHeight = (screenHeight/2) + 1;


void main(void){
  configureClocks();/*setuup master oscillator, CPU & peripheeral clocks*/
  led_init();
  switch_init();
  buzzer_init();
  enableWDTInterrupts();
  or_sr(0x18);

  clearScreen(COLOR_PURPLE);

  while(1){
    if(redrawScreen == 1){
      drawString5x7(10,60,"Wanna Play a Game??",COLOR_RED, COLOR_BLACK);
    }
    P1OUT |= LED_GREEN;
    or_sr(0x10);
    P1OUT |= LED_GREEN;
  }
}

 
