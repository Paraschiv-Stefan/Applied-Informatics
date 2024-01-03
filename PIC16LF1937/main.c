#include <xc.h>
__PROG_CONFIG(1,0x3FE4); 
__PROG_CONFIG(2,0x1EFF); 
unsigned char a;
unsigned int b;
void main(void)
{
   	OSCCON = 0x6B;
	 TRISB = 0b00000000; 
	 PORTB = 0b00000000; 
	 OPTION_REG = 0b00000011; 
	 TMR0IF = 0; 
	 TMR0 = 250; 
while (1) 
 {
   for (a=0x01; a< 0x80; a<<=1) 
   {
      PORTB = a;
	for(b=0; b<6551; b++) 
	 { 
	    while(!TMR0IF);
	    TMR0 = 250; 
	    TMR0IF = 0;
	  }
    }
   for (a=0x80; a> 0x01; a>>=1)
   {
      PORTB = a;
      for(b=0; b<6551; b++) 
      { 
	 while(!TMR0IF);
	 TMR0 = 250; 
	 TMR0IF = 0;
      }
   }
  }
}

