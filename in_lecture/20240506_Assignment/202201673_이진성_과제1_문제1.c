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

unsigned int countIn5sec_Blocking(){
    
    unsigned int count = 0;
    volatile unsigned int delay;
    unsigned int prev = 0;
    unsigned int now = 0;
	for(delay=0;delay<=20 * 3600000;delay++){
        now = (*(volatile unsigned int*)(0x40021810U) >>3) & (0x01U);
        if(!now && prev){
            count++;
            LEDOnOFF(count);
        }
        prev = now;
    }
    return count;
}
//눌렀다가 뗀 횟수이기 때문에
//누른 버튼의 횟수는 뗏을 때를 기준으로 코드를 작성함
//버튼을 눌린 횟수는 LED1~4에 2진수로 나타내도록 작성함

unsigned int countIn5sec_unBlocking_withLED_Blink(){
    unsigned int count = 0;
    volatile unsigned int delay;
    volatile unsigned int delayO;
    unsigned int prev = 0;
    unsigned int now = 0;
    for(delayO = 0;delayO<10;delayO++){  
        LEDOnOFF(count);  
        for(delay=0;delay<=3600000;delay++){
            now = (*(volatile unsigned int*)(0x40021810U) >>3) & (0x01U);
            if(!now && prev){
                count++;
                LEDOnOFF(count);
            }
            prev = now;
        }
        OffAll();
        for(delay=0;delay<=3600000;delay++){
            now = (*(volatile unsigned int*)(0x40021810U) >>3) & (0x01U);
            if(!now && prev)count++;
            prev = now;
        }
    }
    return count;
}
//blinking의 경우 0.5초마다 점멸이 반복
//켜지거나 꺼지는데에는 0.25초 소모되며
//단순 전체 onoff가 아닌 현재 카운트 수만큼
//2진수로 on하도록 만들었음



int main(void){
	hwInit();
    for(int i=1;i<5;i++){userLedInit(i);}
    switch12Init();

    unsigned int count_blocking = 0;

    while(1){
        if(*(volatile unsigned int*)(0x40021810U) & (0x01U<<3)){
            count_blocking = countIn5sec_Blocking();
            break;
        }
    }
    
    for(int i=0;i<5;i++){
        OnAll();
        MyDelay_100ms(1);
        OffAll();
        MyDelay_100ms(1);
    }

    LEDOnOFF(count_blocking);

    MyDelay_100ms(50);
    OffAll();

    unsigned int count_nonblocking_with_ledblink = 0;

    while(1){
        if(*(volatile unsigned int*)(0x40021810U) & (0x01U<<3)){
            count_nonblocking_with_ledblink = countIn5sec_unBlocking_withLED_Blink();
            break;
        }
    }
    
    for(int i=0;i<5;i++){
        OnAll();
        MyDelay_100ms(1);
        OffAll();
        MyDelay_100ms(1);
    }

    LEDOnOFF(count_nonblocking_with_ledblink);

	return 0;
}