#include <plib.h>


#define a1 PORTEbits.RE5
#define b1 PORTEbits.RE6
#define c1 PORTEbits.RE7
#define d1 PORTGbits.RG6
#define a2 PORTGbits.RG7
#define b2 PORTGbits.RG8
#define c2 PORTBbits.RG6
#define d2 PORTBbits.RG7

//we use E, G, and B ports so need to initialize all three

//COMMON CATHODE
/*
I need to get the three readings from A, B, C and pick the max. the largest one is
what gets displayed. there must be an interrupt routine that gets called every 100ms
to update the digits of the display */

//decimal point is hard coded on

void init_display() {
  //declare all pins as GPIO
  //declare all pins as output TRISx = 0 is output, TRISx = 1 is input
  mPORTESetPinsDigitalOut(BIT_5 | BIT_6 | BIT_7);
  mPORTGSetPinsDigitalOut(BIT_6 | BIT_7 | BIT_8);
  mPORTBSetPinsDigitalOut(BIT_6 | BIT_7);
  //zero the pins
  mPORTEClearBits(BIT_5 | BIT_6 | BIT_7);
  mPORTGClearBits(BIT_6 | BIT_7 | BIT_8);
  mPORTBClearBits(BIT_6 | BIT_7);
  //TRISE = 0x00;
  //TRISG = 0x00;
  //TRISB = 0x00;

  //start display ISR
  //TODO
}
/* returns 0 on good return, -1 on failure */
int draw_digit(int pos, int digit) {
  if (pos == 1) {
    switch (digit) {
    case 0:
      a1 = 0;
      b1 = 0;
      c1 = 0;
      d1 = 0;
      break;
    case 1:
      a1 = 1;
      b1 = 0;
      c1 = 0;
      d1 = 0;
      break;
    case 2:
      a1 = 0;
      b1 = 1;
      c1 = 0;
      d1 = 0;
      break;
    case 3:
      a1 = 1;
      b1 = 1;
      c1 = 0;
      d1 = 0;
      break;
    case 4:
      a1 = 0;
      b1 = 0;
      c1 = 1;
      d1 = 0;
      break;
    case 5:
      a1 = 1;
      b1 = 0;
      c1 = 1;
      d1 = 0;
      break;
    case 6:
      a1 = 0;
      b1 = 1;
      c1 = 1;
      d1 = 0;
      break;
    case 7:
      a1 = 1;
      b1 = 1;
      c1 = 1;
      d1 = 0;
      break;
    case 8:
      a1 = 0;
      b1 = 0;
      c1 = 0;
      d1 = 1;
      break;
    case 9:
      a1 = 1;
      b1 = 0;
      c1 = 0;
      d1 = 1;
      break;
    default:
      a1 = 1;
      b1 = 0;
      c1 = 1;
      d1 = 0;
      return -1;
    }
  }
  else if (pos == 2) {
    switch (digit) {
    case 0:
      a2 = 0;
      b2 = 0;
      c2 = 0;
      d2 = 0;
      break;
    case 1:
      a2 = 1;
      b2 = 0;
      c2 = 0;
      d2 = 0;
      break;
    case 2:
      a2 = 0;
      b2 = 1;
      c2 = 0;
      d2 = 0;
      break;
    case 3:
      a2 = 1;
      b2 = 1;
      c2 = 0;
      d2 = 0;
      break;
    case 4:
      a2 = 0;
      b2 = 0;
      c2 = 1;
      d2 = 0;
      break;
    case 5:
      a2 = 1;
      b2 = 0;
      c2 = 1;
      d2 = 0;
      break;
    case 6:
      a2 = 0;
      b2 = 1;
      c2 = 1;
      d2 = 0;
      break;
    case 7:
      a2 = 1;
      b2 = 1;
      c2 = 1;
      d2 = 0;
      break;
    case 8:
      a2 = 0;
      b2 = 0;
      c2 = 0;
      d2 = 1;
      break;
    case 9:
      a2 = 1;
      b2 = 0;
      c2 = 0;
      d2 = 1;
      break;
    default:
      a2 = 1;
      b2 = 0;
      c2 = 1;
      d2 = 0;
      return -1;
    }
  }
  else return -1;
  return 0;

}

