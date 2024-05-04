#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

void drawThing() {
   drawPart(20,20,COLOR_BLACK);
   drawPart(30,30,COLOR_BLACK);
}

void drawPart(char col, char row, int color) {

  for(int i = row - 5; i <= row + 5; i++) {

    for(int j = col - 5; j <= col + 5; j++) {

      drawPixel(j, i, color);

    }
  }
  drawString5x7(5,5,"meow",COLOR_WHITE, COLOR_BLACK);
}
