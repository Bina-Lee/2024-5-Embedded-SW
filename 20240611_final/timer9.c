void timer9_setting(){
    *(volatile unsigned int*)(0x40023844) |= 0x01U<<16; //timer9 enable

    *(volatile unsigned int*)(0x40014000) |= 0x01U<<0;
    *(volatile unsigned int*)(0x40014028) = 21599;
    *(volatile unsigned int*)(0x4001402C) = 9999;
    *(volatile unsigned int*)(0x4001400C) |= 0x01U<<0;
    *(volatile unsigned int*)(0x40014010) &= ~(0x01U<<0);

    *(volatile unsigned int*)(0xE000E100) |= 0x01U<<24; //NVIC -> 24
}






void TIM1_BRK_TIM9_IRQHandler(){
    if(*(volatile unsigned int*)(0x40014010) & 0x01U){
        *(volatile unsigned int*)(0x40014010) &= ~(0x01U);
        

    }
}