#include "led.h"
#define V_UINT32 volatile unsigned int

//0 - PA0 - WKUP
//1 - PF10
//2 - PF9
//3 - PF8

void MyDelay_100ms(unsigned int n){
	volatile unsigned int delay;
	for(delay=0;delay<=n * 3600000;delay++);
}

int count[3] = {0,0,0};
int order[10] = {0,};
int order_num = 0;

#define OUT 1
#define IN 0
//----------------------------------------------------------------
// ARDD Pin
void setDP(int pin, int mode){
    if(mode){
        switch(pin){
            case 0: //PC7
                *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;	//RCC

                *(volatile unsigned int*)(0x40020800) |= 0x01U<<(7*2);	//C_MODER		//01
                *(volatile unsigned int*)(0x40020808) |= 0x03U<<(7*2);	//C_OSPEEDR	//11
                *(volatile unsigned int*)(0x4002080C) |= 0x01U<<(7*2);	//C_PUPDR

                *(volatile unsigned int*)(0x40020818)  = 0x01U<<(7);
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
#define SystemCoreClock 216000000
#define PRESCALER_VALUE ((uint32_t)(SystemCoreClock / 1000000) - 1)
#define PERIOD_VALUE (20000 - 1)

//CH1
void GPIO_Config_TIM3_PC6_ARD1_PWM(){
    *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;
    *(volatile unsigned int*)(0x40020800) |= 0x02U<<(6*2);
    *(volatile unsigned int*)(0x40020820) |= 0x02U<<(6*4);
}

void TIM3_PC6_ARD1_PWM_Config(){
    *(volatile unsigned int*)(0x40023840) |= 0x01U<<1;
    *(volatile unsigned int*)(0x40000428) = PRESCALER_VALUE;
    *(volatile unsigned int*)(0x4000042C) = PERIOD_VALUE;
    *(volatile unsigned int*)(0x40000434) = 1000;   //90도
    *(volatile unsigned int*)(0x40000418) |= 0x06U<<4;
    *(volatile unsigned int*)(0x40000420) |= 0x01U<<0;
    *(volatile unsigned int*)(0x40000400) |= 0x01U<<0;
}

//CH2
void GPIO_Config_TIM3_PC7_ARD0_PWM(){
    *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;
    *(volatile unsigned int*)(0x40020800) |= 0x02U<<(7*2);
    *(volatile unsigned int*)(0x40020820) |= 0x02U<<(7*4);
}

void TIM3_PC7_ARD0_PWM_Config(){
    *(volatile unsigned int*)(0x40023840) |= 0x01U<<2;
    *(volatile unsigned int*)(0x40000428) = PRESCALER_VALUE;
    *(volatile unsigned int*)(0x4000042C) = PERIOD_VALUE;
    *(volatile unsigned int*)(0x40000438) = 1000;   //90도
    *(volatile unsigned int*)(0x40000418) |= 0x06U<<12;
    *(volatile unsigned int*)(0x40000420) |= 0x01U<<4;
    *(volatile unsigned int*)(0x40000400) |= 0x01U<<0;
}
//----------------------------------------------------------------

void input_setting(){
    int now1 = 0;
    int now2 = 0;
    int now3 = 0;
    int now4 = 0;
    int prev1 = 0;
    int prev2 = 0;
    int prev3 = 0;
    int prev4 = 0;
    while(1){
        now1 = inAP(0);
        now2 = inAP(1);
        now3 = inAP(2);
        now4 = inAP(3);
        
        if(now1 && !prev1){
            *(volatile unsigned int*)(0x40000434) = 500;
            count[0]++;
            order[order_num] = 1;
            order_num++;
        }
        if(now2 && !prev2){
            *(volatile unsigned int*)(0x40000434) = 1000;
            *(volatile unsigned int*)(0x40000438) = 500;
            count[1]++;
            order[order_num] = 2;
            order_num++;
        }
        if(now3 && !prev3){
            *(volatile unsigned int*)(0x40000434) = 1000;
            *(volatile unsigned int*)(0x40000438) = 1000;
            count[2]++;
            order[order_num] = 3;
            order_num++;
        }
        if(now4 && !prev4)break;

        prev1 = now1;
        prev2 = now2;
        prev3 = now3;
        prev4 = now4;

        volatile unsigned int t;

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
    }
}

void check_servo(){
    *(volatile unsigned int*)(0x40000434) = 500;
    MyDelay_100ms(2);
    *(volatile unsigned int*)(0x40000438) = 500;
    MyDelay_100ms(2);
    *(volatile unsigned int*)(0x40000434) = 1000;
    MyDelay_100ms(2);
    *(volatile unsigned int*)(0x40000438) = 1000;
}

int main(void){
    hwInit();

    GPIO_Config_TIM3_PC6_ARD1_PWM();
    TIM3_PC6_ARD1_PWM_Config();
    GPIO_Config_TIM3_PC7_ARD0_PWM();
    TIM3_PC7_ARD0_PWM_Config();

    for(int i=4;i<11;i++)setDP(i,OUT);
    for(int i=0;i<4;i++)setAP(i,IN);

    check_servo();

    input_setting();

    while(1);


    return 0;
}