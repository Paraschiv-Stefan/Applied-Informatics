#include <xc.h>
__PROG_CONFIG(1,0x3FE4); 
__PROG_CONFIG(2,0x1EFF);
#define _XTAL_FREQ 8000000 
unsigned char a=0;
unsigned char zm,um;
unsigned char cifr1[10]= { 0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};
unsigned char cifr2[10] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned char digit[5]={0xFE,0xFD,0xFB,0xF7,0xFF};
unsigned long stop;
unsigned int c,zmi,umi,k=0;
void init (void);
void interrupt ia2(void); 

void main(void)
{
   init();
  zm=0; um=0;
   while (1) 
   {
     if(!RA1)
     {
      stop=1;
      while(stop)
      {
	 if(c>=40)
	 {
	    c=0;
	    um++;
	    if(um> 9) 
	    { zm++; um=0;
	       if(zm>9) {zm=9;um=9; stop=0;}
	     }
	    if(RA2==0){zmi=zm; umi=um;}
	     if(!RA3)
	     {
	       stop=0;
	       __delay_ms(1000);
	       if(!RA3){ um=0;zm=0;}
	     }
	  }     
	}
      }
    if(RA3==0)
    {
      __delay_ms(1000);
      if(RA3==0){ um=0; zm=0; zmi=0; umi=0; RA0=0;}
    } 
    if(RA2==0 && k==0)
     {
      __delay_ms(500);
      RA0=1;
      a=2;
      k=1;
     }
    if(k==1 && RA2==0)
    { 
      __delay_ms(500);
      RA0=0;
      a=0;
      k=0;
    }
   }
}

void init (void)
{
	OSCCON=0x73;  
	ANSELB=0x00;
	TRISA=0x0E;
	ANSELA=0;
	TRISB=0x00;
	ANSELD=0x00;
	TRISD=0x00;
	PORTB=0xFF;
	PORTD=0xFF;
	T1CON=0x11;
	TMR1IE=1;
	PEIE=1;
	GIE=1;
	RA0=0;
}

void interrupt ia2(void) 
{ 
	if(TMR1IF)  
	{
 		TMR1IF = 0;  
 		TMR1H = 0xF6;  
 		TMR1L = 0x3B; 
 		c++;
	       switch(a++)
	       {
		  case 0: PORTB= digit[4]; PORTD=cifr2[um]; PORTB=digit[2]; break;
		  case 1: PORTB=digit[4]; PORTD=cifr1[zm]; PORTB=digit[1]; a=0; break; 
		  case 2: PORTB=digit[4]; PORTD=cifr1[zmi]; PORTB=digit[1]; break;
		  case 3: PORTB=digit[4]; PORTD=cifr2[umi]; PORTB=digit[2]; a=2; break;
		  default: break;
		 }
	 }
}
