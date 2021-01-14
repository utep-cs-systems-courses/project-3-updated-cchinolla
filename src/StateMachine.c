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

void drawShapes(int COLOR, int width, int height, int center){
  u_char c_width = screenWidth/2 +1;
  u_char c_height = screenHeight/2 + 1;

  drawDiamond(c_width - width, c_height - height, center, COLOR);
  drawDiamond(c_width, c_height, center, COLOR_BLACK);
}

void clearShapes(int width, int height, int center){
  u_char c_width = screenWidth/2 + 1;
  u_char c_height = screenHeight/2 +1;

  drawDiamond(c_width - width, c_height - height, center, COLOR_BLACK);
  drawDiamond(c_width, c_height, center, COLOR_BLACK);
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

char state1(){
  static short curr = 0;
  switch(curr){
  case 0:
    red_on = 1;
    state = 0;
    curr = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    curr = 0;
    break;
  }
  return 1;
}

char state2(){
  static char state = 0;
  switch(state){
  case 0:
    green_on = 1;
    state = 0;
    break;
  case 1:
    green_on = 0;
    state = 0;
    break;
  }
  return 1;
}

char state3(){
  char changed = 0;
  static enum {R=0, G=1} color = G;
  switch(color){
  case R:
    changed= toggle_red();
    color = G;
  case G:
    changed = toggle_green();
    color = R;
  }
  changed_led = changed;
  led_update();
}

char state4(){
  red_on = 0;
  changed_led = 1;
  led_update();
  return 1;
}
    
void state_advance(){
  
  char state = 0;
  switch(state){
  case 0:
    state1();
    break;
  case 1:
    state2();
    break;
  case 2:
    state3();
    break;
  case 3:
    state4();
    break;
  }
  //changed_led = changed;
  led_update();
}


/*
void state_advance(){
  char changed = 0;
  static enum{R = 0, G = 1} color = G;
  switch(color){
  case R:
    changed = toggle_red();
    color = G;
    break;
  case G:
    changed = toggle_green();
    color = R;
    break;
  }
  leds_changed = changed;
  led_update();
}
*/

/*
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
*/
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
  changed_led = 1;
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
  changed_led = 1;
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
  changed_led = 1;
  led_update();
}

short get_period(short freq){
  return 2000000/freq;
}
