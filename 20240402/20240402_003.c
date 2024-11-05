void MyApp20240402_003(){
	*(volatile unsigned int*)(0x40023830) |= 0x01U<<4;

	*(volatile unsigned int*)(0x40021000) |= 0x01U<<8;
	*(volatile unsigned int*)(0x40021008) |= 0x03U<<8;
	*(volatile unsigned int*)(0x4002100C) |= 0x01U<<8;
	*(volatile unsigned int*)(0x40021018)  = 0x01U<<(4+16);
}