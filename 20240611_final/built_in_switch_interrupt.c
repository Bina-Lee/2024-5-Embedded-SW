void switch12_interrupt_setting(){
    //switch2 PC12
    *(volatile unsigned int*)(0x40023830U) |= 0x00000004U;      //RCC
    *(volatile unsigned int*)(0x40020800U) &= ~(0x03U<<(12*2));   //GPIOC-12
    *(volatile unsigned int*)(0x4002080CU) &= ~(0x03U<<(12*2));

    *(volatile unsigned int*)(0x40023844) |= 0x01U<<14;
    *(volatile unsigned int*)(0x40013814) |= 0x02U<<((12%4) * 4);
    *(volatile unsigned int*)(0x40013C00) |= 0x01U<<12;  //EXTI_IMR - IM12
    *(volatile unsigned int*)(0x40013C08) |= 0x01U<<12; //EXTI_RTSR - TR12  //rising edge

    *(volatile unsigned int*)(0x40013C18) |= 0x01<<8;

    //switch1  PG3 
    *(volatile unsigned int*)(0x40023830U) |= 0x00000040U;      //RCC
    *(volatile unsigned int*)(0x40021800U) &= ~(0x03U<<(3*2));   //GPIOG-3
    *(volatile unsigned int*)(0x4002180CU) &= ~(0x03U<<(3*2));

    *(volatile unsigned int*)(0x40023844) |= 0x01U<<14; //RCC_APB2ENR - SYSSCFEN
    *(volatile unsigned int*)(0x40013808) |= 0x06U<<((3%4) * 4);//SYSCFG_EXTICR1 - EXTI3 - PG3
    *(volatile unsigned int*)(0x40013C00) |= 0x01U<<3;  //EXTI_IMR - IM3
    *(volatile unsigned int*)(0x40013C08) |= 0x01U<<3;  //EXTI_RTSR - TR3   //rising edge trigger

    *(volatile unsigned int*)(0xE000E100) |= 0x01<<9;  
        //NVIC  //Position-9-EXTI9_3
}

void EXTI15_10_IRQHandler(){
if(*(volatile unsigned int*)(0x40013C14) & (0x01U<<12)){
        //PC12
        *(volatile unsigned int*)(0x40013C14) |= 0x01U<<12;
            //interrupt clear
            

        
    }
}

void EXTI3_IRQHandler(){
    if(*(volatile unsigned int*)(0x40013C14) & (0x01U<<3)){
        //PG3
        *(volatile unsigned int*)(0x40013C14) |= 0x01U<<3;
            //interrupt clear
            

        
    }
}