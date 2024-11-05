#if 0

#include "led.h"
#define V_UINT32 volatile unsigned int

void MyDelay10(unsigned int n){
	volatile unsigned int delay;
	for(delay=0;delay<=n * 3600000;delay++);
}

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

void LEDOnOff(unsigned int No){
    Init();

    unsigned int led[4];
    led[0] = (No>>24) & 0xFF;
    led[1] = (No>>16) & 0xFF;
    led[2] = (No>>8) & 0xFF;
    led[3] = (No) & 0xFF;

    unsigned int status[4] = {0,0,0,0};

    unsigned int cycle[4] = {
        led[0] & 0x0F,
        led[1] & 0x0F,
        led[2] & 0x0F,
        led[3] & 0x0F
    };

    if((led[0]>>4) == 0x0F){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12 + 16);	//G_BSRR
    }else if((led[0]>>4) == 0x00){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);	//G_BSRR
    }else{
        status[0] = led[0] & 0x0F;
    }

    if((led[1]>>4) == 0x0F){
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5 + 16);
    }else if((led[1]>>4) == 0x00){
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
    }else{
        status[1] = led[1] & 0x0F;
    }

    if((led[2]>>4) == 0x0F){
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);
    }else if((led[2]>>4) == 0x00){
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
    }else{
        status[2] = led[2] & 0x0F;
    }

    if((led[3]>>4) == 0x0F){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10 + 16);
    }else if((led[3]>>4) == 0x00){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);
    }else{
        status[3] = led[2] & 0x0F;
    }

    unsigned int i=0;

    while(status[0] || status[1] || status[2] || status[3]){
        if(status[0]){
            if((led[0] & 0x0F) % 2 == 0 ){
                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12 + 16);
            }else{
                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);
            }
        }
        if(status[1]){
            if((led[1] & 0x0F) % 2 == 0 ){
                *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5 + 16);
            }else{
                *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
            }
        }
        if(status[2]){
            if((led[2] & 0x0F) % 2 == 0 ){
                *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);
            }else{
                *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
            }
        }
        if(status[3]){
            if((led[3] & 0x0F) % 2 == 0 ){
                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10 + 16);
            }else{
                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);
            }
        }

        MyDelay10(5);

        if(status[0]){
            if((led[0] & 0x0F) % 2 == 1 ){
                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12 + 16);
            }else{
                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);
            }
            status[0] = status[0] - 1;
        }
        if(status[1]){
            if((led[1] & 0x0F) % 2 == 1 ){
                *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5 + 16);
            }else{
                *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
            }
            status[1] = status[1] - 1;
        }
        if(status[2]){
            if((led[2] & 0x0F) % 2 == 1 ){
                *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);
            }else{
                *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
            }
            status[2] = status[2] - 1;
        }
        if(status[3]){
            if((led[3] & 0x0F) % 2 == 1 ){
                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10 + 16);
            }else{
                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);
            }
            status[3] = status[3] - 1;
        }

        MyDelay10(5);
    }

}

void MyApp(){
    LEDOnOff(0xF0F0F1FF);
    MyDelay(5);
    LEDOnOff(0x0000010F);
    MyDelay(5);
    LEDOnOff(0x15FF2A01);
    MyDelay(5);
    LEDOnOff(0x0F0F0F0F);
    MyDelay(5);
    LEDOnOff(0xA3138323);
}

int main(void){
	hwInit();

    MyApp();

	return 0;
}

#endif

#if 01

#include "led.h"
#define V_UINT32 volatile unsigned int

void MyDelay10(unsigned int n){
	volatile unsigned int delay;
	for(delay=0;delay<=n * 3600000;delay++);
}

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

void LEDOnOff(unsigned int No){
    Init();

    unsigned int led[4];
    led[0] = (No>>24) & 0xFF;
    led[1] = (No>>16) & 0xFF;
    led[2] = (No>>8) & 0xFF;
    led[3] = (No) & 0xFF;

    unsigned int status[4] = {0,0,0,0};

    unsigned int cycle[4] = {
        led[0] & 0x0F,
        led[1] & 0x0F,
        led[2] & 0x0F,
        led[3] & 0x0F
    };

    if((led[0]>>4) == 0x0F){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12 + 16);	//G_BSRR
    }else if((led[0]>>4) == 0x00){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);	//G_BSRR
    }else{
        status[0] = led[0] & 0x0F;
    }

    if((led[1]>>4) == 0x0F){
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5 + 16);
    }else if((led[1]>>4) == 0x00){
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
    }else{
        status[1] = led[1] & 0x0F;
    }

    if((led[2]>>4) == 0x0F){
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);
    }else if((led[2]>>4) == 0x00){
        *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
    }else{
        status[2] = led[2] & 0x0F;
    }

    if((led[3]>>4) == 0x0F){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10 + 16);
    }else if((led[3]>>4) == 0x00){
        *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);
    }else{
        status[3] = led[2] & 0x0F;
    }

    unsigned int i=0;

    while(status[0] || status[1] || status[2] || status[3]){
        if(status[0]){
            if((led[0] & 0x0F) % 2 == 0 ){
                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12 + 16);
            }else{
                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);
            }
        }
        if(status[1]){
            if((led[1] & 0x0F) % 2 == 0 ){
                *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5 + 16);
            }else{
                *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
            }
        }
        if(status[2]){
            if((led[2] & 0x0F) % 2 == 0 ){
                *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);
            }else{
                *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
            }
        }
        if(status[3]){
            if((led[3] & 0x0F) % 2 == 0 ){
                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10 + 16);
            }else{
                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);
            }
        }

        MyDelay10(5);

        if(status[0]){
            if((led[0] & 0x0F) % 2 == 1 ){
                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12 + 16);
            }else{
                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);
            }
            status[0] = status[0] - 1;
        }
        if(status[1]){
            if((led[1] & 0x0F) % 2 == 1 ){
                *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5 + 16);
            }else{
                *(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
            }
            status[1] = status[1] - 1;
        }
        if(status[2]){
            if((led[2] & 0x0F) % 2 == 1 ){
                *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);
            }else{
                *(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
            }
            status[2] = status[2] - 1;
        }
        if(status[3]){
            if((led[3] & 0x0F) % 2 == 1 ){
                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10 + 16);
            }else{
                *(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);
            }
            status[3] = status[3] - 1;
        }

        MyDelay10(5);
    }

}

void MyApp(){
    LEDOnOff(0xF0F0F1FF);
    MyDelay(5);
    LEDOnOff(0x0000010F);
    MyDelay(5);
    LEDOnOff(0x15FF2A01);
    MyDelay(5);
    LEDOnOff(0x0F0F0F0F);
    MyDelay(5);
    LEDOnOff(0xA3138323);
}

int main(void){
	hwInit();

    MyApp();

	return 0;
}

#endif

