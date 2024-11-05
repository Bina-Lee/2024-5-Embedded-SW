#if 01

#include "led.h"
#define V_UINT32 volatile unsigned int

void MyDelay_100ms(unsigned int n){
	volatile unsigned int delay;
	for(delay=0;delay<=n * 3600000;delay++);
}

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

void switch12Init(){
    //switch2
    *(volatile unsigned int*)(0x40023830U) |= 0x00000004U;      //RCC
    *(volatile unsigned int*)(0x40020800U) &= ~(0x03U<<(12*2));   //GPIOC-12
    *(volatile unsigned int*)(0x40020808U) &= ~(0x03U<<(12*2));
    *(volatile unsigned int*)(0x4002080CU) &= ~(0x03U<<(12*2));

    //switch1
    *(volatile unsigned int*)(0x40023830U) |= 0x00000040U;      //RCC
    *(volatile unsigned int*)(0x40021800U) &= ~(0x03U<<(3*2));   //GPIOG-3
    *(volatile unsigned int*)(0x40021808U) &= ~(0x03U<<(3*2));
    *(volatile unsigned int*)(0x4002180CU) &= ~(0x03U<<(3*2));
}

void OnAll(){
    *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12+16);
    *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5+16);
    *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);
    *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10+16);
}

void OffAll(){
    *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);
    *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
    *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
    *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);
}

int BTN_Check(int No){
    if(No==1){
        if(*(volatile unsigned int*)(0x40021810U) & (0x01U<<3))return 1;
        else return 0;
    }else if(No==2){
        if(*(volatile unsigned int*)(0x40020810U) & (0x01U<<12))return 1;
        else return 0;
    }
}

int main(void){
	hwInit();
    for(int i=1;i<5;i++){userLedInit(i);}
    switch12Init();

    while(1){
        if(BTN_Check(1)){
            for(int i=0;i<5;i++){
                OnAll();
                MyDelay_100ms(5);
                OffAll();
                MyDelay_100ms(5);
            }
        }
    }

	return 0;
}


#endif