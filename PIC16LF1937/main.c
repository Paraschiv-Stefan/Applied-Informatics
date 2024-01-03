#include <xc.h>
__PROG_CONFIG(1,0x3FE4);
__PROG_CONFIG(2,0x1EFF);
#define  _XTAL_FREQ 16000000
void main(void)
 {
     unsigned i;
    OSCCON = 0x7B;
    ANSELD=0x00;
    TRISD=0x00;
    ANSELB=0x00;
    TRISB=0x00;
    PORTD=0x00;
    PORTB=0x00;
    while(1)
    {
          for(i=0b00100000;i<=0b10000000;i<<=1)
	  {
	     PORTB=i;
	    __delay_ms(500);
	  }
	  PORTB=0;
	  for(i=0b00000100;i<=0b01000000;i<<=1)
	  {
	      if(i==0b00010000) i<<=1;
	     PORTD=i;
	    __delay_ms(500);
	  }
	  PORTD=0;
	  for(i=0b01000000;i>=0b00000100;i>>=1)
	  {
	      if(i==0b00010000) i>>=1;
	     PORTD=i;
	    __delay_ms(500);
	  }
	  PORTD=0;
	
	  for(i=0b10000000;i>=0b00100000;i>>=1)
	  {
	     PORTB=i;
	    __delay_ms(500);
	  }
	  PORTB=0;
	
       }
	     
	  
 }
