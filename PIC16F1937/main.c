#include <xc.h>
__PROG_CONFIG(1,0x3FE4); 
__PROG_CONFIG(2,0x3EFF); 
unsigned char a=0;
unsigned int b;
double k;
unsigned char cifra1, cifra2,zecimala3;
unsigned char cifra[10] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned char cifr1[10]= { 0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};
unsigned char digit[5] = { 0xFE, 0xFD, 0xFB, 0xF7, 0xFF};
void init (void);
void interrupt ia2(void); 
unsigned int read_adc(void);
void main(void)
{
     init();
      while (1) 
      {
	 k= read_adc(); 
	 k = (k*52)/255;
	 k=k*10;
	 b=(int)k;
	 zecimala3 = (b % 10); 
	 cifra2 = (b / 10)%10; 
	 cifra1 = (b / 100)%10; 
      }
}
unsigned int read_adc(void)
{
   GO_nDONE = 1; 
   while(GO_nDONE); 
   return ADRESH; 
}
void init (void)
{
   OSCCON = 0x73; 
   ANSELA = 0xFF; 
   TRISA = 0xFF; 
   ANSELB = 0x00; 
   TRISB = 0x00; 
   PORTB = 0xFF; 
   TRISC = 0xFF; 
   ANSELD = 0x00; 
   TRISD = 0x00; 
   T1CON = 0x11; 
   ADCON0 = 0x11; 
   ADCON1 = 0x60; 
   TMR1IE = 1; 
   PEIE = 1; 
   GIE = 1; 
}
void interrupt ia2(void) 
{ 
   if(TMR1IF) 
   {
      TMR1IF = 0; 
      TMR1H = 0xF6;
      TMR1L = 0x3B;
     if(!RC2)
      switch(a++)
      {
	 case 0:
	 PORTB = digit[4]; 
	 PORTD = cifra[cifra1];
	 PORTB = digit[1];
	 break;
	 case 1:
	 PORTB = digit[4]; 
	 PORTD = cifr1[cifra2];
	 PORTB = digit[2];
	 break;
	 case 2:
	 PORTB = digit[4]; 
	 PORTD = cifra[zecimala3];
	 PORTB = digit[3];
	 a=0;
	 break;
	 default: break;
      }
   	else  
	 switch(a++)
	 {
	    case 0:
	    PORTB = digit[4]; 
	    PORTD = cifra[cifra1];
	    PORTB = digit[2];
	    break;
	    case 1:
	    PORTB = digit[4]; 
	    PORTD = cifra[cifra2];
	    PORTB = digit[3];
	    a=0;
	    break;
	    default: break;
	  }
   }
 }
  
