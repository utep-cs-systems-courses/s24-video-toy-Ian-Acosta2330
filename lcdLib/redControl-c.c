#include <msp430.h>
#include "led.h"
#include "libTimer.h"

#define LED BIT6
#define SW2 BIT0

int redControl(int on) {
  int r = 0;
  if(on) {
    P1OUT |= LED;
  } else {
    P1OUT &= ~LED;
    r = 1;
  }
  
  return r;
  
}
