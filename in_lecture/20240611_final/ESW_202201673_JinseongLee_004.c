#include "led.h"
#define V_UINT32 volatile unsigned int

int count[4] = {1,8,5,0};

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
            
        count[2]=((count[2]+5)%10);
        count[1]=count[1]+1;
        if(count[1]==10){
            count[1]=0;
            count[0]=count[0]+1;
        }
        
        
    }
}

void EXTI3_IRQHandler(){
    if(*(volatile unsigned int*)(0x40013C14) & (0x01U<<3)){
        //PG3
        *(volatile unsigned int*)(0x40013C14) |= 0x01U<<3;
            //interrupt clear
            

        count[2]=((count[2]+5)%10);
        count[1]=count[1]+1;
        if(count[1]==10){
            count[1]=0;
            count[0]=count[0]+1;
        }
    }
}
//SEGMENT의 전원을 핀 8,9,10,11에 연결
//값 입력을 4,5,6,7에 함


int main(void){
    hwInit();

    for(int i=4;i<12;i++)setDP(i,1);
    switch12_interrupt_setting();


    volatile unsigned int t=0;
    
    while(1){
        outDP(8,1);
        for(int k=0;k<4;k++)outDP(4+k,(count[0]>>k) & 0x01);
        for(t=0;t<500;t++);
        outDP(8,0);

        outDP(9,1);
        for(int k=0;k<4;k++)outDP(4+k,(count[1]>>k) & 0x01);
        for(t=0;t<500;t++);
        outDP(9,0);

        outDP(10,1);
        for(int k=0;k<4;k++)outDP(4+k,(count[2]>>k) & 0x01);
        for(t=0;t<500;t++);
        outDP(10,0);

        outDP(11,1);
        for(int k=0;k<4;k++)outDP(4+k,(count[3]>>k) & 0x01);
        for(t=0;t<500;t++);
        outDP(11,0);
    }


    return 0;
}