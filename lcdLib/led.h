#ifndef led_included
#define led_included

//#define LED_RED BIT6
//#define LED_GREEN BIT0
//#define LEDS (BIT6 | BIT0)

int redControl(int on);
void drawFilledTriangle();
void drawThing();
void drawTriangle(char acol,char arow,char size,int color);
int blink();
void song();
void play(int dur);

#endif
