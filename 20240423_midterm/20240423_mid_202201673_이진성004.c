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

void JustOneLED(unsigned int LED1, unsigned int LED2, unsigned int LED3, unsigned int LED4){
    unsigned int count[4] = {0,0,0,0};
    for(int i=0;i<32;i++)if((LED1>>i) & 0x01)count[0]++;
    for(int i=0;i<32;i++)if((LED2>>i) & 0x01)count[1]++;
    for(int i=0;i<32;i++)if((LED3>>i) & 0x01)count[2]++;
    for(int i=0;i<32;i++)if((LED4>>i) & 0x01)count[3]++;

    unsigned int maxV = count[0];
    unsigned int maxI = 0;

    for(int i=1;i<4;i++){
        if(maxV<count[i]){
            maxV = count[i];
            maxI = i;
        }
    }
    for(int i=0;i<4;i++){
        if(count[i]==maxV){
            OnOne(i+1);
        }else{
            OffOne(i+1);
        }
    }
}

MyApp(){
    JustOneLED(1,3,7,15);
    MyDelay_100ms(10);
    JustOneLED(7,15,7,15);
    MyDelay_100ms(10);
}

int main(void){
	hwInit();
    for(int i=1;i<5;i++){userLedInit(i);}

    MyApp();

	return 0;
}