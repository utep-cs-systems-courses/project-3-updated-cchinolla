#include <msp430.h>
#include "switches.h"


void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if(P2IFG & SWITCHES){//if a button cause this interrupt
    P2IFG &= ~SWITCHES;//clear pending switch interrupts
    switch_interrupt_handler();
  }
}
