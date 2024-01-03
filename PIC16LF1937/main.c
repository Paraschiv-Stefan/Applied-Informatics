#include <xc.h>
__PROG_CONFIG  (1,0x3FE4);
__PROG_CONFIG  (2,0x1EFF); 
#define _XTAL_FREQ 16000000
#define LED1_scurt RB1
#define LED2_med RB2
#define LED3_lung RB3

void main(void)
 {
  OSCCON  = 0x7B; 
    TRISB =0b00000001;
    ANSELB =0x00;
    PORTB=0x00;
    while(1)
    {
       if(RB0 ==0)
       {
	  __delay_ms(800);
	  if(RB0 == 1) LED1_scurt  = 1;
	   else
	   { __delay_ms(1000);
	      if(RB0 == 1) LED2_med =1;
	      else LED3_lung = 1;
	   }
	    __delay_ms(2000) ;
	  PORTB= 0x00; 
	}
      }
 }
