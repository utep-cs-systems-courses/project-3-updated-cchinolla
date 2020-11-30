#include <msp430.h>
#include "stateMachine.h"

void __interrupt_vec(WDT_VECTOR) WDT(){//250 interrupts/sec

  static char counter=0;
  switch(state){
  case 1:
    if(++counter == 50){
      state_advance();
      counter = 0;
    }
  case 2:
    if(++counter == 125){
      state_advance();
      counter = 0;
    }
  case 3:
    state_advance();
    counter = 0;
  case 4:
    if(++counter < 62){
      dim25();
    }else if(++counter < 125){
      dim50();
    }else{
      if(++counter == 250){
	counter = 0;
      }else{
	dim75();
      }
  
  }
