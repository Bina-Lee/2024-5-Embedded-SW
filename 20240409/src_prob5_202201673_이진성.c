#if 0

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

void cycle13(){
    while(1){
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);	//G_BSRR		//

        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12+16);	//G_BSRR		//
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);

        MyDelay(1);

        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);	//G_BSRR		//
        
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12+16);	//G_BSRR		//
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);

        MyDelay(1);

        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);	//G_BSRR		//
        
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);	//G_BSRR		//
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);

        MyDelay(1);

        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);	//G_BSRR		//
        
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);	//G_BSRR		//
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);

        MyDelay(1);
    }
}

void cycle24(){
    while(1){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);	//G_BSRR		//
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
        
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5+16);
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);	//G_BSRR		//

        MyDelay(1);

        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);	//G_BSRR		//
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
        
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5+16);
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10+16);	//G_BSRR		//

        MyDelay(1);

        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);	//G_BSRR		//
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
        
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10+16);	//G_BSRR		//

        MyDelay(1);

        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);	//G_BSRR		//
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
        
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);	//G_BSRR		//

        MyDelay(1);
    }   
}

void snifflingLED(unsigned char No){
    Init();
    if(No%2==1){
        cycle13();
    }else{
        cycle24();
    }
}

int main(void){
	hwInit();

    snifflingLED(13);

	return 0;
}

#endif

#if 01

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

void snifflingLED(unsigned char No){
    Init();		//
    *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);	//G_BSRR
    *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);		//
    *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
    *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);	//G_BSRR
    
    if(No%2==1){
        while(1){
            *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12+16);	//G_BSRR
            MyDelay(1);
            *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);
            MyDelay(1);
            *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);	//G_BSRR		//
            MyDelay(1);
            *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
            MyDelay(1);
        }
    }else{
        while(1){
            *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5+16);
            MyDelay(1);
            *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10+16);	//G_BSRR
            MyDelay(1);
            *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
            MyDelay(1);
            *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);	//G_BSRR
            MyDelay(1);
        }   
    }
}

int main(void){
	hwInit();

    snifflingLED(13);

	return 0;
}

#endif

