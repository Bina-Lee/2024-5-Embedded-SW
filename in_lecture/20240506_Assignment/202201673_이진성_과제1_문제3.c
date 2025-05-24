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

int data[11] = {2,6,8,5,10,
                2,15,6,13,11,6};
                //nnnyyyyyny
                //6개 + 4개
int input[10];
int answer[10];

int abs_minus(int a, int b){
    if(a>b)return a-b;
    return b-a;
}
int small_or_equal(int a){
    if(a<=5)return 1;
    return 2;
}

int main(void){
	hwInit();
    for(int i=1;i<5;i++){userLedInit(i);}
    switch12Init();

    LEDOnOFF(data[0]);
    int count_correct = 0;

    MyDelay_100ms(5);
    for(int i=1;i<11;i++){
        LEDOnOFF(data[i]);
        volatile unsigned int delay;
	    for(delay=0;delay<=2 * 3600000;delay++){
            if(*(volatile unsigned int*)(0x40021810U) & (0x01U<<3)){
                input[i-1] = 1;
            }

            if(*(volatile unsigned int*)(0x40020810U) & (0x01U<<12)){
                input[i-1] = 2;
            }
            //입력이 없는 경우는 0으로 그대로 두며
            //이 경우는 무조건 오답이 되도록 처리하였음
        }
        int minus = abs_minus(data[i-1], data[i]);
        answer[i-1] = small_or_equal(minus);
        if(answer[i-1] == input[i-1])count_correct++;
    }

    for(int i=0;i<count_correct;i++){
        OffAll();
        MyDelay_100ms(5);
        OnAll();
        MyDelay_100ms(5);
    }

    LEDOnOFF(count_correct);
    //끝나고 led 4개에 대해 이진수로 정답 갯수 출력하도록 함
    

	return 0;
}