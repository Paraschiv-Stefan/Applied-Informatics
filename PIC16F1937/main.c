#include <xc.h> 
#define LED1 RE2
#define LED2 RB2
unsigned long y; 
void main(void)
{
TRISE = 0x00; 
ANSELE = 0x00;
TRISB= 0x00;
ANSELB=0x00;
while (1)
 {
 LED1 = 1; 
  LED2 = 0; 
 for(y=0; y<10000; y++); 
 LED2=1;
 LED1= 0; 
 for(y=0; y<10000; y++); 
 }
}
