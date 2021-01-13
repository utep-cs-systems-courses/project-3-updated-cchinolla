#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"
#include "StateMachine.h"
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"


char state;
char SW1down;
char SW2down;
char SW3down;
char SW4down;
char switch_state;
char switch_state_changed;
char button = 0;



static char switch_update_interrupt_sense(){
  char p2val = P2IN;
  //update switch interrupt to detect changes from current buttons
  P2IES |= (p2val & SWITCHES);//if switch is up then sense down
  P2IES &= (p2val | ~SWITCHES);//if switch is down then sense up
  return p2val;
}
void switch_init(){
  P2REN |= SWITCHES;//enables resistors for switches
  P2IE |= SWITCHES;//enables interrupts from switches
  P2OUT |= SWITCHES;//pull-ups for switches
  P2DIR &= ~SWITCHES;//set switches bits for inpput
  switch_update_interrupt_sense();
  switch_interrupt_handler();
  led_update();
}


void switch_interrupt_handler(){
  char p2val = switch_update_interrupt_sense();

  char s1 = (p2val & SW1) ? 0:1;
  char s2 = (p2val & SW2) ? 0:1;
  char s3 = (p2val & SW3) ? 0:1;
  char s4 = (p2val & SW4) ? 0:1;
  
  if(s1){
    button = 1;
  }
}
