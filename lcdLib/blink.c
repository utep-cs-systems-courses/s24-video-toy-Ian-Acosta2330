#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include <stdlib.h>

static int once = 0;
#define LED BIT6

int blink (void) {
  P1DIR |= LED;
  P1OUT &= ~LED;
  P1OUT |= LED;
  
  configureClocks();
  enableWDTInterrupts();

  if(once) {
    //P1IFG &= LED_RED;
    P1OUT &= ~LED;
    WDTCTL = WDTPW | WDTHOLD;
    once = 0;
    return 0;
  }
  
  /*
  if(c) {
    P1OUT &= ~LED_RED;
    return 1;
    }*/
  /*
  int a = 0;
  while(a < 25) {
      P1OUT &= ~LED_RED;
      __delay_cycles(800000);
      P1OUT |= LED_RED;
      __delay_cycles(800000);
      a++;
  }*/
  
  or_sr(0x18);
}

// blink state machine
static int blinkLimit = 5;   //  state var representing reciprocal of duty cycle 
void blinkUpdate() // called every 1/250s to blink with duty cycle 1/blinkLimit
{
  static int blinkCount = 0; // state var representing blink state
  blinkCount ++;
  if (blinkCount >= blinkLimit) {
    blinkCount = 0;
    redControl(1);
  } else
    redControl(0);
}

void oncePerSecond() // repeatedly start bright and gradually lower duty cycle, one step/sec
{
  blinkLimit++;  // reduce duty cycle
  if (blinkLimit >= 8){  // but don't let duty cycle go below 1/7.
    blinkLimit = 0;
    once = 1;
    blink();
    //exit(0);
  }
}

void secondUpdate()  // called every 1/250 sec to call oncePerSecond once per second
{
  static int secondCount = 0; // state variable representing repeating time 0…1s
  secondCount ++;
  if (secondCount >= 250) { // once each second
    secondCount = 0;
    oncePerSecond();
  } }

void timeAdvStateMachines() // called every 1/250 sec
{
  blinkUpdate();
  secondUpdate();
}


void __interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  // handle blinking   
  timeAdvStateMachines();
} 
