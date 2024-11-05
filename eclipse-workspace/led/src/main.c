#include "led.h"
#define V_UINT32 volatile unsigned int

void MyDelay_100ms(unsigned int n){
	volatile unsigned int delay;
	for(delay=0;delay<=n * 3600000;delay++);
}

//Newton-Raphson
unsigned int int_sqrt(unsigned long long n) {
    unsigned long long x = n;
    unsigned long long y = (x + 1)>>1;

    while (y < x) {
    // for(int i=0;i<20 && y<x;i++){
        x = y;
        y = (x + n / x)>>1;
    }

    return (unsigned int)x;
}//sqrt 값을 구하기 위한 함수

int count[3] = {0,0,0};
    //최초 스위치 입력에 대해 홀에 들어가는 구슬 숫자 카운트
int count_rt[3] = {0,0,0};
    //작동 중 홀에 들어간 구슬 수
int order[20] = {0,};
    //n번째 구슬이 빠져야 할 홀 저장
    //값은 1,2,3 중 하나
int order_num = 0;
    //order에 값 넣을때 인덱스로 사용

int sensor1_count = 0;
int sensor2_count = 0;
int actuator1_count = 0;
int actuator2_count = 0;
    //각 센서와 액추에이터를 지난 구슬의 인덱스

unsigned long long t0 = 0;
    //첫 번째 구슬이 센서 두 개를 거치는 시간
unsigned long long t0t0 = 0;
    //의 제곱
unsigned long long t0p5 = 0;
    //의 다섯 배
unsigned long long t0p7 = 0;
    //t0t0의 7배

// unsigned int td1[20] = {0,};
unsigned int td2[20] = {0,};
unsigned int td3[20] = {0,};
unsigned int td4[20] = {0,};
    //n번째 구슬이 Sensor2, Actuator1, Actuator2에 도달하는 시간 CNT값

// unsigned int calculate_td3(unsigned int td2){
//     unsigned int returnV;
//     returnV = int_sqrt((long long)((long long)td2*(long long)td2 + t0p5));
//     return returnV;
// }
//
// unsigned int calculate_td4(unsigned int td3){
//     unsigned int returnV;
//     returnV = int_sqrt((long long)((long long)td3*(long long)td3 + t0p7));
//     return returnV;
// }   //td2를 베이스로 td3와 td4를 구하는 함수
//     //실제로 사용되진 않음 inline으로 코드 내에서 구현

#define OUT 1
#define IN 0
//----------------------------------------------------------------
// ARDD Pin
void setDP(int pin, int mode){
    if(mode){
        switch(pin){
            case 0: //PC7
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;
                    //RCC Clock enable

                *(volatile unsigned int*)(0x40020800) |= 0x01U<<(7*2);
                    //C_MODER - general purpose output
                *(volatile unsigned int*)(0x40020808) |= 0x03U<<(7*2);
                    //C_OSPEEDR	//11 - very high speed
                *(volatile unsigned int*)(0x4002080C) |= 0x01U<<(7*2);
                    //C_PUPDR - pull up

                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(7);
                    //bit set
                break;
            case 1: //PC6
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;	//RCC

                *(volatile unsigned int*)(0x40020800) |= 0x01U<<(6*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40020808) |= 0x03U<<(6*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002080C) |= 0x01U<<(6*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(6);
                break;
            case 2: //PG6
                *(volatile unsigned int*)(0x40023830) |= 0x00000040U;	//RCC

                *(volatile unsigned int*)(0x40021800) |= 0x01U<<(6*2);	//G_MODER		//01
                *(volatile unsigned int*)(0x40021808) |= 0x03U<<(6*2);	//G_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002180C) |= 0x01U<<(6*2);	//G_PUPDR

                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(6);
                break;
            case 3: //PB4
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<1;	//RCC

                *(volatile unsigned int*)(0x40020400) |= 0x01U<<(4*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40020408) |= 0x03U<<(4*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002040C) |= 0x01U<<(4*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40020418)  = 0x01U<<(4);
                break;
            case 4: //PG7
                *(volatile unsigned int*)(0x40023830) |= 0x00000040U;	//RCC

                *(volatile unsigned int*)(0x40021800) |= 0x01U<<(7*2);	//G_MODER		//01
                *(volatile unsigned int*)(0x40021808) |= 0x03U<<(7*2);	//G_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002180C) |= 0x01U<<(7*2);	//G_PUPDR

                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(7);
                break;
            case 5: //PA8
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<0;	//RCC

                *(volatile unsigned int*)(0x40020000) |= 0x01U<<(8*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40020008) |= 0x03U<<(8*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002000C) |= 0x01U<<(8*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(8);
                break;
            case 6: //PA2
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<0;	//RCC

                *(volatile unsigned int*)(0x40020000) |= 0x01U<<(2*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40020008) |= 0x03U<<(2*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002000C) |= 0x01U<<(2*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(2);
                break;
            case 7: //PC1
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;	//RCC

                *(volatile unsigned int*)(0x40020800) |= 0x01U<<(1*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40020808) |= 0x03U<<(1*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002080C) |= 0x01U<<(1*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(1);
                break;
            case 8: //PC2
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;	//RCC

                *(volatile unsigned int*)(0x40020800) |= 0x01U<<(2*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40020808) |= 0x03U<<(2*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002080C) |= 0x01U<<(2*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(2);
                break;
            case 9: //PA3
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<0;	//RCC

                *(volatile unsigned int*)(0x40020000) |= 0x01U<<(3*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40020008) |= 0x03U<<(3*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002000C) |= 0x01U<<(3*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(3);
                break;
            case 10: //PB9
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<1;	//RCC

                *(volatile unsigned int*)(0x40020400) |= 0x01U<<(9*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40020408) |= 0x03U<<(9*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002040C) |= 0x01U<<(9*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40020418)  = 0x01U<<(9);
                break;
            case 11: //PB15
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<1;	//RCC

                *(volatile unsigned int*)(0x40020400) |= 0x01U<<(15*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40020408) |= 0x03U<<(15*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002040C) |= 0x01U<<(15*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40020418)  = 0x01U<<(15);
                break;
            case 12: //PB14
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<1;	//RCC

                *(volatile unsigned int*)(0x40020400) |= 0x01U<<(14*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40020408) |= 0x03U<<(14*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002040C) |= 0x01U<<(14*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40020418)  = 0x01U<<(14);
                break;
            case 13: //PA9
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<0;	//RCC

                *(volatile unsigned int*)(0x40020000) |= 0x01U<<(9*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40020008) |= 0x03U<<(9*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002000C) |= 0x01U<<(9*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(9);
                break;
            default:
                break;
        }
    }else{
        switch(pin){
            case 0: //PC7
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;	//RCC

                *(volatile unsigned int*)(0x40020800) &= ~(0x03U<<(7*2));
                *(volatile unsigned int*)(0x40020808) &= ~(0x03U<<(7*2));
                *(volatile unsigned int*)(0x4002080C) &= ~(0x03U<<(7*2));
                break;
            case 1: //PC6
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;	//RCC

                *(volatile unsigned int*)(0x40020800) &= ~(0x03U<<(6*2));
                *(volatile unsigned int*)(0x40020808) &= ~(0x03U<<(6*2));
                *(volatile unsigned int*)(0x4002080C) &= ~(0x03U<<(6*2));
                break;
            case 2: //PG6
                *(volatile unsigned int*)(0x40023830) |= 0x00000040U;	//RCC

                *(volatile unsigned int*)(0x40021800) &= ~(0x03U<<(6*2));
                *(volatile unsigned int*)(0x40021808) &= ~(0x03U<<(6*2));
                *(volatile unsigned int*)(0x4002180C) &= ~(0x03U<<(6*2));
                break;
            case 3: //PB4
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<1;	//RCC

                *(volatile unsigned int*)(0x40020400) &= ~(0x03U<<(4*2));
                *(volatile unsigned int*)(0x40020408) &= ~(0x03U<<(4*2));
                *(volatile unsigned int*)(0x4002040C) &= ~(0x03U<<(4*2));
                break;
            case 4: //PG7
                *(volatile unsigned int*)(0x40023830) |= 0x00000040U;	//RCC

                *(volatile unsigned int*)(0x40021800) &= ~(0x03U<<(7*2));
                *(volatile unsigned int*)(0x40021808) &= ~(0x03U<<(7*2));
                *(volatile unsigned int*)(0x4002180C) &= ~(0x03U<<(7*2));
                break;
            case 5: //PA8
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<0;	//RCC

                *(volatile unsigned int*)(0x40020000) &= ~(0x03U<<(8*2));
                *(volatile unsigned int*)(0x40020008) &= ~(0x03U<<(8*2));
                *(volatile unsigned int*)(0x4002000C) &= ~(0x03U<<(8*2));
                break;
            case 6: //PA2
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<0;	//RCC

                *(volatile unsigned int*)(0x40020000) &= ~(0x03U<<(2*2));
                *(volatile unsigned int*)(0x40020008) &= ~(0x03U<<(2*2));
                *(volatile unsigned int*)(0x4002000C) &= ~(0x03U<<(2*2));
                break;
            case 7: //PC1
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;	//RCC

                *(volatile unsigned int*)(0x40020800) &= ~(0x03U<<(1*2));
                *(volatile unsigned int*)(0x40020808) &= ~(0x03U<<(1*2));
                *(volatile unsigned int*)(0x4002080C) &= ~(0x03U<<(1*2));
                break;
            case 8: //PC2
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;	//RCC

                *(volatile unsigned int*)(0x40020800) &= ~(0x03U<<(2*2));
                *(volatile unsigned int*)(0x40020808) &= ~(0x03U<<(2*2));
                *(volatile unsigned int*)(0x4002080C) &= ~(0x03U<<(2*2));
                break;
            case 9: //PA3
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<0;	//RCC

                *(volatile unsigned int*)(0x40020000) &= ~(0x03U<<(3*2));
                *(volatile unsigned int*)(0x40020008) &= ~(0x03U<<(3*2));
                *(volatile unsigned int*)(0x4002000C) &= ~(0x03U<<(3*2));
                break;
            case 10: //PB9
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<1;	//RCC

                *(volatile unsigned int*)(0x40020400) &= ~(0x03U<<(9*2));
                *(volatile unsigned int*)(0x40020408) &= ~(0x03U<<(9*2));
                *(volatile unsigned int*)(0x4002040C) &= ~(0x03U<<(9*2));
                break;
            case 11: //PB15
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<1;	//RCC

                *(volatile unsigned int*)(0x40020400) &= ~(0x03U<<(15*2));
                *(volatile unsigned int*)(0x40020408) &= ~(0x03U<<(15*2));
                *(volatile unsigned int*)(0x4002040C) &= ~(0x03U<<(15*2));
                break;
            case 12: //PB14
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<1;	//RCC

                *(volatile unsigned int*)(0x40020400) &= ~(0x03U<<(12*2));
                *(volatile unsigned int*)(0x40020408) &= ~(0x03U<<(12*2));
                *(volatile unsigned int*)(0x4002040C) &= ~(0x03U<<(12*2));
                break;
            case 13: //PA9
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<0;	//RCC

                *(volatile unsigned int*)(0x40020000) &= ~(0x03U<<(9*2));
                *(volatile unsigned int*)(0x40020008) &= ~(0x03U<<(9*2));
                *(volatile unsigned int*)(0x4002000C) &= ~(0x03U<<(9*2));
                break;
            default:
                break;
        }
    }
}

void outDP(int pin, int v){
    if(v){
        switch(pin){
            case 0:
                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(7);
                break;
            case 1:
                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(6);
                break;
            case 2:
                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(6);
                break;
            case 3:
                *(volatile unsigned int*)(0x40020418)  = 0x01U<<(4);
                break;
            case 4:
                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(7);
                break;
            case 5:
                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(8);
                break;
            case 6:
                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(2);
                break;
            case 7:
                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(1);
                break;
            case 8:
                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(2);
                break;
            case 9:
                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(3);
                break;
            case 10:
                *(volatile unsigned int*)(0x40020418)  = 0x01U<<(9);
                break;
            case 11:
                *(volatile unsigned int*)(0x40020418)  = 0x01U<<(15);
                break;
            case 12:
                *(volatile unsigned int*)(0x40020418)  = 0x01U<<(14);
                break;
            case 13:
                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(9);
                break;
            default:
                break;
        }
    }else{
        switch(pin){
            case 0:
                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(7+16);
                break;
            case 1:
                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(6+16);
                break;
            case 2:
                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(6+16);
                break;
            case 3:
                *(volatile unsigned int*)(0x40020418)  = 0x01U<<(4+16);
                break;
            case 4:
                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(7+16);
                break;
            case 5:
                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(8+16);
                break;
            case 6:
                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(2+16);
                break;
            case 7:
                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(1+16);
                break;
            case 8:
                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(2+16);
                break;
            case 9:
                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(3+16);
                break;
            case 10:
                *(volatile unsigned int*)(0x40020418)  = 0x01U<<(9+16);
                break;
            case 11:
                *(volatile unsigned int*)(0x40020418)  = 0x01U<<(15+16);
                break;
            case 12:
                *(volatile unsigned int*)(0x40020418)  = 0x01U<<(14+16);
                break;
            case 13:
                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(9+16);
                break;
            default:
                break;
        }
    }
}

int inDP(int pin){
    int returnV = 0;
    switch(pin){
        case 0:
            returnV = (*(volatile unsigned int*)(0x40020810U) >>7) & (0x01U);
            break;
        case 1:
            returnV = (*(volatile unsigned int*)(0x40020810U) >>6) & (0x01U);
            break;
        case 2:
            returnV = (*(volatile unsigned int*)(0x40021810U) >>6) & (0x01U);
            break;
        case 3:
            returnV = (*(volatile unsigned int*)(0x40020410U) >>4) & (0x01U);
            break;
        case 4:
            returnV = (*(volatile unsigned int*)(0x40021810U) >>7) & (0x01U);
            break;
        case 5:
            returnV = (*(volatile unsigned int*)(0x40020010U) >>8) & (0x01U);
            break;
        case 6:
            returnV = (*(volatile unsigned int*)(0x40020010U) >>2) & (0x01U);
            break;
        case 7:
            returnV = (*(volatile unsigned int*)(0x40020810U) >>1) & (0x01U);
            break;
        case 8:
            returnV = (*(volatile unsigned int*)(0x40020810U) >>2) & (0x01U);
            break;
        case 9:
            returnV = (*(volatile unsigned int*)(0x40020010U) >>3) & (0x01U);
            break;
        case 10:
            returnV = (*(volatile unsigned int*)(0x40020410U) >>9) & (0x01U);
            break;
        case 11:
            returnV = (*(volatile unsigned int*)(0x40020410U) >>15) & (0x01U);
            break;
        case 12:
            returnV = (*(volatile unsigned int*)(0x40020410U) >>14) & (0x01U);
            break;
        case 13:
            returnV = (*(volatile unsigned int*)(0x40020010U) >>9) & (0x01U);
            break;
        default:
            break;
    }
    return returnV;
}
//----------------------------------------------------------------

//----------------------------------------------------------------
// ARDA Pin
void setAP(int pin, int mode){
    if(mode){
        switch(pin){
            case 0: //PA0
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<0;	//RCC

                *(volatile unsigned int*)(0x40020000) |= 0x01U<<(0*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40020008) |= 0x03U<<(0*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002000C) |= 0x01U<<(0*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(0);
                break;
            case 1: //PF10
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<5;	//RCC

                *(volatile unsigned int*)(0x40021400) |= 0x01U<<(10*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40021408) |= 0x03U<<(10*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002140C) |= 0x01U<<(10*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40021418)  = 0x01U<<(10);
                break;
            case 2: //PF9
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<5;	//RCC

                *(volatile unsigned int*)(0x40021400) |= 0x01U<<(9*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40021408) |= 0x03U<<(9*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002140C) |= 0x01U<<(9*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40021418)  = 0x01U<<(9);
                break;
            case 3: //PF8
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<5;	//RCC

                *(volatile unsigned int*)(0x40021400) |= 0x01U<<(8*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40021408) |= 0x03U<<(8*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002140C) |= 0x01U<<(8*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40021418)  = 0x01U<<(8);
                break;
            default:
                break;
        }
    }else{
        switch(pin){
            case 0: //PA0
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<0;	//RCC

                *(volatile unsigned int*)(0x40020000) &= ~(0x03U<<(0*2));
                *(volatile unsigned int*)(0x40020008) &= ~(0x03U<<(0*2));
                *(volatile unsigned int*)(0x4002000C) &= ~(0x03U<<(0*2));
                break;
            case 1: //PF10
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<5;	//RCC

                *(volatile unsigned int*)(0x40021400) &= ~(0x03U<<(10*2));
                *(volatile unsigned int*)(0x40021408) &= ~(0x03U<<(10*2));
                *(volatile unsigned int*)(0x4002140C) &= ~(0x03U<<(10*2));
                break;
            case 2: //PF9
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<5;	//RCC

                *(volatile unsigned int*)(0x40021400) &= ~(0x03U<<(9*2));
                *(volatile unsigned int*)(0x40021408) &= ~(0x03U<<(9*2));
                *(volatile unsigned int*)(0x4002140C) &= ~(0x03U<<(9*2));
                break;
            case 3: //PF8
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<5;	//RCC

                *(volatile unsigned int*)(0x40021400) &= ~(0x03U<<(8*2));
                *(volatile unsigned int*)(0x40021408) &= ~(0x03U<<(8*2));
                *(volatile unsigned int*)(0x4002140C) &= ~(0x03U<<(8*2));
                break;
            default:
                break;
        }
    }
}

void outAP(int pin, int v){
    if(v){
        switch(pin){
            case 0:
                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(0);
                break;
            case 1:
                *(volatile unsigned int*)(0x40021418)  = 0x01U<<(10);
                break;
            case 2:
                *(volatile unsigned int*)(0x40021418)  = 0x01U<<(9);
                break;
            case 3:
                *(volatile unsigned int*)(0x40021418)  = 0x01U<<(8);
                break;
            default:
                break;
        }
    }else{
        switch(pin){
            case 0:
                *(volatile unsigned int*)(0x40020018)  = 0x01U<<(0+16);
                break;
            case 1:
                *(volatile unsigned int*)(0x40021418)  = 0x01U<<(10+16);
                break;
            case 2:
                *(volatile unsigned int*)(0x40021418)  = 0x01U<<(9+16);
                break;
            case 3:
                *(volatile unsigned int*)(0x40021418)  = 0x01U<<(8+16);
                break;
            default:
                break;
        }
    }
}

int inAP(int pin){
    int returnV = 0;
    switch(pin){
        case 0:
            returnV = (*(volatile unsigned int*)(0x40020010U) >>0) & (0x01U);
            break;
        case 1:
            returnV = (*(volatile unsigned int*)(0x40021410U) >>10) & (0x01U);
            break;
        case 2:
            returnV = (*(volatile unsigned int*)(0x40021410U) >>9) & (0x01U);
            break;
        case 3:
            returnV = (*(volatile unsigned int*)(0x40021410U) >>8) & (0x01U);
            break;
        default:
            break;
    }
    return returnV;
}
//----------------------------------------------------------------

//----------------------------------------------------------------
// PWM Timer
//CH1
void GPIO_Config_TIM3_PC6_ARD1_PWM(){
    *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;
        //RCC_AHB2ENR GPIOC enable
    *(volatile unsigned int*)(0x40020800) |= 0x02U<<(6*2);
        //GPIOC MODER6 Alternate function mode - TIM
    *(volatile unsigned int*)(0x40020820) |= 0x02U<<(6*4);
        //GPIOC_AFRL AFR6 - set AF2 - Link TIM3 Channel2
}

void TIM3_PC6_ARD1_PWM_Config(){
    *(volatile unsigned int*)(0x40023840) |= 0x01U<<1;
        //RCC_APB1ENR - TIM3 enable
    *(volatile unsigned int*)(0x40000428) = 108 - 1;
        //set Prescaler value
    *(volatile unsigned int*)(0x4000042C) = 20000 - 1;
        //set Auto Reload register value
        //APB1 block's clock is 108MHz
        // 108,000,000/(108 * 20000) = 50(Hz)
    *(volatile unsigned int*)(0x40000434) = 1000;
        //TIM3 capture/compare register
        // 1000 -> 1ms(ARR = 20000 - 1)
    *(volatile unsigned int*)(0x40000418) |= 0x06U<<4;
        //TIM3_CCMR1 - OC1M
        //Output compare 1 mode
        //PWM mode 1
    *(volatile unsigned int*)(0x40000420) |= 0x01U<<0;
        //TIM3_CCER - CC1E
        //Capture/Compare 1 output enable
    *(volatile unsigned int*)(0x40000400) |= 0x01U<<0;
        //TIM3_CR1 - CEN
        //Counter enable
}

//CH2
void GPIO_Config_TIM3_PC7_ARD0_PWM(){
    *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;
    *(volatile unsigned int*)(0x40020800) |= 0x02U<<(7*2);
    *(volatile unsigned int*)(0x40020820) |= 0x02U<<(7*4);
}

void TIM3_PC7_ARD0_PWM_Config(){
    *(volatile unsigned int*)(0x40023840) |= 0x01U<<2;
    *(volatile unsigned int*)(0x40000428) = 108 - 1;
    *(volatile unsigned int*)(0x4000042C) = 20000 - 1;
    *(volatile unsigned int*)(0x40000438) = 1000;
    *(volatile unsigned int*)(0x40000418) |= 0x06U<<12;
        //TIM3_CCMR1 - OC2M
        //Output compare 2 mode
        //PWM mode 1
    *(volatile unsigned int*)(0x40000420) |= 0x01U<<4;
        //TIM3_CCER - CC2E
        //Capture/Compare 2 output enable
    *(volatile unsigned int*)(0x40000400) |= 0x01U<<0;
}
//----------------------------------------------------------------

//----------------------------------------------------------------
// Interrupt
void interrupt_setting_PG6_ARD2(){
    *(volatile unsigned int*)(0x40023830) |= 0x00000040U;
        //RCC_GPIOG clock enable
    *(volatile unsigned int*)(0x40021800) &= ~(0x03U<<(6*2));
    // *(volatile unsigned int*)(0x40021808) &= ~(0x03U<<(6*2));
    *(volatile unsigned int*)(0x4002180C) &= ~(0x03U<<(6*2));

    *(volatile unsigned int*)(0x40023844) |= 0x01U<<14;
        //RCC_APB2ENR - SYSSCFEN
    *(volatile unsigned int*)(0x4001380C) |= 0x06U<<((6%4) * 4);
        //SYSCFG_EXTICR2 - EXTI6 - PG6
    *(volatile unsigned int*)(0x40013C00) |= 0x01U<<6;
        //EXTI_IMR - IM6
    *(volatile unsigned int*)(0x40013C08) |= 0x01U<<6;
        //EXTI_RTSR - TR6   //rising edge trigger

    *(volatile unsigned int*)(0xE000E100) |= 1<<23;
        //NVIC  //Position-23-EXTI9_5
}

void interrupt_setting_PB4_ARD3(){
    *(volatile unsigned int*)(0x40023830) |= 0x01U<<1;
        //RCC_GPIOB clock enable
    *(volatile unsigned int*)(0x40020400) &= ~(0x03U<<(4*2));
    // *(volatile unsigned int*)(0x40020408) &= ~(0x03U<<(4*2));
    *(volatile unsigned int*)(0x4002040C) &= ~(0x03U<<(4*2));

    *(volatile unsigned int*)(0x40023844) |= 0x01U<<14;
        //RCC_APB2ENR - SYSSCFEN
    *(volatile unsigned int*)(0x4001380C) |= 0x01U<<((4%4) * 4);
        //SYSCFG_EXTICR2 - EXTI4 - PB4
    *(volatile unsigned int*)(0x40013C00) |= 0x01U<<4;
        //EXTI_IMR - IM4
    *(volatile unsigned int*)(0x40013C08) |= 0x01U<<4;
        //EXTI_RTSR - TR4   //rising edge trigger

    *(volatile unsigned int*)(0xE000E100) |= 1<<10;
        //NVIC  //Position-10-EXTI4
}
//----------------------------------------------------------------

int led=0;

//----------------------------------------------------------------
// Interrupt Handler
void EXTI9_5_IRQHandler(){
    if(*(volatile unsigned int*)(0x40013C14) & (0x01U<<6)){
        //PG6
        *(volatile unsigned int*)(0x40013C14) |= 0x01U<<6;  //EXTI_PR-PR6 clear

        led^=1;
        outDP(11,led);

        if(sensor1_count == 0){
            *(volatile unsigned int*)(0x40000000) |= 0x01U<<0;  //TIM2_CR1-CEN
                //timer 시작
            sensor1_count = 1;  //sensor1 detect first ball
            return;

        }
        // if(sensor1_count != 0){
        //     //caculate timing of distance  two balls
        //     //caculate t_d
        //
        //     // td = *(unsigned int*)(0x40000C24);  //TIM5_CNT
        //     //
        //     // *(volatile unsigned int*)(0x40000C24) = 0;
        //     // *(volatile unsigned int*)(0x40000C2C) = td;
        //
        //     td1[sensor1_counnt] = *(unsigned int*)(0x40000024);
        //
        //     sensor1_count++;
        // }
    }
}

void EXTI4_IRQHandler(){
    if(*(volatile unsigned int*)(0x40013C14) & (0x01U<<4)){
        //PB4
        *(volatile unsigned int*)(0x40013C14) |= 0x01U<<4;
            //interrupt clear

        led^=1;
        outDP(11,led);

        if(sensor2_count != 0){
            td2[sensor2_count] = *(unsigned int*)(0x40000024);
                                    //n번째 구슬이 Sensor2에 감지된 시간

            td3[sensor2_count] = int_sqrt(((unsigned long long)td2[sensor2_count]*(unsigned long long)td2[sensor2_count] + t0p5));
            td4[sensor2_count] = int_sqrt(((unsigned long long)td3[sensor2_count]*(unsigned long long)td3[sensor2_count] + t0p7));
                                    //td2를 베이스로 td3와 td4 계산, 배열에 저장

            if(*(volatile unsigned int*)(0x40000034) == 0){
                *(volatile unsigned int*)(0x40000034) = td3[sensor2_count];
            }//CCR이 비어있으면 TIM2에서 td3를 갱신하려했지만 값이 없어서 0이었던 경우
            if(*(volatile unsigned int*)(0x40000038) == 0){
                *(volatile unsigned int*)(0x40000038) = td4[sensor2_count];
            }

            sensor2_count = sensor2_count + 1 ;
        }
        if(sensor2_count == 0){
            //check counter value and save value
            //caculate t_0
            t0 = *(volatile unsigned int*)(0x40000024); //TIM2_CNT
            *(volatile unsigned int*)(0x40000024) = t0 * 2;   //modify CNT value
                                        //now CNT's 0 is first ball's start time

            t0t0 = t0 * t0;
            t0p5 = t0t0 * 5;
            t0p7 = t0t0 * 9;
                //원래는 9이지만
                //3d프린터 구조물에 의한 마찰변화로 인한 조정

            td3[0] = t0*3;
            td4[0] = t0<<2;

            *(volatile unsigned int*)(0x40000034) = td3[0];
            *(volatile unsigned int*)(0x40000038) = td4[0];
                //첫 번째 구슬이 Actuator1,2에 도착하는 시간 CCR에 입력

            sensor2_count = 1;

        }
    }
}

//----------------------------------------------------------------
void TIM2_setting(){
    *(volatile unsigned int*)(0x40023840) |= 0x01U<<0;  //RCC_APB1ENR-TIM2EN

    //*(volatile unsigned int*)(0x40000000) |= 0x01U<<0;  //TIM2_CR1-CEN

                            //system_clock : 216,000,000
                            //APB1 block -> 108,000,000
                            //2^31-1 : 2,147,483,647
    *(volatile unsigned int*)(0x4000000C) |= 0x01U<<1;  //TIM2_DIER-CC1IE
                                            //output compare interrupt1
    *(volatile unsigned int*)(0x4000000C) |= 0x01U<<2;  //TIM2_DIER-CC2IE
                                            //output compare interrupt2
            //CCR1 for actuator1 and CCR2 for actuator2
    *(volatile unsigned int*)(0x40000010) &= ~(0x01U<<1);   //CC1IF clear
    *(volatile unsigned int*)(0x40000010) &= ~(0x01U<<2);   //CC2IF clear

    *(volatile unsigned int*)(0x40000024) = 0;  //TIM2_CNT
    // *(volatile unsigned int*)(0x40000028) = 27 - 1;   //TIM2_PSC
    *(volatile unsigned int*)(0x40000028) = 43200 - 1;   //TIM2_PSC
                                            // CNT 10000 -> 1sec
    // *(volatile unsigned int*)(0x4000002C) = 8000000 - 1;   //TIM2_ARR
                                            //default value is 0xFFFFFFFF
                                            //use maximum value
                                            //don't use overflow
                                            // //먼저 2초간 테스트
    *(volatile unsigned int*)(0x4000000C) |= 0x01U<<0;  //TIM2_DIER-UIE
    *(volatile unsigned int*)(0x40000010) &= ~(0x01U<<0);   //TIM2_SR-UIF

    *(volatile unsigned int*)(0xE000E100) |= 0x01U<<28; //NVIC -> 28
}

void TIM2_IRQHandler(){
    if(*(volatile unsigned int*)(0x40000010) & (0x01U)){
        *(volatile unsigned int*)(0x40000010) &= ~(0x01U);   //TIM2_SR-UIF

        led^=1;
        outDP(11,led);
    }
    if(*(volatile unsigned int*)(0x40000010) & (0x01U<<1)){
        //Output Capture1
        *(volatile unsigned int*)(0x40000010) &= ~(0x01U<<1);
            //interrupt clear

        led^=1;
        outDP(11,led);

        actuator1_count++;
        *(volatile unsigned int*)(0x40000034) = td3[actuator1_count];
            //CCR1 값 갱신 다음 구슬이 도착하는 시점
        if(order[actuator1_count] == 1) *(volatile unsigned int*)(0x40000434) = 1000;
        if(order[actuator1_count] == 2 || order[actuator1_count] == 3) *(volatile unsigned int*)(0x40000434) = 2000;
            //구슬이 통과할거면 열고, 빠질거면 막음

        if(order[actuator1_count-1] == 1)count_rt[0]++;
    }
    if(*(volatile unsigned int*)(0x40000010) & (0x01U<<2)){
        //Output Capture2
        *(volatile unsigned int*)(0x40000010) &= ~(0x01U<<2);
            //interrupt clear

        led^=1;
        outDP(11,led);

        actuator2_count++;
        *(volatile unsigned int*)(0x40000038) = td4[actuator2_count];
            //CCR2 값 갱신 다음 구슬이 도착하는 시점
        if(order[actuator2_count] == 2) *(volatile unsigned int*)(0x40000438) = 1000;
        if(order[actuator2_count] == 3) *(volatile unsigned int*)(0x40000438) = 2000;
            //구슬이 통과할거면 열고, 빠질거면 막음

        if(order[actuator2_count-1] == 2)count_rt[1]++;
        if(order[actuator2_count-1] == 3)count_rt[2]++;


    }
}

void input_setting(){
    int now1 = 0;
    int now2 = 0;
    int now3 = 0;
    int now4 = 0;
    int prev1 = 0;
    int prev2 = 0;
    int prev3 = 0;
    int prev4 = 0;

    volatile unsigned int t;

    while(1){
        now1 = inAP(0);
        now2 = inAP(1);
        now3 = inAP(2);
        now4 = inAP(3);
            //polling 값 읽어옴

        if(now1 && !prev1){
            *(volatile unsigned int*)(0x40000434) = 1000;
            count[0]++;
            order[order_num] = 1;
            order_num++;
        }
        if(now2 && !prev2){
            *(volatile unsigned int*)(0x40000434) = 2000;
            *(volatile unsigned int*)(0x40000438) = 1000;
            count[1]++;
            order[order_num] = 2;
            order_num++;
        }
        if(now3 && !prev3){
            *(volatile unsigned int*)(0x40000434) = 2000;
            *(volatile unsigned int*)(0x40000438) = 2000;
            count[2]++;
            order[order_num] = 3;
            order_num++;
        }
        if(now4 && !prev4)break;
            //switch 입력 1~3 해당 번째 구슬이 빠질 홀 저장
            //어떻게 동작해야 하는지 서보모터 구동으로 보여줌

        prev1 = now1;
        prev2 = now2;
        prev3 = now3;
        prev4 = now4;
            //polling으로 구현함


        outDP(8,1);
        for(int k=0;k<4;k++)outDP(4+k,(count[2]>>k) & 0x01);
        for(t=0;t<500;t++);
        outDP(8,0);

        outDP(9,1);
        for(int k=0;k<4;k++)outDP(4+k,(count[1]>>k) & 0x01);
        for(t=0;t<500;t++);
        outDP(9,0);

        outDP(10,1);
        for(int k=0;k<4;k++)outDP(4+k,(count[0]>>k) & 0x01);
        for(t=0;t<500;t++);
        outDP(10,0);
            //7-Segment를 반복적으로 껐다키면서 세 개의 Segment를 Display
    }
}

void setting_first_position(){
    if(order[0]==1){
        *(volatile unsigned int*)(0x40000434) = 1000;
            //첫 번째 구슬이 첫번째 홀에 들어가면 미리 막음

        int order_index = 1;
        while(order[order_index] == 1)order_index++;
        if(order[order_index] == 0)return;
        else if(order[order_index] == 2) *(volatile unsigned int*)(0x40000438) = 1000;
        else if(order[order_index] == 3) *(volatile unsigned int*)(0x40000438) = 2000;
            //다음 구슬이 두 번째 홀인지 세 번째 홀에 들어가는지에 따라 미리 세팅함

    }else if(order[0]==2){
        *(volatile unsigned int*)(0x40000434) = 2000;
        *(volatile unsigned int*)(0x40000438) = 1000;
    }else if(order[0]==3){
        *(volatile unsigned int*)(0x40000434) = 2000;
        *(volatile unsigned int*)(0x40000438) = 2000;
    }   //두 번째, 세 번째 홀에 들어가는지에 따라 서보모터 미리 제어
}

void check_servo(){
    *(volatile unsigned int*)(0x40000434) = 1000;
    MyDelay_100ms(2);
    *(volatile unsigned int*)(0x40000438) = 1000;
    MyDelay_100ms(2);
    *(volatile unsigned int*)(0x40000434) = 2000;
    MyDelay_100ms(2);
    *(volatile unsigned int*)(0x40000438) = 2000;
        //각 서보모터 0~90도 동작 확인
}

int main(void){
    hwInit();

    GPIO_Config_TIM3_PC6_ARD1_PWM();
    TIM3_PC6_ARD1_PWM_Config();
    GPIO_Config_TIM3_PC7_ARD0_PWM();
    TIM3_PC7_ARD0_PWM_Config();
        //서보모터 세팅

    interrupt_setting_PG6_ARD2();
    interrupt_setting_PB4_ARD3();
        //인터럽트 세팅

    TIM2_setting();
        //타이머 세팅

    for(int i=4;i<11;i++)setDP(i,OUT);
    for(int i=0;i<4;i++)setAP(i,IN);
        //입출력핀 세팅

    setDP(11,OUT);
    outDP(11,led);
        //디버깅용 LED 무시해도 무방

    check_servo();
        //서보모터 세팅 확인

    input_setting();
        //홀 순서 정하는 구간

    setting_first_position();
        //첫번째 통과 홀 위치 세팅

    MyDelay_100ms(10);

    volatile unsigned int t;

    while(1){
        outDP(8,1);
        for(int k=0;k<4;k++)outDP(4+k,(count_rt[2]>>k) & 0x01);
        for(t=0;t<500;t++);
        outDP(8,0);

        outDP(9,1);
        for(int k=0;k<4;k++)outDP(4+k,(count_rt[1]>>k) & 0x01);
        for(t=0;t<500;t++);
        outDP(9,0);

        outDP(10,1);
        for(int k=0;k<4;k++)outDP(4+k,(count_rt[0]>>k) & 0x01);
        for(t=0;t<500;t++);
        outDP(10,0);
        //현재 들어간 구슬 수 표기
    }


    return 0;
}
