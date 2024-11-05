#include "led.h"
#define V_UINT32 volatile unsigned int

#define OUT 1
#define IN 0
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

                *(volatile unsigned int*)(0x40020400) &= ~(0x03U<<(4*2));
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

int btn_check(){
    int returnV = ((*(volatile unsigned int*)(0x40021810U) >>3) & (0x01U)) + ((*(volatile unsigned int*)(0x40020810U) >>11) & (0x02U));
    return returnV;
}

//polling으로 구현함
//매 순간 받아서 값 지정
int main(void){
    hwInit();
    switch12Init();
    setDP(1,OUT);
    setDP(2,OUT);
    setDP(3,OUT);
    
    unsigned int btn = 0;

    volatile unsigned t=0;
    
    while(1){

        for(t=0;t<1200000;t++){
            btn = btn_check();
            if(btn ==1){
                outDP(1,0);
                outDP(2,0);
                outDP(3,0);
            }
            if(btn==2){
                outDP(1,0);
                outDP(2,0);
                outDP(3,0);
            }
            if(btn==3){
                outDP(1,1);
                outDP(2,1);
                outDP(3,1);
            }
            if(btn==0){
                outDP(1,1);
                outDP(2,1);
                outDP(3,1);
            }
        }

        for(t=0;t<1200000;t++){
            btn = btn_check();
            if(btn ==1){
                outDP(1,0);
                outDP(2,0);
                outDP(3,0);
            }
            if(btn==2){
                outDP(1,0);
                outDP(2,0);
                outDP(3,0);
            }
            if(btn==3){
                outDP(1,0);
                outDP(2,1);
                outDP(3,1);
            }
            if(btn==0){
                outDP(1,0);
                outDP(2,0);
                outDP(3,0);
            }
        }
    }


    return 0;
}