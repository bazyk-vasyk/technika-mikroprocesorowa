#include "STM8S208R_for_mac.h"

#define D1 5 //PC5
#define D2 7 //PC7
#define D3 6 //PC6
#define D4 5 //PE5

#define S1 4 //PB4
#define S2 3 //PB3
#define S3 2 //PB2


unsigned short tim4_divider = 0;
unsigned int tim4_divider2 = 0;
unsigned int tim4_divider3 = 0;
volatile unsigned long tim4_divider4 = 0;

unsigned char led_status = 1;
//unsigned char zliczanie=0;
volatile unsigned char zliczanie3=0;
volatile unsigned long dzielnik = 1;

void delay( char ms)
{
    int i=0;
    for (i=0; i<(ms*100);i++);
}
void main()
{   
// D1
	PC_DDR |= 1<<D1;
	PC_CR1 |= 1<<D1;
	PC_CR2 &= ~(1<<D1);
	
	// D2
	PC_DDR |= 1<<D2;
	PC_CR1 |= 1<<D2;
	PC_CR2 &= ~(1<<D2);
	
	// D3
	PC_DDR |= 1<<D3;
	PC_CR1 |= 1<<D3;
	PC_CR2 &= ~(1<<D3);
    // D4
	PE_DDR |= 1<<D4;
	PE_CR1 |= 1<<D4;
	PE_CR2 &= ~(1<<D4);
	
	// S1
	PB_DDR &= ~(1<<S1);	
	PB_CR2 &= ~(1<<S1);
    // S2
	PB_DDR &= ~(1<<S2);
	PB_CR2 &= ~(1<<S2);
    // S3
	PB_DDR &= ~(1<<S3);
	PB_CR2 &= ~(1<<S3);
    
    PB_CR1 |= ((1<<S1) | (1<<S2) | (1<<S3)); 
	
    
    // TIM4
    TIM4_PSCR = 4;
    TIM4_ARR = 187;
    TIM4_IER |= 1 << 0;
    TIM4_CR1 |= 1 << 0;
    
    __asm__ ("rim");
while (1)
{
   if ((PB_IDR & (1<<S1)) == 0) 
    {
            for(volatile long d=0; d<10000; d++); // delay
            if ((PB_IDR & (1 << S1)) == 0) 
            {
                if (dzielnik >= 3) dzielnik /= 3; 
                while((PB_IDR & (1 << S1)) == 0)
                {
                    delay(10);
                }
            }
    }
    if ((PB_IDR & (1<<S2)) == 0) 
    {
            for(volatile long d=0; d<10000; d++);
            if ((PB_IDR & (1<<S2)) == 0) 
            {
                if (dzielnik < 30000) dzielnik *= 3; 
                while ((PB_IDR & (1<<S2)) == 0)
                {
                delay(10);
                }
            }
        }
   if ((PB_IDR & (1<<S3)) == 0) 
    {
        for(volatile long d = 0; d < 10000; d++); // delay
        if ((PB_IDR & (1 << S3)) == 0) 
        {
            zliczanie3++;
            if(zliczanie3 == 1)
            {
                TIM4_CR1 &= ~(1 << 0); 
            }
            else 
            {
                zliczanie3 = 0;
                TIM4_CR1 |= (1 << 0);
            }
            while((PB_IDR & (1<<S3)) == 0)
            {
                delay(10);
            }
            
        }
    }
}

}
void foo(void) __interrupt(23)
{
    TIM4_SR &= ~(1 << 0);

tim4_divider++;
tim4_divider2++;
tim4_divider3++;
tim4_divider4++;

if (tim4_divider >= (2*dzielnik))
{
tim4_divider = 0;
PC_ODR ^= (1 << D1);
}

if (tim4_divider2 >= (222*dzielnik))
{
tim4_divider2 = 0;
PC_ODR ^= (1 << D2);
}

if (tim4_divider3 >= (444*dzielnik))
{
tim4_divider3 = 0;
PC_ODR ^= (1 << D3);
}
if (tim4_divider4 >= (2000*dzielnik))
{
tim4_divider4 = 0;
PE_ODR ^= (1 << D4);
}

return;
}