#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

#define A4 4545
#define C5 3822
#define B3 2025
#define G3 2551
#define E3 3033
#define C3 3846
#define C4 1911
#define D4 1703
#define E4 1517
#define B  494
#define D  294
#define A  440



void buzzer_init(){
  timerAUpmode();
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6;
}

void buzzer_set_period(short cycles){
  CCR0 = cycles;
  CCR1 = cycles >> 1;
}

void kimPossible(){
  int notes[] = {A4,0,A4,0,0,C5,0,0,A4};
  int i = 0;
  while(i<sizeof(notes)){
      int temp = 0;
      while (temp <40){
	int temp2 = 0;
	while(temp2 < 2000){
	  temp2++;
	}
	temp++;
      }
      buzzer_set_period(notes[i]);
      i++;
    }
    
  // for (int i =0; i<sizeof(notes)/sizeof(*notes);i++){
    // buzzer_set_period(notes[i]);
    // __delay_cycles(850000);
  // }
}
void soundTwo(){
  int notes[] = {E4,0,G3,0,B3,D4};
  int i = 0;
  while(i<sizeof(notes)){
      int temp = 0;
      while (temp < 40){
	int temp2 = 0;
	while(temp2 < 2000){
	  temp2++;
	}
	temp++;
      }
    buzzer_set_period(notes[i]);
    i++;
  }
    //    for(int i = 0; i<sizeof(notes)/sizeof(*notes);i++){
    // buzzer_set_period(notes[i]);
      //      __delay_cycles(850000);
   
  }

  void soundThree(){
    int notes[] = {C4,0,B,0};
    int i = 0;
    while(i<sizeof(notes)){
      int temp = 0;
      while(temp < 40){
	int temp2 = 0;
	while(temp2 < 2000){
	  temp2++;
	}
	temp++;
      }
     buzzer_set_period(notes[i]);
     i++;
    }
    // for (int i = 0; i<sizeof(notes)/sizeof(*notes);i++){
    //	buzzer_set_period(notes[i]);
	//	__delay_cycles(850000);
    // }
  }

  void soundFour(){
    int notes[] = {C,0,0,D,A};
    int i = 0;
    while(i<sizeof(notes)){
      int temp = 0;
      while(temp < 40){
	int temp2 = 0;
	while(temp2 < 2000){
	  temp2++;
	}
	temp++;
      }
      buzzer_set_period(notes[i]);
      i++;
    //   for (int i = 0; i<sizeof(notes)/sizeof(*notes); i++){
      //      buzzer_set_period(notes[i]);
      // __delay_cycles(850000);
    }
}
