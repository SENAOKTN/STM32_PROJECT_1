#include "stm32f4xx.h"

volatile static int led=12;

void EXTI0_IRQHandler(void){
    if(EXTI->PR & EXTI_PR_PR0){
       EXTI->PR |= EXTI_PR_PR0;

       GPIOD->ODR &= ~(0xFFFF<<0);
       SysTick->VAL = 0;
       SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk ;
    }     
}
void SysTick_Handler(void);
void SysTick_Handler(void){

    GPIOD->ODR |= (1<<12);
    SysTick->CTRL &= ~ (SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk);


}
int main(void){
   
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    GPIOD->MODER |= GPIO_MODER_MODER0_0 |
                    GPIO_MODER_MODER1_0 |
                    GPIO_MODER_MODER2_0 |
                    GPIO_MODER_MODER3_0 |
                    GPIO_MODER_MODER4_0 |
                    GPIO_MODER_MODER5_0 |
                    GPIO_MODER_MODER6_0 |
                    GPIO_MODER_MODER7_0 |
                    GPIO_MODER_MODER8_0 |
                    GPIO_MODER_MODER9_0 |
                    GPIO_MODER_MODER10_0 |
                    GPIO_MODER_MODER11_0 |
                    GPIO_MODER_MODER12_0 |
                    GPIO_MODER_MODER13_0 |
                    GPIO_MODER_MODER14_0 |
                    GPIO_MODER_MODER15_0;

    GPIOD->ODR |= (1<<13);

    SYSCFG->EXTICR[0]&= ~SYSCFG_EXTICR1_EXTI0;
    NVIC_EnableIRQ(EXTI0_IRQn);
    EXTI->IMR |= EXTI_IMR_MR0;
    EXTI->RTSR |= EXTI_RTSR_TR0;
    

    SysTick->LOAD = (SystemCoreClock / 2) - 1;   
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  
	SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk);

    while (1) {

	}	
}
