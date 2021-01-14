//Alternate LEDs from Off, Green, and red
#include <msp430.h>
#include <libTimer.h>
#include "led.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "StateMachine.h"


//#define LED_GREEN BIT6
short redrawScreen = 1;
u_int fontFgColor = COLOR_BLUE;
long COLOR1;
long COLOR2;

static int prev = 0;

//void drawCircle(intxc, int yc, int x, int y){
  // putpixel (xc+x, yc+y, RED)

u_char centerWidth = (screenWidth/2) + 1;
u_char centerHeight = (screenHeight/2) + 1;

void wdt_c_handler(){
  static int count = 0;
  static int count2 = 0;
  static int count3 = 0;

  if(switch_state == 1){
    if(++count % 5 == 0){
      buzzer_advance();
      if(count == 250){
	state_advance();
	count = 0;
	}
      }
    }
  if(++count2 == 250){
    state_advance();
    count2 = 0;
    count2++;
    redrawScreen = 1;
   }
 if(switch_state == 4){
   buzzer_advance();
    if(++count3 == 250){
      count3 == 0;
      fontFgColor = (fontFgColor == COLOR_YELLOW ? COLOR_BROWN : COLOR_GREEN);
      redrawScreen = 1;
      }
    }
  }


/*extern char s;
static char button = 0;

void wdt_c_handler(){
  static int count = 0;
  // u_init state = p2sw_read();

  count++;

  if((state & 1) == 0){
    button = 1;
  }
  if((state & 2) == 0){
    button = 2;
  }

  if((state & 4) == 0){
    button = 3;
  }
  if((state & 8) == 0){
    button = 4;
  }


  switch(button){
  case 1:
    redrawScreen = 1;
    break;
  case 2:
    if(count == 250){
      redrawScreen = 1;
    }
    break;
  case 3:
    if(count == 250){
      redrawScreen = 1;
      count = 0;
    }
    break;
  case 4:
    if(count == 250){
      redrawScreen = 1;
      count = 0;
    }
    break;
  }

  if(count == 250){
    count = 0;
  }
}
   
*/

void main(void){
  P1DIR |= LED_GREEN;
  P1OUT |= LED_GREEN;
  configureClocks();/*setuup master oscillator, CPU & peripheeral clocks*/
  lcd_init();
  led_init();
  switch_init();
  buzzer_init();
  enableWDTInterrupts();
  or_sr(0x18);

  clearScreen(COLOR_PURPLE);

  while(1){
    if(redrawScreen){
      switch(switch_state){
      case 0:
	// redrawScreen = 0;
	drawString5x7(10,20,"Wanna Play a Game??",COLOR_BLACK, COLOR_BLUE);
	break;
      case 1:
	if(prev == 2){
	  clearShapes(25, 30, 20);
	}else if(prev == 3){
	  clearShapes(50, 50, 10);
	}
      // switch(s){
	// case 1:
	//state_advance();
	//break;
	//      case 2:
	
    }
    }
    P1OUT &=~LED_GREEN;
    or_sr(0x10);
    P1OUT |= LED_GREEN;
    }
 
}

 
