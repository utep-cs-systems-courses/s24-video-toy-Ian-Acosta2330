#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
//#include "led.h"
//#include "buzzer.h"

void drawFilledTriangle(u_char acol, u_char arow, u_int color, u_char size) {
  int i;
  int j;
    
  for(i = 0; i <= size; i++) {
    for(j = acol-i; j < acol+i; j++) {
      drawPixel(j,i+arow,color);
    }
  }
}
