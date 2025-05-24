#include "led.h"
#define V_UINT32 volatile unsigned int
void MyDelay_100ms(unsigned int n){
	volatile unsigned int delay;
	for(delay=0;delay<=n * 3600000;delay++);
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

void OffAll(){
    *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);
    *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
    *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
    *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);
}

int main(void){
	hwInit();
    for(int i=1;i<5;i++){userLedInit(i);}
    while(1){
        
        for(unsigned int i=1;i<16;i++){
            LEDOnOFF(i);
            MyDelay_100ms(8);
            OffAll();
            MyDelay_100ms(2);
        }
    }
	return 0;
}