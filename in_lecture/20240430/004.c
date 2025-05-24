#if 01

#include "led.h"
#define V_UINT32 volatile unsigned int

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

volatile unsigned int status[2] = {0,0};

int BTN_Check(int No){
    if(No==1){
        if(*(volatile unsigned int*)(0x40021810U) & (0x01U<<3))return 1;
        else return 0;
    }else if(No==2){
        if(*(volatile unsigned int*)(0x40020810U) & (0x01U<<12))return 1;
        else return 0;
    }
}

int prev[2] = {0,0};

int BTN_Check_BNB(int No, int Status){
    int v[2] = {BTN_Check(1),BTN_Check(2)};
    int returnV = 0;

    if(Status==0){
        if(v[No-1] && !prev[No-1])returnV = 1;
        else returnV = 0;
    }else if(Status==1){
        if(!v[No-1] && prev[No-1])returnV = 1;
        else returnV = 0;
    }

    prev[0]=v[0];
    prev[1]=v[1];
    return returnV;
}

int func(){
    for(int i=0;i<5;i++){
        volatile unsigned int delay;
        OnAll();
        for(delay=0;delay<=5 * 3600000;delay++){
            if(BTN_Check(BNB(1,1)))return 1;
        }
        OffAll();
        for(delay=0;delay<=5 * 3600000;delay++){
            if(BTN_Check(BNB(1,1)))return 1;
        }
    }
    return 0;
}

int main(void){
	hwInit();
    for(int i=1;i<3;i++){userLedInit(i);}
    switch12Init();

    int flag=0;

    while(1){
        if(BTN_Check_BNB(1,1) || flag){
            flag=0;
            flag=func();
        }
    }

    

	return 0;
}


#endif