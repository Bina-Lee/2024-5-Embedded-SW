#include "led.h"
#define V_UINT32 volatile unsigned int

unsigned int arr=1250;
unsigned int led=0;
unsigned int state=0;

#define OUT 1
#define IN 0
// ARDD Pin
void setDP(int pin, int mode){
    if(mode){
        switch(pin){
            case 0: //PC7
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;	
                    //RCC Clock enable

                *(volatile unsigned int*)(0x40020800) |= 0x01U<<(7*2);	
                    //C_MODER - general purpose output
                *(volatile unsigned int*)(0x40020808) |= 0x03U<<(7*2);	
                    //C_OSPEEDR	//11 - very high speed
                *(volatile unsigned int*)(0x4002080C) |= 0x01U<<(7*2);	
                    //C_PUPDR - pull up

                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(7);
                    //bit set
                break;
            case 1: //PC6
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;	//RCC

                *(volatile unsigned int*)(0x40020800) |= 0x01U<<(6*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40020808) |= 0x03U<<(6*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002080C) |= 0x01U<<(6*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(6);
                break;
            case 2: //PG6
                *(volatile unsigned int*)(0x40023830) |= 0x00000040U;	//RCC

                *(volatile unsigned int*)(0x40021800) |= 0x01U<<(6*2);	//G_MODER		//01
                *(volatile unsigned int*)(0x40021808) |= 0x03U<<(6*2);	//G_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002180C) |= 0x01U<<(6*2);	//G_PUPDR

                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(6);
                break;
            case 3: //PB4
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<1;	//RCC

                *(volatile unsigned int*)(0x40020400) &= ~(0x03U<<(4*2));
                *(volatile unsigned int*)(0x40020400) |= 0x01U<<(4*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40020408) |= 0x03U<<(4*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002040C) |= 0x01U<<(4*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40020418)  = 0x01U<<(4);
                break;
            case 4: //PG7
                *(volatile unsigned int*)(0x40023830) |= 0x00000040U;	//RCC

                *(volatile unsigned int*)(0x40021800) |= 0x01U<<(7*2);	//G_MODER		//01
                *(volatile unsigned int*)(0x40021808) |= 0x03U<<(7*2);	//G_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002180C) |= 0x01U<<(7*2);	//G_PUPDR

                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(7);
                break;
            case 5: //PA8
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<0;	//RCC

                *(volatile unsigned int*)(0x40020000) |= 0x01U<<(8*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40020008) |= 0x03U<<(8*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002000C) |= 0x01U<<(8*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(8);
                break;
            case 6: //PA2
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<0;	//RCC

                *(volatile unsigned int*)(0x40020000) |= 0x01U<<(2*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40020008) |= 0x03U<<(2*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002000C) |= 0x01U<<(2*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(2);
                break;
            case 7: //PC1
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;	//RCC

                *(volatile unsigned int*)(0x40020800) |= 0x01U<<(1*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40020808) |= 0x03U<<(1*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002080C) |= 0x01U<<(1*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(1);
                break;
            case 8: //PC2
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;	//RCC

                *(volatile unsigned int*)(0x40020800) |= 0x01U<<(2*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40020808) |= 0x03U<<(2*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002080C) |= 0x01U<<(2*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(2);
                break;
            case 9: //PA3
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<0;	//RCC

                *(volatile unsigned int*)(0x40020000) |= 0x01U<<(3*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40020008) |= 0x03U<<(3*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002000C) |= 0x01U<<(3*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(3);
                break;
            case 10: //PB9
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<1;	//RCC

                *(volatile unsigned int*)(0x40020400) |= 0x01U<<(9*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40020408) |= 0x03U<<(9*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002040C) |= 0x01U<<(9*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40020418)  = 0x01U<<(9);
                break;
            case 11: //PB15
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<1;	//RCC

                *(volatile unsigned int*)(0x40020400) |= 0x01U<<(15*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40020408) |= 0x03U<<(15*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002040C) |= 0x01U<<(15*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40020418)  = 0x01U<<(15);
                break;
            case 12: //PB14
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<1;	//RCC

                *(volatile unsigned int*)(0x40020400) |= 0x01U<<(14*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40020408) |= 0x03U<<(14*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002040C) |= 0x01U<<(14*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40020418)  = 0x01U<<(14);
                break;
            case 13: //PA9
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<0;	//RCC

                *(volatile unsigned int*)(0x40020000) |= 0x01U<<(9*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40020008) |= 0x03U<<(9*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002000C) |= 0x01U<<(9*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(9);
                break;
            default:
                break;
        }
    }else{
        switch(pin){
            case 0: //PC7
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;	//RCC

                *(volatile unsigned int*)(0x40020800) &= ~(0x03U<<(7*2));
                *(volatile unsigned int*)(0x40020808) &= ~(0x03U<<(7*2));
                *(volatile unsigned int*)(0x4002080C) &= ~(0x03U<<(7*2));
                break;
            case 1: //PC6
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;	//RCC

                *(volatile unsigned int*)(0x40020800) &= ~(0x03U<<(6*2));
                *(volatile unsigned int*)(0x40020808) &= ~(0x03U<<(6*2));
                *(volatile unsigned int*)(0x4002080C) &= ~(0x03U<<(6*2));
                break;
            case 2: //PG6
                *(volatile unsigned int*)(0x40023830) |= 0x00000040U;	//RCC

                *(volatile unsigned int*)(0x40021800) &= ~(0x03U<<(6*2));
                *(volatile unsigned int*)(0x40021808) &= ~(0x03U<<(6*2));
                *(volatile unsigned int*)(0x4002180C) &= ~(0x03U<<(6*2));
                break;
            case 3: //PB4
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<1;	//RCC

                *(volatile unsigned int*)(0x40020400) &= ~(0x03U<<(4*2));
                *(volatile unsigned int*)(0x40020408) &= ~(0x03U<<(4*2));
                *(volatile unsigned int*)(0x4002040C) &= ~(0x03U<<(4*2));
                break;
            case 4: //PG7
                *(volatile unsigned int*)(0x40023830) |= 0x00000040U;	//RCC

                *(volatile unsigned int*)(0x40021800) &= ~(0x03U<<(7*2));
                *(volatile unsigned int*)(0x40021808) &= ~(0x03U<<(7*2));
                *(volatile unsigned int*)(0x4002180C) &= ~(0x03U<<(7*2));
                break;
            case 5: //PA8
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<0;	//RCC

                *(volatile unsigned int*)(0x40020000) &= ~(0x03U<<(8*2));
                *(volatile unsigned int*)(0x40020008) &= ~(0x03U<<(8*2));
                *(volatile unsigned int*)(0x4002000C) &= ~(0x03U<<(8*2));
                break;
            case 6: //PA2
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<0;	//RCC

                *(volatile unsigned int*)(0x40020000) &= ~(0x03U<<(2*2));
                *(volatile unsigned int*)(0x40020008) &= ~(0x03U<<(2*2));
                *(volatile unsigned int*)(0x4002000C) &= ~(0x03U<<(2*2));
                break;
            case 7: //PC1
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;	//RCC

                *(volatile unsigned int*)(0x40020800) &= ~(0x03U<<(1*2));
                *(volatile unsigned int*)(0x40020808) &= ~(0x03U<<(1*2));
                *(volatile unsigned int*)(0x4002080C) &= ~(0x03U<<(1*2));
                break;
            case 8: //PC2
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;	//RCC

                *(volatile unsigned int*)(0x40020800) &= ~(0x03U<<(2*2));
                *(volatile unsigned int*)(0x40020808) &= ~(0x03U<<(2*2));
                *(volatile unsigned int*)(0x4002080C) &= ~(0x03U<<(2*2));
                break;
            case 9: //PA3
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<0;	//RCC

                *(volatile unsigned int*)(0x40020000) &= ~(0x03U<<(3*2));
                *(volatile unsigned int*)(0x40020008) &= ~(0x03U<<(3*2));
                *(volatile unsigned int*)(0x4002000C) &= ~(0x03U<<(3*2));
                break;
            case 10: //PB9
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<1;	//RCC

                *(volatile unsigned int*)(0x40020400) &= ~(0x03U<<(9*2));
                *(volatile unsigned int*)(0x40020408) &= ~(0x03U<<(9*2));
                *(volatile unsigned int*)(0x4002040C) &= ~(0x03U<<(9*2));
                break;
            case 11: //PB15
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<1;	//RCC

                *(volatile unsigned int*)(0x40020400) &= ~(0x03U<<(15*2));
                *(volatile unsigned int*)(0x40020408) &= ~(0x03U<<(15*2));
                *(volatile unsigned int*)(0x4002040C) &= ~(0x03U<<(15*2));
                break;
            case 12: //PB14
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<1;	//RCC

                *(volatile unsigned int*)(0x40020400) &= ~(0x03U<<(12*2));
                *(volatile unsigned int*)(0x40020408) &= ~(0x03U<<(12*2));
                *(volatile unsigned int*)(0x4002040C) &= ~(0x03U<<(12*2));
                break;
            case 13: //PA9
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<0;	//RCC

                *(volatile unsigned int*)(0x40020000) &= ~(0x03U<<(9*2));
                *(volatile unsigned int*)(0x40020008) &= ~(0x03U<<(9*2));
                *(volatile unsigned int*)(0x4002000C) &= ~(0x03U<<(9*2));
                break;
            default:
                break;
        }
    }
}

void outDP(int pin, int v){
    if(v){
        switch(pin){
            case 0:
                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(7);
                break;
            case 1:
                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(6);
                break;
            case 2:
                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(6);
                break;
            case 3:
                *(volatile unsigned int*)(0x40020418)  = 0x01U<<(4);
                break;
            case 4:
                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(7);
                break;
            case 5:
                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(8);
                break;
            case 6:
                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(2);
                break;
            case 7:
                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(1);
                break;
            case 8:
                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(2);
                break;
            case 9:
                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(3);
                break;
            case 10:
                *(volatile unsigned int*)(0x40020418)  = 0x01U<<(9);
                break;
            case 11:
                *(volatile unsigned int*)(0x40020418)  = 0x01U<<(15);
                break;
            case 12:
                *(volatile unsigned int*)(0x40020418)  = 0x01U<<(14);
                break;
            case 13:
                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(9);
                break;
            default:
                break;
        }
    }else{
        switch(pin){
            case 0:
                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(7+16);
                break;
            case 1:
                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(6+16);
                break;
            case 2:
                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(6+16);
                break;
            case 3:
                *(volatile unsigned int*)(0x40020418)  = 0x01U<<(4+16);
                break;
            case 4:
                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(7+16);
                break;
            case 5:
                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(8+16);
                break;
            case 6:
                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(2+16);
                break;
            case 7:
                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(1+16);
                break;
            case 8:
                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(2+16);
                break;
            case 9:
                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(3+16);
                break;
            case 10:
                *(volatile unsigned int*)(0x40020418)  = 0x01U<<(9+16);
                break;
            case 11:
                *(volatile unsigned int*)(0x40020418)  = 0x01U<<(15+16);
                break;
            case 12:
                *(volatile unsigned int*)(0x40020418)  = 0x01U<<(14+16);
                break;
            case 13:
                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(9+16);
                break;
            default:
                break;
        }
    }
}

int inDP(int pin){
    int returnV = 0;
    switch(pin){
        case 0:
            returnV = (*(volatile unsigned int*)(0x40020810U) >>7) & (0x01U);
            break;
        case 1:
            returnV = (*(volatile unsigned int*)(0x40020810U) >>6) & (0x01U);
            break;
        case 2:
            returnV = (*(volatile unsigned int*)(0x40021810U) >>6) & (0x01U);
            break;
        case 3:
            returnV = (*(volatile unsigned int*)(0x40020410U) >>4) & (0x01U);
            break;
        case 4:
            returnV = (*(volatile unsigned int*)(0x40021810U) >>7) & (0x01U);
            break;
        case 5:
            returnV = (*(volatile unsigned int*)(0x40020010U) >>8) & (0x01U);
            break;
        case 6:
            returnV = (*(volatile unsigned int*)(0x40020010U) >>2) & (0x01U);
            break;
        case 7:
            returnV = (*(volatile unsigned int*)(0x40020810U) >>1) & (0x01U);
            break;
        case 8:
            returnV = (*(volatile unsigned int*)(0x40020810U) >>2) & (0x01U);
            break;
        case 9:
            returnV = (*(volatile unsigned int*)(0x40020010U) >>3) & (0x01U);
            break;
        case 10:
            returnV = (*(volatile unsigned int*)(0x40020410U) >>9) & (0x01U);
            break;
        case 11:
            returnV = (*(volatile unsigned int*)(0x40020410U) >>15) & (0x01U);
            break;
        case 12:
            returnV = (*(volatile unsigned int*)(0x40020410U) >>14) & (0x01U);
            break;
        case 13:
            returnV = (*(volatile unsigned int*)(0x40020010U) >>9) & (0x01U);
            break;
        default:
            break;
    }
    return returnV;
}
//----------------------------------------------------------------


void switch12_interrupt_setting(){
    //switch2 PC12
    *(volatile unsigned int*)(0x40023830U) |= 0x00000004U;      //RCC
    *(volatile unsigned int*)(0x40020800U) &= ~(0x03U<<(12*2));   //GPIOC-12
    *(volatile unsigned int*)(0x4002080CU) &= ~(0x03U<<(12*2));

    *(volatile unsigned int*)(0x40023844) |= 0x01U<<14;
    *(volatile unsigned int*)(0x40013814) |= 0x02U<<((12%4) * 4);
    *(volatile unsigned int*)(0x40013C00) |= 0x01U<<12;  //EXTI_IMR - IM12
    // *(volatile unsigned int*)(0x40013C08) |= 0x01U<<12; //EXTI_RTSR - TR12  //rising edge
    *(volatile unsigned int*)(0x40013C0C) |= 0x01U<<12; //EXTI_RTSR - TR12  //falling edge

    *(volatile unsigned int*)(0xE000E104) |= 0x01<<8;

    //switch1  PG3 
    *(volatile unsigned int*)(0x40023830U) |= 0x00000040U;      //RCC
    *(volatile unsigned int*)(0x40021800U) &= ~(0x03U<<(3*2));   //GPIOG-3
    *(volatile unsigned int*)(0x4002180CU) &= ~(0x03U<<(3*2));

    *(volatile unsigned int*)(0x40023844) |= 0x01U<<14; //RCC_APB2ENR - SYSSCFEN
    *(volatile unsigned int*)(0x40013808) |= 0x06U<<((3%4) * 4);//SYSCFG_EXTICR1 - EXTI3 - PG3
    *(volatile unsigned int*)(0x40013C00) |= 0x01U<<3;  //EXTI_IMR - IM3
    // *(volatile unsigned int*)(0x40013C08) |= 0x01U<<3;  //EXTI_RTSR - TR3   //rising edge trigger
    *(volatile unsigned int*)(0x40013C0C) |= 0x01U<<3;  //EXTI_RTSR - TR3   //falling edge trigger

    *(volatile unsigned int*)(0xE000E100) |= 0x01<<9;  
        //NVIC  //Position-9-EXTI9_3
}

void EXTI15_10_IRQHandler(){
if(*(volatile unsigned int*)(0x40013C14) & (0x01U<<12)){
        //PC12
        *(volatile unsigned int*)(0x40013C14) |= 0x01U<<12;
            //interrupt clear
            
        if(state==1){
            state=2;
            arr = 2500;

            *(volatile unsigned int*)(0x4000002C) = arr - 1;   //TIM2_ARR
            *(volatile unsigned int*)(0x40000024) = 0;  //TIM2_CNT
            *(volatile unsigned int*)(0x40014024) = 0;  //TIM9_CNT
            
            *(volatile unsigned int*)(0x40000000) |= 0x01U<<0;  //TIM2_CR1-CEN
            *(volatile unsigned int*)(0x40014000) |= 0x01U<<0;
        }
        if(state==0){
            state=1;
            *(volatile unsigned int*)(0x40000000) &= ~(0x01U<<0);  //TIM2_CR1-CEN
            *(volatile unsigned int*)(0x40014000) &= ~(0x01U<<0);
        }
        
    }
}

void EXTI3_IRQHandler(){
    if(*(volatile unsigned int*)(0x40013C14) & (0x01U<<3)){
        //PG3
        *(volatile unsigned int*)(0x40013C14) |= 0x01U<<3;
            //interrupt clear
            

        if(state==1){
            state=2;
            arr = 2500;

            *(volatile unsigned int*)(0x4000002C) = arr - 1;   //TIM2_ARR
            *(volatile unsigned int*)(0x40000024) = 0;  //TIM2_CNT
            *(volatile unsigned int*)(0x40014024) = 0;  //TIM9_CNT
            
            *(volatile unsigned int*)(0x40000000) |= 0x01U<<0;  //TIM2_CR1-CEN
            *(volatile unsigned int*)(0x40014000) |= 0x01U<<0;
        }
        if(state==0){
            state=1;
            *(volatile unsigned int*)(0x40000000) &= ~(0x01U<<0);  //TIM2_CR1-CEN
            *(volatile unsigned int*)(0x40014000) &= ~(0x01U<<0);
        }
    }
}

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
    *(volatile unsigned int*)(0x40000028) = 21599 - 1;   //TIM2_PSC
    *(volatile unsigned int*)(0x4000002C) = arr - 1;   //TIM2_ARR
    *(volatile unsigned int*)(0x4000000C) |= 0x01U<<0;  //TIM2_DIER-UIE
    *(volatile unsigned int*)(0x40000010) &= ~(0x01U<<0);   //TIM2_SR-UIF

    *(volatile unsigned int*)(0xE000E100) |= 0x01U<<28; //NVIC -> 28
}

void TIM2_IRQHandler(){
    if(*(volatile unsigned int*)(0x40000010) & (0x01U)){
        *(volatile unsigned int*)(0x40000010) &= ~(0x01U);   //TIM2_SR-UIF

        led^=1;
        
        outDP(1,led);
        outDP(2,led);
        outDP(3,led);
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

void timer9_setting(){
    *(volatile unsigned int*)(0x40023844) |= 0x01U<<16; //timer9 enable

    *(volatile unsigned int*)(0x40014000) |= 0x01U<<0;
    *(volatile unsigned int*)(0x40014028) = 21599;
    *(volatile unsigned int*)(0x4001402C) = 50000-1;
    *(volatile unsigned int*)(0x4001400C) |= 0x01U<<0;
    *(volatile unsigned int*)(0x40014010) &= ~(0x01U<<0);

    *(volatile unsigned int*)(0xE000E100) |= 0x01U<<24; //NVIC -> 24
}


void TIM1_BRK_TIM9_IRQHandler(){
    if(*(volatile unsigned int*)(0x40014010) & 0x01U){
        *(volatile unsigned int*)(0x40014010) &= ~(0x01U);
        
        arr = arr <<1;
        *(volatile unsigned int*)(0x4000002C) = arr - 1;   //TIM2_ARR
    }
}


//tim2는 깜빡임 주기
//tim9은 5초마다 tim2의 주기를 두배로 늘림
//각 스위치의 인터럽트는
//state가 0일때는 그냥 동작
//stste가 1이 되면 타이머를 멈추고
//main문에서는 led를 켬
//state가 1인 상태에서 한번 더 들어오면
//arr값을 수정하고 타이머를 다시 실행함
//state가 2가 되는데
//main문에서 다시 0으로 만들어서 반복하도록 함
int main(void){
    hwInit();
    switch12_interrupt_setting();
    setDP(1,OUT);
    setDP(2,OUT);
    setDP(3,OUT);

    TIM2_setting();
    timer9_setting();

    while(1){
        if(state==1){
            outDP(1,0);
            outDP(2,0);
            outDP(3,0);
        }
        if(state==2)state=0;
    }


    return 0;
}