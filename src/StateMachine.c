#include <msp430.h>
#include "StateMachine.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"


static char dim_state = 0;

void drawSquare(int offc, int offr){
  for(int r = 0; r < 20; r++){
    for (int c = 0; c < 20; c++){
      drawPixel(c + offc, r + offr, COLOR_BLUE);
}
  }
}




void state_advance(){
  switch(state){
  case 0:
     break;
  case 1:
    // redLight();
    //    buzzer_set_period(1000);
    red_on = 1;
    green_on = 0;
    kimPossible();
    drawSquare(70,70);
    break;
  case 2:
    // greenLight();
    red_on = 0;
    green_on = 1;
    soundTwo();
    break;
  case 3:
    //    bothLights();
    red_on = 1;
    green_on = 1;
    soundThree();
    state = 0;
    break;
  case 4:
    //  dim();
    soundFour();
    state = 0;
    break;
  }
  led_changed = 1;
  led_update();
}

//void dim(){
//static int dim_counter = 0;
// switch(dim_counter){
//case 0:
// dim25();
// dim_counter = 1;
// break;
//case 1:
// dim50();
//  dim_counter = 2;
//  break;
//case 2:
// dim75();
// dim_counter = 0;
// break;
// }
// return 1;
//}

void dim25(){
  switch(dim_state){
  case 0: red_on = 1; break;
  case 1:
  case 2:
  case 3: red_on = 0; break;
  default: dim_state = 0;
  }
  led_changed = 1;
  led_update();
}

void dim50(){
  switch(dim_state){
  case 0:
  case 1: red_on = 1; break;
  case 2:
  case 3: red_on = 0; break;
  default: dim_state = 0;
  }
  led_changed = 1;
  led_update();
}

void dim75(){
  switch(dim_state){
  case 0: red_on = 0; break;
  case 1:
  case 2:
  case 3: red_on = 1; break;
  default: dim_state = 0;
  }
  led_changed = 1;
  led_update();
}
