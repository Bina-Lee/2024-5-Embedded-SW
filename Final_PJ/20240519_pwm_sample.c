#include "led.h"
#define V_UINT32 volatile unsigned int

void MyDelay_100ms(unsigned int n){
	volatile unsigned int delay;
	for(delay=0;delay<=n * 3600000;delay++);
}


#define PRESCALER_VALUE ((uint32_t)(SystemCoreClock / 1000000) - 1)
#define PERIOD_VALUE (20000 - 1)

void GPIO_Config_TIM3_PB4_ARD3_PWM(void){
    *(volatile unsigned int*)(0x40023830) |= 0x01U<<1;
    *(volatile unsigned int*)(0x40020400) |= 0x02U<<(4*2);
    *(volatile unsigned int*)(0x40020420) |= 0x02U<<(4*4);
}

void TIM3_PB4_ARD3_PWM_Config(void){
    *(volatile unsigned int*)(0x40023840) |= 0x01U<<1;
    *(volatile unsigned int*)(0x40000428) = PRESCALER_VALUE;
    *(volatile unsigned int*)(0x4000042C) = PERIOD_VALUE;
    *(volatile unsigned int*)(0x40000434) = 1500;
    *(volatile unsigned int*)(0x40000418) |= 0x06U<<4;
    *(volatile unsigned int*)(0x40000420) |= 0x01U<<0;
    *(volatile unsigned int*)(0x40000400) |= 0x01U<<0;
}

void GPIO_Config_TIM3_PC7_ARD0_PWM(void){
    *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;
    *(volatile unsigned int*)(0x40020800) |= 0x02U<<(7*2);
    *(volatile unsigned int*)(0x40020820) |= 0x02U<<(7*4);
}

void TIM3_PC7_ARD0_PWM_Config(void){
    *(volatile unsigned int*)(0x40023840) |= 0x01U<<2;
    *(volatile unsigned int*)(0x40000428) = PRESCALER_VALUE;
    *(volatile unsigned int*)(0x4000042C) = PERIOD_VALUE;
    *(volatile unsigned int*)(0x40000438) = 1500;
    *(volatile unsigned int*)(0x40000418) |= 0x06U<<12;
    *(volatile unsigned int*)(0x40000420) |= 0x01U<<4;
    *(volatile unsigned int*)(0x40000400) |= 0x01U<<0;
}

int main(void){
    hwInit();

    GPIO_Config_TIM3_PB4_ARD3_PWM();
    TIM3_PB4_ARD3_PWM_Config();
    GPIO_Config_TIM3_PC7_ARD0_PWM();
    TIM3_PC7_ARD0_PWM_Config();
    *(volatile unsigned int*)(0x40000400) |= 0x01U<<0;

    while (1){
        *(volatile unsigned int*)(0x40000434) = 500;
        MyDelay_100ms(1);
        *(volatile unsigned int*)(0x40000438) = 500;
        MyDelay_100ms(1);
        *(volatile unsigned int*)(0x40000434) = 1000;
        MyDelay_100ms(1);
        *(volatile unsigned int*)(0x40000438) = 1000;
        MyDelay_100ms(1);
    }


    return 0;
}
