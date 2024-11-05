void MyApp20240401_000(){
	*(volatile unsigned int*)(0x40023830) |= 0x00000040U;	//RCC

	*(volatile unsigned int*)(0x40021800) |= 0x01000000U;	//G_MODER		//01
	*(volatile unsigned int*)(0x40021808) |= 0x03000000U;	//G_OSPEEDR	//11
	*(volatile unsigned int*)(0x4002180C) |= 0x01000000U;	//G_PUPDR		//01
	*(volatile unsigned int*)(0x40021818) |= 0x10000000U;	//G_BSRR		//
}