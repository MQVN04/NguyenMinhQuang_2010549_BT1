#include "stdint.h"
#include "stm32f10x.h"
void SysTick_Handler(void);
int main(void){
	SysTick->LOAD  = (uint32_t)(SystemCoreClock/1000 - 1UL);                         /* set reload register */
  //NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); /* set Priority for Systick Interrupt */
  SysTick->VAL   = 0UL;                                             /* Load the SysTick Counter Value */
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_TICKINT_Msk   |
                   SysTick_CTRL_ENABLE_Msk;                         /* Enable SysTick IRQ and SysTick Timer */
	//SysTick_Config(SystemCoreClock/1000);
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH |=(3<<20);// MODE 13=11
	GPIOC->CRH &= ~(3UL<<22);// CNF 13=00
	
	
	while(1){
	}
}
void SysTick_Handler(void){
	static uint32_t tickcount = 0;
		tickcount++;

	if (tickcount ==500){
		if ((GPIOC->ODR & (1<<13)) == 0){
			GPIOC->ODR |= (1<<13);
		}
		else
			GPIOC->ODR &= ~(1<<13);
		tickcount=0;
 }
}
