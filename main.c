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
unsigned char led_status = 0;

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
	
	// S1
	PB_DDR &= ~(1<<S1);
	PB_CR1 &= ~(1<<S1);
	PB_CR2 &= ~(1<<S1);
    // S2
	PB_DDR &= ~(1<<S2);
	PB_CR1 &= ~(1<<S2);
	PB_CR2 &= ~(1<<S2);
	
    
    // TIM4
    TIM4_PSCR = 2;
    TIM4_ARR = 249;
    TIM4_IER |= 1 << 0;
    TIM4_CR1 |= 1 << 0;
    
    __asm__ ("rim");
while (1)
{
if ((PB_IDR & (1<<S1)) == 0) 
    {
            for(volatile long d=0; d<10000; d++); // delay
            if ((PB_IDR & (1<<S1)) == 0) {
                led_status=1;
            }
    }
if ((PB_IDR & (1<<S2)) == 0) 
    {
            for(volatile long d=0; d<10000; d++); // delay
            if ((PB_IDR & (1<<S2)) == 0) {
                led_status=0;
                 PC_ODR |= (1<<D1) | (1<<D2) | (1<<D3);
            }
    }
}
}
void foo(void) __interrupt(23)
{
    TIM4_SR &= ~(1 << 0);
    if(led_status==0) 
        {   
            return;
        }
tim4_divider++;
tim4_divider2++;
tim4_divider3++;

if (tim4_divider >= 5)
{
tim4_divider = 0;
PC_ODR ^= (1 << D1);
}

if (tim4_divider2 >= 200)
{
tim4_divider2 = 0;
PC_ODR ^= (1 << D2);
}

if (tim4_divider3 >= 6000)
{
tim4_divider3 = 0;
PC_ODR ^= (1 << D3);
}

return;
}