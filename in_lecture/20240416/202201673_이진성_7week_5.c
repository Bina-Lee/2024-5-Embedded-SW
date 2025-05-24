#include "led.h"
#define V_UINT32 volatile unsigned int

void MyDelay10(unsigned int n){
	volatile unsigned int delay;
	for(delay=0;delay<=n * 3600000;delay++);
}

void MyDelay_div(unsigned int n){
	volatile unsigned int delay;
	for(delay=0;delay<=36000000/n;delay++);
}

void MyDelay(unsigned int n){
	volatile unsigned int delay;
	for(delay=0;delay<=n * 36000000;delay++);
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

void ledBlink(unsigned char Number){
    unsigned char mask[4]={
        (Number>>6),
        (Number>>4) & 0x03,
        (Number>>2) & 0x03,
        (Number) & 0x03
    };
    for(int i=0;i<4;i++){
        if(mask[i]==0){
            *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12 + 16);
            MyDelay10(1);
            *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);
        }else if(mask[i]==1){
            *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5 + 16);
            MyDelay10(1);
            *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
        }else if(mask[i]==2){
            *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);
            MyDelay10(1);
            *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
        }else if(mask[i]==3){
            *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10 + 16);
            MyDelay10(1);
            *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);
        }
    }
}

int main(void){
	hwInit();
    for(int i=0;i<5;i++){userLedInit(i);}

    while(1){
        ledBlink(73);
        //0b01001001
    }

	return 0;
}