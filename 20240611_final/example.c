#include "led.h"
#define V_UINT32 volatile unsigned int


void userLedInit(unsigned char No){
    if(No==1){
        *(volatile unsigned int*)(0x40023830) |= 0x00000040U;	//RCC

        *(volatile unsigned int*)(0x40021800) |= 0x01U<<24;	//G_MODER		//01
        *(volatile unsigned int*)(0x40021808) |= 0x03U<<24;	//G_OSPEEDR	//11
        *(volatile unsigned int*)(0x4002180C) |= 0x01U<<24;	//G_PUPDR		//01

        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);
    }else if(No==2){
        *(volatile unsigned int*)(0x40023830) |= 0x01U<<4;

        *(volatile unsigned int*)(0x40021000) |= 0x01U<<10;
        *(volatile unsigned int*)(0x40021008) |= 0x03U<<10;
        *(volatile unsigned int*)(0x4002100C) |= 0x01U<<10;

        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
    }else if(No==3){
        *(volatile unsigned int*)(0x40023830) |= 0x01U<<4;

        *(volatile unsigned int*)(0x40021000) |= 0x01U<<8;
        *(volatile unsigned int*)(0x40021008) |= 0x03U<<8;
        *(volatile unsigned int*)(0x4002100C) |= 0x01U<<8;

        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
    }else if(No==4){
        *(volatile unsigned int*)(0x40023830) |= 0x00000040U;	//RCC

        *(volatile unsigned int*)(0x40021800) |= 0x01U<<20;	//G_MODER		//01
        *(volatile unsigned int*)(0x40021808) |= 0x03U<<20;	//G_OSPEEDR	//11
        *(volatile unsigned int*)(0x4002180C) |= 0x01U<<20;	//G_PUPDR		//01

        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);
    }
}

void OnOne(unsigned char No){
    if(No==1){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12+16);
    }else if(No==2){
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5+16);
    }else if(No==3){
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);
    }else if(No==4){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10+16);
    }
}

void OffOne(unsigned char No){
    if(No==1){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);
    }else if(No==2){
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
    }else if(No==3){
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
    }else if(No==4){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);
    }
}

void LEDOnOFF(unsigned int No){
    if(No & 0x01){
        OnOne(1);
    }else{
        OffOne(1);
    }
    if(No & 0x02){
        OnOne(2);
    }else{
        OffOne(2);
    }
    if(No & 0x04){
        OnOne(3);
    }else{
        OffOne(3);
    }
    if(No & 0x08){
        OnOne(4);
    }else{
        OffOne(4);
    }
}

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
            
        LEDOnOFF(3);
        
    }
}

void EXTI3_IRQHandler(){
    if(*(volatile unsigned int*)(0x40013C14) & (0x01U<<3)){
        //PG3
        *(volatile unsigned int*)(0x40013C14) |= 0x01U<<3;
            //interrupt clear
            
        LEDOnOFF(12);
        
    }
}

int main(void){
    hwInit();
    for(int i=1;i<5;i++)userLedInit(i);
    switch12_interrupt_setting();
    
    while(1){
        ;
    }


    return 0;
}