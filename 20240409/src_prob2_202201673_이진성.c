#include "led.h"
#define V_UINT32 volatile unsigned int

void MyDelay(unsigned int n){
	volatile unsigned int delay;
	for(delay=0;delay<=n * 36000000;delay++);            
}

void Init(){
    *(volatile unsigned int*)(0x40023830) |= 0x00000040U;	//RCC

    *(volatile unsigned int*)(0x40021800) |= 0x01U<<24;	//G_MODER		//01
    *(volatile unsigned int*)(0x40021808) |= 0x03U<<24;	//G_OSPEEDR	//11
    *(volatile unsigned int*)(0x4002180C) |= 0x01U<<24;	//G_PUPDR		//01

    *(volatile unsigned int*)(0x40021800) |= 0x01U<<20;	//G_MODER		//01
    *(volatile unsigned int*)(0x40021808) |= 0x03U<<20;	//G_OSPEEDR	//11
    *(volatile unsigned int*)(0x4002180C) |= 0x01U<<20;	//G_PUPDR		//01

    *(volatile unsigned int*)(0x40023830) |= 0x01U<<4;

    *(volatile unsigned int*)(0x40021000) |= 0x01U<<10;
    *(volatile unsigned int*)(0x40021008) |= 0x03U<<10;
    *(volatile unsigned int*)(0x4002100C) |= 0x01U<<10;

    *(volatile unsigned int*)(0x40021000) |= 0x01U<<8;
    *(volatile unsigned int*)(0x40021008) |= 0x03U<<8;
    *(volatile unsigned int*)(0x4002100C) |= 0x01U<<8;
}

void TurnOffOneLED(unsigned char No){
    Init();
    if(No==1){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);	//G_BSRR		//
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5+16);
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10+16);	//G_BSRR		//
    }else if(No==2){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12+16);	//G_BSRR		//
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10+16);	//G_BSRR		//
    }else if(No==3){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12+16);	//G_BSRR		//
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5+16);
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10+16);	//G_BSRR		//
    }else if(No==4){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12+16);	//G_BSRR		//
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5+16);
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);	//G_BSRR		//
    }
}

int main(void){
	hwInit();

	TurnOffOneLED(1);
	MyDelay(1);
	TurnOffOneLED(2);
	MyDelay(1);
	TurnOffOneLED(3);
	MyDelay(1);
	TurnOffOneLED(4);
	MyDelay(1);

	return 0;
}