#include "STM8S208R_for_mac.h"

main()
{
    //przycisk
	PE_DDR &= ~(1<<4);
	PE_CR1 |= (1<<4);
	PE_CR2 |=(1<<4);
	//led
    PC_DDR |= 1 << 5;
	PC_CR1 |= 1 << 5;
	PC_CR2 &= ~( 1 << 5);

    EXTI_CR2 |= (1 << 0);
    __asm__ ("rim");
    while (1);
}

void foo(void) __interrupt(7){
PC_ODR ^= (1 << 5);
return;
}
