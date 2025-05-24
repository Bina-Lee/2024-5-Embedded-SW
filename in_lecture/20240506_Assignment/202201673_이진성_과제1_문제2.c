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

unsigned int timing_push[100];
unsigned int timing_pull[100];
//임의로 100칸 배열 생성
//눌리는 순간이나 떼는 순간의 타이밍을 저장함

void remaining_pattern(unsigned int sec, unsigned int but){
    volatile unsigned int delay;
    volatile unsigned int se;
    
    unsigned int prev = 0;
    unsigned int now = 0;
    
    unsigned int push_count = 0;
    unsigned int pull_count = 0;
    for(delay=0;delay<=sec * 3600000;delay++){
        for(se = 0;se<2;se++){
            if(but==1){
                now = (*(volatile unsigned int*)(0x40021810U) >>3) & (0x01U);
            }else if(but==2){
                now = (*(volatile unsigned int*)(0x40020810U) >>12) & (0x01U);
            }

            if(!now && prev){
                timing_pull[pull_count] = delay;
                OffAll();
                pull_count++;
            }else if(now && !prev){
                timing_push[push_count] = delay;
                OnAll();
                push_count++;
            }
            prev = now;
        }
    }
}

void call_pattern(unsigned int sec){
    volatile unsigned int delay;
    volatile unsigned int se;
    OnAll();
    unsigned int push_count = 0;
    unsigned int pull_count = 0;
    for(delay=0;delay<=sec * 3600000;delay++){
        for(se = 0;se<=3;se++){
            if(timing_push[push_count]==delay){
                OnAll();
                push_count++;
            }
            if(timing_pull[pull_count]==delay){
                OffAll();
                pull_count++;
            }
        }
    }
}

int main(void){
	hwInit();
    for(int i=1;i<5;i++){userLedInit(i);}
    switch12Init();

    unsigned int N = 5;
    unsigned int X = 2;

    while(1){
        if(X==1){
            if(*(volatile unsigned int*)(0x40021810U) & (0x01U<<3)){
                remaining_pattern(N, X);
                break;
            }
        }else if(X==2){
            if(*(volatile unsigned int*)(0x40020810U) & (0x01U<<12)){
                remaining_pattern(N, X);
                break;
            }
        }
        
    }
    
    OnAll();
    MyDelay_100ms(9);
    OffAll();
    MyDelay_100ms(1);
    //패턴입력 끝났음을 표기
    
    call_pattern(N);

    OnAll();
    MyDelay_100ms(10);
    OffAll();
    //패턴출력 끝났음을 표기
    

	return 0;
}