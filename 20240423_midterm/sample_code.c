#include "led.h"
#define V_UINT32 volatile unsigned int

void MyDelay_100ms(unsigned int n){
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

void Init(){
    *(volatile unsigned int*)(0x40023830) |= 0x00000040U;

    *(volatile unsigned int*)(0x40021800) |= 0x01U<<24;
    *(volatile unsigned int*)(0x40021808) |= 0x03U<<24;
    *(volatile unsigned int*)(0x4002180C) |= 0x01U<<24;

    *(volatile unsigned int*)(0x40021800) |= 0x01U<<20;
    *(volatile unsigned int*)(0x40021808) |= 0x03U<<20;
    *(volatile unsigned int*)(0x4002180C) |= 0x01U<<20;

    *(volatile unsigned int*)(0x40023830) |= 0x01U<<4;

    *(volatile unsigned int*)(0x40021000) |= 0x01U<<10;
    *(volatile unsigned int*)(0x40021008) |= 0x03U<<10;
    *(volatile unsigned int*)(0x4002100C) |= 0x01U<<10;

    *(volatile unsigned int*)(0x40021000) |= 0x01U<<8;
    *(volatile unsigned int*)(0x40021008) |= 0x03U<<8;
    *(volatile unsigned int*)(0x4002100C) |= 0x01U<<8;
    //All LED OFF(set)
    *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);
    *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
    *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
    *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);
}

void userLedInit(unsigned char No){
    if(No==1){
        *(volatile unsigned int*)(0x40023830) |= 0x00000040U;

        *(volatile unsigned int*)(0x40021800) |= 0x01U<<24;
        *(volatile unsigned int*)(0x40021808) |= 0x03U<<24;
        *(volatile unsigned int*)(0x4002180C) |= 0x01U<<24;

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
        *(volatile unsigned int*)(0x40023830) |= 0x00000040U;

        *(volatile unsigned int*)(0x40021800) |= 0x01U<<20;
        *(volatile unsigned int*)(0x40021808) |= 0x03U<<20;
        *(volatile unsigned int*)(0x4002180C) |= 0x01U<<20;

        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);
    }
}

void OnOne(unsigned char No){
    Init();
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
    Init();
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




int main(void){
	hwInit();
    for(int i=1;i<5;i++){userLedInit(i);}


	return 0;
}