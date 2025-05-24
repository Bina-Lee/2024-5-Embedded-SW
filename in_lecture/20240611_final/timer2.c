void TIM2_setting(){
    *(volatile unsigned int*)(0x40023840) |= 0x01U<<0;  //RCC_APB1ENR-TIM2EN

    *(volatile unsigned int*)(0x40000000) |= 0x01U<<0;  //TIM2_CR1-CEN

                            //system_clock : 216,000,000
                            //APB1 block -> 108,000,000
                            //2^31-1 : 2,147,483,647
    // *(volatile unsigned int*)(0x4000000C) |= 0x01U<<1;  //TIM2_DIER-CC1IE
    //                                         //output compare interrupt1
    // *(volatile unsigned int*)(0x4000000C) |= 0x01U<<2;  //TIM2_DIER-CC2IE
    //                                         //output compare interrupt2
    //         //CCR1 for actuator1 and CCR2 for actuator2
    // *(volatile unsigned int*)(0x40000010) &= ~(0x01U<<1);   //CC1IF clear
    // *(volatile unsigned int*)(0x40000010) &= ~(0x01U<<2);   //CC2IF clear

    *(volatile unsigned int*)(0x40000024) = 0;  //TIM2_CNT
    // *(volatile unsigned int*)(0x40000028) = 27 - 1;   //TIM2_PSC
    *(volatile unsigned int*)(0x40000028) = 43200 - 1;   //TIM2_PSC
                                            // CNT 10000 -> 1sec
    // *(volatile unsigned int*)(0x4000002C) = 8000000 - 1;   //TIM2_ARR
                                            //default value is 0xFFFFFFFF
                                            //use maximum value
                                            //don't use overflow
                                            // //먼저 2초간 테스트
    *(volatile unsigned int*)(0x4000000C) |= 0x01U<<0;  //TIM2_DIER-UIE
    *(volatile unsigned int*)(0x40000010) &= ~(0x01U<<0);   //TIM2_SR-UIF

    *(volatile unsigned int*)(0xE000E100) |= 0x01U<<28; //NVIC -> 28
}

void TIM2_IRQHandler(){
    if(*(volatile unsigned int*)(0x40000010) & (0x01U)){
        *(volatile unsigned int*)(0x40000010) &= ~(0x01U);   //TIM2_SR-UIF


    }
    // if(*(volatile unsigned int*)(0x40000010) & (0x01U<<1)){
    //     //Output Capture1
    //     *(volatile unsigned int*)(0x40000010) &= ~(0x01U<<1);
    //         //interrupt clear

    // }
    // if(*(volatile unsigned int*)(0x40000010) & (0x01U<<2)){
    //     //Output Capture2
    //     *(volatile unsigned int*)(0x40000010) &= ~(0x01U<<2);
    //         //interrupt clear

    // }
}