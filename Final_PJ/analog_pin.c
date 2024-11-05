//0 - PA0 - WKUP
//1 - PF10
//2 - PF9
//3 - PF8

#define OUT 1
#define IN 0

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
            case 4:
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