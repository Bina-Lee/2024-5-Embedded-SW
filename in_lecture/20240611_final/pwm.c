void GPIO_Config_TIM3_PC6_ARD1_PWM(){
    *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;
        //RCC_AHB2ENR GPIOC enable
    *(volatile unsigned int*)(0x40020800) |= 0x02U<<(6*2);
        //GPIOC MODER6 Alternate function mode - TIM
    *(volatile unsigned int*)(0x40020820) |= 0x02U<<(6*4);
        //GPIOC_AFRL AFR6 - set AF2 - Link TIM3 Channel2
}

void TIM3_PC6_ARD1_PWM_Config(){
    *(volatile unsigned int*)(0x40023840) |= 0x01U<<1;
        //RCC_APB1ENR - TIM3 enable
    *(volatile unsigned int*)(0x40000428) = 108 - 1;
        //set Prescaler value
    *(volatile unsigned int*)(0x4000042C) = 20000 - 1;
        //set Auto Reload register value
        //APB1 block's clock is 108MHz
        // 108,000,000/(108 * 20000) = 50(Hz)
    *(volatile unsigned int*)(0x40000434) = 1000;
        //TIM3 capture/compare register
        // 1000 -> 1ms(ARR = 20000 - 1)
    *(volatile unsigned int*)(0x40000418) |= 0x06U<<4;
        //TIM3_CCMR1 - OC1M
        //Output compare 1 mode
        //PWM mode 1
    *(volatile unsigned int*)(0x40000420) |= 0x01U<<0;
        //TIM3_CCER - CC1E
        //Capture/Compare 1 output enable
    *(volatile unsigned int*)(0x40000400) |= 0x01U<<0;
        //TIM3_CR1 - CEN
        //Counter enable
}

//CH2
void GPIO_Config_TIM3_PC7_ARD0_PWM(){
    *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;
    *(volatile unsigned int*)(0x40020800) |= 0x02U<<(7*2);
    *(volatile unsigned int*)(0x40020820) |= 0x02U<<(7*4);
}

void TIM3_PC7_ARD0_PWM_Config(){
    *(volatile unsigned int*)(0x40023840) |= 0x01U<<2;
    *(volatile unsigned int*)(0x40000428) = 108 - 1;
    *(volatile unsigned int*)(0x4000042C) = 20000 - 1;
    *(volatile unsigned int*)(0x40000438) = 1000;
    *(volatile unsigned int*)(0x40000418) |= 0x06U<<12;
        //TIM3_CCMR1 - OC2M
        //Output compare 2 mode
        //PWM mode 1
    *(volatile unsigned int*)(0x40000420) |= 0x01U<<4;
        //TIM3_CCER - CC2E
        //Capture/Compare 2 output enable
    *(volatile unsigned int*)(0x40000400) |= 0x01U<<0;
}