#include <msp430.h>
#include "StateMachine.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include <libTimer.h>

static char dim_state = 0;

void drawSquare(int offc, int offr){
  for(int r = 0; r < 20; r++){
    for (int c = 0; c < 20; c++){
      drawPixel(c + offc, r + offr, COLOR_BLUE);
}
  }
}

char toggle_green(){
  static char s = 0;
  switch(s){
  case 0:
    red_on = 1;
    s = 1;
    break;
  case 1:
    red_on = 0;
    s = 0;
    break;
  }
  return 1;
}

char toggle_red(){
  static char s = 0;
  switch(s){
  case 0:
    green_on = 1;
    s = 1;
    break;
  case 1:
    green_on = 0;
    s = 0;
    break;
  }
  return 1;
}

void buzzer_advance(){
  static char sec_count = 0;
  switch(sec_count){
  case 0:
    buzzer_set_period(1000);
    sec_count = 1;
    break;
  case 1:
    buzzer_set_period(5000);
    sec_count = 2;
    break;
  case 2:
    buzzer_set_period(3000);
    sec_count = 3;
    break;
  case 3:
    buzzer_set_period(7000);
    sec_count = 0;
    break;
  }
}


void state_advance(){
  char changed = 0;
  switch(state){
  case 0:
    changed = toggle_green();
    break;
  case 1:
    changed = toggle_red();
    break;
  case 2:
    changed = dim();
    break;
  }
  led_changed = changed;
  led_update();
}

void dim(){
static int dim_counter = 0;
switch(dim_counter){
case 0:
  red_on = 0;
  led_changed = 1;
  led_update();
  dim_counter = 1;
  break;
case 1:
  dim25();
  dim_counter = 2;
  break;
case 2:
  dim50();
  dim_counter = 3;
  break;
case 3:
  dim75();
  dim_counter = 0;
  break;
}
  return 1;
}

void dim25(){
  static char dimState = 0;
  switch(dimState){
  case 0:
    red_on = 1;
    dimState = 1;
    break;
  case 1:
    red_on = 0;
    dimState = 2;
    break;
  case 2:
    red_on = 1;
    dimState = 3;
    break;
  case 3:
    red_on = 0;
    dimState = 0;
    break;
  }
  led_changed = 1;
  led_update();
}

void dim50(){
  static char dimState = 0;
  switch(dimState){
  case 0:
    red_on = 1;
    dimState = 1;
    break;
  case 1:
    red_on = 0;
    dimState = 2;
    break;
  case 2:
    red_on = 1;
    dimState = 3;
    break;
  case 3:
    red_on = 1;
    dimState = 0;
  }
  led_changed = 1;
  led_update();
}

void dim75(){
  static char dimState = 0;
  switch(dimState){
  case 0:
    red_on = 1;
    dimState = 1;
    break;
  case 1:
    red_on = 1;
    dimState = 2;
    break;
  case 2:
    red_on = 1;
    dimState = 3;
    break;
  case 3:
    red_on = 0;
    dimState = 0;
    break;
  }
  led_changed = 1;
  led_update();
}
