void MyApp20240408_002_Init(){
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

void MyApp20240408_002_LED_ON(){
		*(volatile unsigned int*)(0x40021818)  = 0x01U<<(12+16);	//G_BSRR		//
		//*(volatile unsigned int*)(0x40021818)  = 0x01U<<(10+16);	//G_BSRR		//
		*(volatile unsigned int*)(0x40021018)  = 0x01U<<(5+16);
		*(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);
}

void MyApp20240408_002_LED_OFF(){
		*(volatile unsigned int*)(0x40021818)  = 0x01U<<(12);	//G_BSRR		//
		//*(volatile unsigned int*)(0x40021818)  = 0x01U<<(10);	//G_BSRR		//
		*(volatile unsigned int*)(0x40021018)  = 0x01U<<(5);
		*(volatile unsigned int*)(0x40021018)  = 0x01U<<(4);
}

void MyApp20240408_001(){
	MyApp20240408_002_Init();
	while(1){
		MyApp20240408_002_LED_ON();
		MYApp20240408_002_LEDOFF();
	}
}