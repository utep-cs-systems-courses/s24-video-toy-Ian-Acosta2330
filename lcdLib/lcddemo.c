/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */
#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "buzzer.h"

#define LED BIT6

#define SW1 BIT3

#define SW2 1
#define SW3 BIT1
#define SW4 BIT2
#define SW5 BIT3


#define SWITCH_1 SW1
#define SWITCH_2 SW2
#define SWITCH_3 SW3
#define SWITCH_4 SW4
#define SWITCH_5 SW5

#define SWITCH_P2 ( SWITCH_2 | SWITCH_3 | SWITCH_4 | SWITCH_5)

volatile int red_on = 0;
volatile int green_on = 0;
volatile int redDim = 0;

static void drawTriangle(u_char acol, u_char arow, u_char size, u_int color) {
  int i;
  /*
  for(i = arow-size; i < size+arow; i++) {
    for(j = acol-size; j < size+acol; j++) {
      drawPixel(j, i, color);
    } 
  }   */

  for(i = arow-size;i < size+arow;i++) {
    drawPixel(i,i,color);
  }
  for(i = arow+size;i > arow-size;i--) {
    drawPixel(i,arow+size,color);
  }
  for(i = arow-size; i < arow+size;i++) {
    drawPixel(acol,i,color);
  }
    
}

static void drawFilledTriangle(u_char acol, u_char arow, u_int color) {
  int i;
  int j;
  
  for(i = 0; i <= 60; i++) {
    for(j = acol-i; j < acol+i; j++) {
      drawPixel(j,i+arow,color);
    }
  }
}

volatile u_char width = screenWidth>>1, height = screenHeight>>1;

int main(void) {
   P1DIR |= LED;
   P1OUT &= ~LED;

  configureClocks(); //always include
  lcd_init(); //Initializes the whole lcd
  buzzer_init();

  clearScreen(COLOR_WHITE);
  //drawBox(width, height, 15, COLOR_RED);

  
  P1REN |= SWITCH_1;
  P1IE |= SWITCH_1;
  P1OUT |= SWITCH_1;
  P1DIR &= ~SWITCH_1;
  
  
  P2REN |= SWITCH_P2;
  P2IE |= SWITCH_P2;
  P2IES |= SWITCH_P2;
  P2OUT |= SWITCH_P2;

  or_sr(0x18);
}

  //drawString5x7(20,20, "omg >_<", COLOR_WHITE, COLOR_BLACK);

  // fillRectangle(30,30, 60, 60, COLOR_RED);
  /*
  short centerCol = screenWidth >> 1;
  short centerRow = screenHeight >> 1;

  int x = 0;
  int y = 0;
  int speed = 6;
  for(short i= 0;i < screenWidth; i++) {
    drawPixel(x,centerRow - y, COLOR_PINK);
    drawPixel(x,centerRow - speed, COLOR_GREEN);
    x++;
    y+=speed;
    speed -= 1;
    if(y<= 0)
      speed = -speed;
   }
   }*/


/*
void drawBox(u_char acol, u_char arow, u_char size, u_int color) {
  u_char max_col = acol + size;
  u_char max_row = arow + size;
  
  for (u_char col = acol - size; col < max_col; col++) {
    for(u_char row = arow - size; row < max_row; row++) {
      drawPixel(col, row, color);
    }
  }
  }*/


void switch_interrupt_handler_P1() {
  char p1val = P1IN;
  
  P1IES |= (p1val & SWITCH_1);
  P1IES &= (p1val | ~SWITCH_1);

  if (p1val & SW1) {
    //P1OUT &= ~LEDS;
    //P1OUT &= ~LED_GREEN;
    // buzzer_set_period(0);
    //redControl(1);
   
  } else {
    P1OUT |= LED;
    red_on = 1;
    green_on = 1;
    clearScreen(COLOR_BLACK);
    drawTriangle(width, height, 15, COLOR_RED);

    //redControl(0);
    //P1OUT |= LED_GREEN;
    //buzzer_set_period(800);
  }
}

/*
void song(int A, int B, int C4, int D, int E, int F, int G) {
  buzzer_set_period(A);
  buzzer_set_period(0);
}*/


void switch_interrupt_handler_P2_2() {
  char p2val = P2IN;
  
  P2IES |= (p2val & SWITCH_2);
  P2IES &= (p2val | ~SWITCH_2);
  
  if(p2val & SW2) {

    //red_on = 0;
    //P1OUT &= ~LED_RED;
    //buzzer_set_period(0);
  } else {
    if(red_on) {
      red_on = blink();
    }
    //red_on = redControl(red_on);
    //buzzer_set_period(800);
    //redControl(1);
  }  
  }

void switch_interrupt_handler_P2_3() {
  char p2val = P2IN;
  P2IES |= (p2val & SWITCH_3);
  P2IES &= (p2val | ~SWITCH_3);

 if(p2val & SW3) {
    //P1OUT &= ~LED_GREEN;
    green_on = 0;
    //buzzer_set_period(0);
 } else {
    //P1OUT |= LED_GREEN;
    //buzzer_set_period(3300);
    green_on = 1;
    clearScreen(COLOR_RED);
    drawFilledTriangle(width, height, COLOR_BLACK);

  }
}

void switch_interrupt_handler_P2_4() {
  char p2val = P2IN;
  P2IES |= (p2val & SWITCH_4);
  P2IES &= (p2val | ~SWITCH_4);
  if (p2val & SW4) {

  }else {
    P1OUT &= ~LED;
  }
}

void switch_interrupt_handler_P2_5() {
  char p2val = P2IN;
  P2IES |= (p2val & SWITCH_5);
  P2IES &= (p2val | ~SWITCH_5);
  if(p2val & SW5) {
    buzzer_set_period(0);
  } else {
    buzzer_set_period(4940);
    __delay_cycles(10000000);
    buzzer_set_period(4440);
    __delay_cycles(10000000);
    buzzer_set_period(0);
    /* buzzer_set_period(4940);
    __delay_cycles(2500000);
    buzzer_set_period(5240);
    */
  }
}

void __interrupt_vec(PORT1_VECTOR) Port_1() {
  if(P1IFG & SWITCH_1) {
    P1IFG &= ~SWITCH_1;
    switch_interrupt_handler_P1();
  }
}

void __interrupt_vec(PORT2_VECTOR) Port_2() {
  if (P2IFG & SWITCH_2) {
    P2IFG &= ~SWITCH_2;
    switch_interrupt_handler_P2_2();
    }
  if (P2IFG & SWITCH_3) {
    P2IFG &= ~SWITCH_3;
    switch_interrupt_handler_P2_3();
  }
  if (P2IFG & SWITCH_4) {
    P2IFG &= ~SWITCH_4;
    switch_interrupt_handler_P2_4();
  }
  if(P2IFG & SWITCH_5) {
    P2IFG &= ~SWITCH_5;
    //song();
    switch_interrupt_handler_P2_5();
  }
}


  
