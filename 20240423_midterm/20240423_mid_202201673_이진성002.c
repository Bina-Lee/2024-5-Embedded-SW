#include "led.h"
#define V_UINT32 volatile unsigned int

void InitGPIO(){
    *(volatile unsigned int*)(0x40023830) |= 0x00000040U;

    *(volatile unsigned int*)(0x40021800) |= 0x01U<<24;
    *(volatile unsigned int*)(0x40021808) |= 0x03U<<24;
    *(volatile unsigned int*)(0x4002180C) |= 0x01U<<24;

    *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12+16);
    
    *(volatile unsigned int*)(0x40023830) |= 0x01U<<4;

    *(volatile unsigned int*)(0x40021000) |= 0x01U<<10;
    *(volatile unsigned int*)(0x40021008) |= 0x03U<<10;
    *(volatile unsigned int*)(0x4002100C) |= 0x01U<<10;

    *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5+16);
    
    *(volatile unsigned int*)(0x40023830) |= 0x01U<<4;

    *(volatile unsigned int*)(0x40021000) |= 0x01U<<8;
    *(volatile unsigned int*)(0x40021008) |= 0x03U<<8;
    *(volatile unsigned int*)(0x4002100C) |= 0x01U<<8;

    *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);

    *(volatile unsigned int*)(0x40023830) |= 0x00000040U;

    *(volatile unsigned int*)(0x40021800) |= 0x01U<<20;
    *(volatile unsigned int*)(0x40021808) |= 0x03U<<20;
    *(volatile unsigned int*)(0x4002180C) |= 0x01U<<20;

    *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10+16);
}

void MyDelay_100ms(unsigned int n){
	volatile unsigned int delay;
	for(delay=0;delay<=n * 3600000;delay++);
}

char MoveLED(char Dir, char Start, char Count, char Blink){
    *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);
    *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
    *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
    *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);

    if(!Dir){
        if(!Blink){
            for(int i=0;i<Count;i++){
                for(int j=Start-1;j<Start+3;j++){
                    switch(j%4){
                        case 0:
                            *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12+16);
                            MyDelay_100ms(8);
                            *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);
                            MyDelay_100ms(2);
                            break;
                        case 1:
                            *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5+16);
                            MyDelay_100ms(8);
                            *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
                            MyDelay_100ms(2);
                            break;
                        case 2:
                            *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);
                            MyDelay_100ms(8);
                            *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
                            MyDelay_100ms(2);
                            break;
                        case 3:
                            *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10+16);
                            MyDelay_100ms(8);
                            *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);
                            MyDelay_100ms(2);
                            break;
                    }
                }
            }
        }
        else{
            for(int i=0;i<Count;i++){
                for(int j=Start-1;j<Start+3;j++){
                    switch(j%4){
                        case 0:
                            for(int k=0;k<5;k++){
                                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12+16);
                                MyDelay_100ms(1);
                                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);
                                MyDelay_100ms(1);
                            }
                            break;
                        case 1:
                            for(int k=0;k<5;k++){
                                *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5+16);
                                MyDelay_100ms(1);
                                *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
                                MyDelay_100ms(1);
                            }
                            break;
                        case 2:
                            for(int k=0;k<5;k++){
                                *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);
                                MyDelay_100ms(1);
                                *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
                                MyDelay_100ms(1);
                            }
                            break;
                        case 3:
                            for(int k=0;k<5;k++){
                                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10+16);
                                MyDelay_100ms(1);
                                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);
                                MyDelay_100ms(1);
                            }
                            break;
                    }
                }
            }
        }
    }
    else{
        if(!Blink){
            for(int i=0;i<Count;i++){
                for(int j=Start+7;j>=Start+4;j--){
                    switch(j%4){
                        case 0:
                            *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12+16);
                            MyDelay_100ms(8);
                            *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);
                            MyDelay_100ms(2);
                            break;
                        case 1:
                            *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5+16);
                            MyDelay_100ms(8);
                            *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
                            MyDelay_100ms(2);
                            break;
                        case 2:
                            *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);
                            MyDelay_100ms(8);
                            *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
                            MyDelay_100ms(2);
                            break;
                        case 3:
                            *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10+16);
                            MyDelay_100ms(8);
                            *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);
                            MyDelay_100ms(2);
                            break;
                    }
                }
            }
        }
        else{
            for(int i=0;i<Count;i++){
                for(int j=Start+7;j>=Start+4;j--){
                    switch(j%4){
                        case 0:
                            for(int k=0;k<5;k++){
                                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12+16);
                                MyDelay_100ms(1);
                                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);
                                MyDelay_100ms(1);
                            }
                            break;
                        case 1:
                            for(int k=0;k<5;k++){
                                *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5+16);
                                MyDelay_100ms(1);
                                *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
                                MyDelay_100ms(1);
                            }
                            break;
                        case 2:
                            for(int k=0;k<5;k++){
                                *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);
                                MyDelay_100ms(1);
                                *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
                                MyDelay_100ms(1);
                            }
                            break;
                        case 3:
                            for(int k=0;k<5;k++){
                                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10+16);
                                MyDelay_100ms(1);
                                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);
                                MyDelay_100ms(1);
                            }
                            break;
                    }
                }
            }
        }
    }
    char returnV;
    if(!Dir){
        returnV = (Start+3)%4;  
    }
    else{
        returnV = (Start+1)%4;
    }
    
    if(returnV == 0)returnV = 4;

    if(returnV == 1){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12+16);
        MyDelay_100ms(10);
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);
    }else if(returnV ==2){
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5+16);
        MyDelay_100ms(10);
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
                               
    }else if(returnV==3){
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);
        MyDelay_100ms(10);
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
        
    }else if(returnV==4){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10+16);
        MyDelay_100ms(10);
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);
    }

    return returnV;
    
}

void MyApp(){
    unsigned char Dir = 0,Start = 1,Count = 4, Ret = 0, Blink = 0;

    InitGPIO();

    Ret = MoveLED(Dir, Start, Count, Blink);
    
    Ret = MoveLED(!Dir, Ret, Count, !Blink);
    return;
}

int main(void){
	hwInit();

    MyApp();


	return 0;
}