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

void TurnOnOneLED(unsigned char No){
    if(No==1){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12+16);	//G_BSRR		//
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);	//G_BSRR		//
    }else if(No==2){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);	//G_BSRR		//
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5+16);
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);	//G_BSRR		//
    }else if(No==3){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);	//G_BSRR		//
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);	//G_BSRR		//
    }else if(No==0 || No==4){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);	//G_BSRR		//
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10+16);	//G_BSRR		//
    }
}

void oneCycle(unsigned char No){
	if(No==1){
		TurnOnOneLED(1);
		MyDelay(1);
		TurnOnOneLED(2);
		MyDelay(1);
		TurnOnOneLED(3);
		MyDelay(1);
		TurnOnOneLED(4);
		MyDelay(1);
	}else if(No==2){
		TurnOnOneLED(2);
		MyDelay(1);
		TurnOnOneLED(3);
		MyDelay(1);
		TurnOnOneLED(4);
		MyDelay(1);
		TurnOnOneLED(1);
		MyDelay(1);
	}else if(No==3){
		TurnOnOneLED(3);
		MyDelay(1);
		TurnOnOneLED(4);
		MyDelay(1);
		TurnOnOneLED(1);
		MyDelay(1);
		TurnOnOneLED(2);
		MyDelay(1);
	}else if(No==4){
		TurnOnOneLED(4);
		MyDelay(1);
		TurnOnOneLED(1);
		MyDelay(1);
		TurnOnOneLED(2);
		MyDelay(1);
		TurnOnOneLED(3);
		MyDelay(1);
	}
}

void CycleLED(unsigned char No, unsigned char Cnt){
			Init();
			volatile unsigned int i;
			for(i=1;i<=Cnt;i++){
				oneCycle(No);
			}
}

int main(void){
	hwInit();

  CycleLED(2,2);

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

void TurnOnOneLED(unsigned char No){
    if(No==1){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12+16);	//G_BSRR		//
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);	//G_BSRR		//
    }else if(No==2){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);	//G_BSRR		//
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5+16);
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);	//G_BSRR		//
    }else if(No==3){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);	//G_BSRR		//
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);	//G_BSRR		//
    }else if(No==0 || No==4){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);	//G_BSRR		//
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10+16);	//G_BSRR		//
    }
}

void CycleLED(unsigned char No, unsigned char Cnt){
	Init();
	volatile unsigned int i;
	for(i=1;i<=Cnt;i++){
		TurnOnOneLED(No);
		MyDelay(1);
		TurnOnOneLED((No+1)%4);
		MyDelay(1);
		TurnOnOneLED((No+2)%4);
		MyDelay(1);
		TurnOnOneLED((No+3)%4);
		MyDelay(1);
	}
}

int main(void){
	hwInit();

  	CycleLED(2,2);

	return 0;
}

#endif