void interrupt_setting_PG6_ARD2(){
    *(volatile unsigned int*)(0x40023830) |= 0x00000040U;	
        //RCC_GPIOG clock enable
    *(volatile unsigned int*)(0x40021800) &= ~(0x03U<<(6*2));
    // *(volatile unsigned int*)(0x40021808) &= ~(0x03U<<(6*2));
    *(volatile unsigned int*)(0x4002180C) &= ~(0x03U<<(6*2));

    *(volatile unsigned int*)(0x40023844) |= 0x01U<<14; 
        //RCC_APB2ENR - SYSSCFEN
    *(volatile unsigned int*)(0x4001380C) |= 0x06U<<((6%4) * 4);    
        //SYSCFG_EXTICR2 - EXTI6 - PG6
    *(volatile unsigned int*)(0x40013C00) |= 0x01U<<6;  
        //EXTI_IMR - IM6
    *(volatile unsigned int*)(0x40013C08) |= 0x01U<<6;  
        //EXTI_RTSR - TR6   //rising edge trigger

    *(volatile unsigned int*)(0xE000E100) |= 1<<23;  
        //NVIC  //Position-23-EXTI9_5
}

void interrupt_setting_PB4_ARD3(){
    *(volatile unsigned int*)(0x40023830) |= 0x01U<<1;
        //RCC_GPIOB clock enable
    *(volatile unsigned int*)(0x40020400) &= ~(0x03U<<(4*2));
    // *(volatile unsigned int*)(0x40020408) &= ~(0x03U<<(4*2));
    *(volatile unsigned int*)(0x4002040C) &= ~(0x03U<<(4*2));

    *(volatile unsigned int*)(0x40023844) |= 0x01U<<14; 
        //RCC_APB2ENR - SYSSCFEN
    *(volatile unsigned int*)(0x4001380C) |= 0x01U<<((4%4) * 4);    
        //SYSCFG_EXTICR2 - EXTI4 - PB4
    *(volatile unsigned int*)(0x40013C00) |= 0x01U<<4;  
        //EXTI_IMR - IM4
    *(volatile unsigned int*)(0x40013C08) |= 0x01U<<4;  
        //EXTI_RTSR - TR4   //rising edge trigger

    *(volatile unsigned int*)(0xE000E100) |= 1<<10;  
        //NVIC  //Position-10-EXTI4
}

void EXTI9_5_IRQHandler(){
    if(*(volatile unsigned int*)(0x40013C14) & (0x01U<<6)){
        //PG6
        *(volatile unsigned int*)(0x40013C14) |= 0x01U<<6;  //EXTI_PR-PR6 clear
        
        
    }
}

void EXTI4_IRQHandler(){
    if(*(volatile unsigned int*)(0x40013C14) & (0x01U<<4)){
        //PB4
        *(volatile unsigned int*)(0x40013C14) |= 0x01U<<4;
            //interrupt clear
            

        
    }
}