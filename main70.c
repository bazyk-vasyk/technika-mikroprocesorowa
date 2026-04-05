#include "STM8S208R_for_mac.h"

main()
{
    //przycisk
	PB_DDR &= ~(1<<3);
	PB_CR1 |= (1<<3);
	PB_CR2 |=(1<<3);
	//led
    //D2
    PC_DDR |= (1<<7);
	PC_CR1 |= (1<<7);
	PC_CR2 &= ~(1<<7);
	//D1
	PC_DDR |= (1<<5);
	PC_CR1 |= (1<<5);
	PC_CR2 &= ~(1<<5);
    //D3
    PC_DDR |= (1<<6);
	PC_CR1 |= (1<<6);
	PC_CR2 &= ~(1<<6);
    //D4
    PE_DDR |= (1<<5);
	PE_CR1 |= (1<<5);
	PE_CR2 &= ~(1<<5);

    EXTI_CR1 |= (3 << 2);
    __asm__ ("rim");
    while (1);
}
void foo(void) __interrupt(4){
if (!(PB_IDR & (1 << 3))) {
        // 0- wciśnięty
        PC_ODR |= (1 << 6); 
        PE_ODR |=((1 << 5)); 
        PC_ODR &= ~((1 << 7) | (1 << 5)); //zero zeby włączyc
    } else {
        // 1-odpuszczony
        PC_ODR |= (1 << 7) | (1 << 5);  //wyłączamy
        PC_ODR &= ~((1 << 6)); 
        PE_ODR &= ~((1 << 5)); 
    }
return;
}