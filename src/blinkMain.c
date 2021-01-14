//Alternate LEDs from Off, Green, and red
#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "StateMachine.h"
#include "buzzer.h"
#include "switches.h"


short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;
long color;
static int prev = 0;

u_char c_width = (screenWidth/2) + 1;
u_char c_height = (screenHeight/2) + 1;

void drawDiamond(u_char col, u_char row, u_char center, u_int color){
  u_char r;
  u_char c;

  for(c = 0; c < center; c++){
    for(r = center; r < center * 2 - c; r++){
      drawPixel(center + col + c, row + r, color);
      drawPixel(center + col - c, row + r, color);
    }
  }

  for(r = 0; r < center; r++){
    for(c = 0; c < r; c++){
      drawPixel(center + col + c, row + r, color);
      drawPixel(center + col - c, row + r, color);
  }
  }
}

void wdt_c_handler(){
  static int count = 0;
  static int count2 = 0;
  static int count3 = 0;
  /*
  if(switch_state == 1){
    if(++count %5 == 0)
      buzzer_advance();
    if(count == 250)
	state_advance();
	count = 0;
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
      fontFgColor = (fontFgColor == COLOR_GREEN ? COLOR_PINK : COLOR_GREEN);
      redrawScreen = 1;
      }
    }
  */
  count++;
  if(count == 250 & switch_state == 0){
    count = 0;
  }else if(count != 250 && switch_state == 1){
    count = 0;
  }else if(count != 250 && switch_state == 2){
    count = 0;
  }else if(count != 250 && switch_state == 3){
    count = 0;
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

void main(){
  //  led_init();
  P1DIR |= LED_GREEN;
  P1OUT |= LED_GREEN;
  configureClocks();/*setuup master oscillator, CPU & peripheeral clocks*/
  lcd_init();
  switch_init();
  buzzer_init();
  enableWDTInterrupts();
  or_sr(0x8);

  clearScreen(COLOR_BLACK);

  drawString5x7(15,30,"Wanna Play a Game?",COLOR_RED, COLOR_BLACK);

  while(1){
    state_advance();
  }


  /*
  while(1){
    if(redrawScreen){
      switch(switch_state){
      case 0:
	// redrawScreen = 0;
	drawString5x7(15,30,"Wanna Play a Game?",COLOR_RED, COLOR_BLACK);
	//	drawShapes(COLOR_PINK, 100, 100, 10);
	break;
      case 1:
	if(prev == 2){
	  clearShapes(25, 30, 20);
	}else if(prev == 3){
	  clearShapes(50, 50, 10);
	}
	drawShapes(COLOR_PINK, 100, 100, 10);
	prev = 1;
	break;
      case 2:
	if(prev == 1){
	  clearShapes(100,100,10);
	}else if(prev == 3){
	  clearShapes(50,50,10);
	}
	drawShapes(COLOR_YELLOW, 25, 30, 20);
	prev = 2;
	break;
      case 3:
	if(prev == 1){
	  clearShapes(100,100,10);
	}else if(prev == 2){
	  clearShapes(25,30,20);
	}
	drawShapes(COLOR_BLUE, 50, 50, 10);
	prev = 3;
	break;
      case 4:
	if(prev == 1){
	  clearShapes(100,100,10);
	}else if(prev == 2){
	  clearShapes(25, 30, 20);
	}else if(prev == 3){
	  clearShapes(50,50,10);
	}
      }
    }
      // switch(s){
	// case 1:
	//state_advance();
	//break;
	//      case 2:
	*/	

    P1OUT &=~LED_GREEN;
    or_sr(0x10);
    P1OUT |= LED_GREEN;
    
 
}

 
