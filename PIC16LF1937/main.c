#include <xc.h>
#include <string.h>

__PROG_CONFIG(1,0x3FE4); // config. uC (WDT=dis|OSC=int)
__PROG_CONFIG(2,0x3EFF); // config. uC (PLL (OSC*4)=off) 
int nr1,nr2,nr3,tens,r=0,units;
unsigned char v[10] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90 };
void init(void);
void send_string(const char* buffer, int size);
void main(void)
{
    init();
    while (1)
    {
      if(r==0)
      {
	  send_string("\r\n type the firs number: ",strlen("\r\n type the firs number: "));
	  r++;
      }
        if(RCIF)
	{
	 r++;
	 if(r==2)
	 {
	    nr1=RCREG;
	    TXREG=nr1;
	    nr1=nr1-'0';
	    send_string("\r\n type the second number: ",strlen("\r\n type the second number: "));
	  }
	  if(r==3)
	  {
	    nr2=RCREG;
	    TXREG=nr2;
	    nr2=nr2-'0';
	    nr3=nr1*nr2;
	    tens=nr3/10+'0';
	    units=nr3%10+'0';
	    send_string("\r\n the result of the product is = ",strlen("\r\n the result of the product is = "));
	    TXREG=tens;
	    while(!TXIF);
	    TXREG=units;
	    while(!TXIF);
	    r=0;
	    nr3=0;
	    }
	}
    }
}

void init(void)
{
    OSCCON = 0x73;
    ANSELB = 0x00;
    TRISB = 0x00;
    PORTB = 0x00;
    TRISC = 0b10111111;
    PORTC = 0x00;
    ANSELD = 0x00;
    TRISD = 0x00;
    PORTD = 0xFF;

    SPBRG = 12;
    TXEN = 1;
    BRGH = 0;
    SPEN = 1;
    CREN = 1;
    BRG16 = 0;
    SYNC = 0;

    T1CON = 0x11;
    TMR1IE = 1;
    PEIE = 1;
    GIE = 1;
}

void send_string(const char* buffer, int size)
{
   while(size)
 {
 TXREG = *buffer;
 while(!TXIF); 
 buffer++;
 size--;
 }
} 

