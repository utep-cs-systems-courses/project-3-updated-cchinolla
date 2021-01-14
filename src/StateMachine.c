#include <msp430.h>
#include "StateMachine.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include <libTimer.h>

char toggle = 0;
char times = 0;

char buttonState = 0;
short int state = 0;
short freq = 500;



void drawShapes(int COLOR, int width, int height, int center){
  u_char c_width = screenWidth/2 +1;
  u_char c_height = screenHeight/2 + 1;

  drawDiamond(c_width - width, c_height - height, center, COLOR);
  drawDiamond(c_width, c_height, center, COLOR);
}

void clearShapes(int width, int height, int center){
  u_char c_width = screenWidth/2 + 1;
  u_char c_height = screenHeight/2 +1;

  drawDiamond(c_width - width, c_height - height, center, COLOR_BLACK);
  drawDiamond(c_width, c_height, center, COLOR_BLACK);
}

/*
void toggle_green_led(){
  if(times < 70){
    times++;
    toggle = toggle_green(toggle);
    led_update;
  }else{
    times = 0;
  }
}
*/

char toggle_green(){
  char changed = 0;
  if(red_on){
    green_on ^= 1;
    changed = 1;
  }
  return changed;
}



char toggle_red(){
  static char state = 0;
  switch(state){
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
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
    sec_count = 4;
    break;
  default:
    sec_count = 0;
  }
}


/*
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
    buzzer_set_period(1000);
    //    state = 0;
    break;
  case 1:
    green_on = 0;
    state = 0;
    buzzer_set_period(0);
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
    buzzer_set_period(2000);
  case G:
    changed = toggle_green();
    color = R;
    buzzer_set_period(1000);
  }
  changed_led = changed;
  led_update();
}

char state4(){
  red_on = 0;
  buzzer_set_period(0);
  changed_led = 1;
  led_update();
  return 1;
}




void state_advance(){
  
  char changed = 0;
  switch(switch_state){
  case 1:
    state1();
    // state1();
    break;
  case 2:
    changed = toggle_green();
    break;
  case 3:
    changed = toggle_green();
    break;
  case 4:
    changed = toggle_green();
    break;
  }
  changed_led = changed;
  led_update();
}
*/

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

void state_advance(){
  switch(switch_state){
  case 1:
    //  toggle_red();
    buzzer_set_period(1000);
    clearScreen(COLOR_BLACK);
    //    clearShapes(50,50,10);
    drawShapes(COLOR_PINK, 100, 100, 10);
    break;
  case 2:
    // toggle_green();
    buzzer_set_period(500);
    clearShapes(100,100,10);
    drawShapes(COLOR_YELLOW, 25, 30, 20);
    break;
  case 3:
    toggle_green();
    buzzer_set_period(5000);
    break;
  case 4:
    //    toggle_green_led();
    buzzer_set_period(0);
    clearScreen(COLOR_BLACK);
    break;
  }
}

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
