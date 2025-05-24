void MyApp20240402_002(){
	*(volatile unsigned int*)(0x40023830) |= 0x01U<<4;

	*(volatile unsigned int*)(0x40021000) |= 0x01U<<10;
	*(volatile unsigned int*)(0x40021008) |= 0x03U<<10;
	*(volatile unsigned int*)(0x4002100C) |= 0x01U<<10;
	*(volatile unsigned int*)(0x40021018)  = 0x01U<<(5+16);
}