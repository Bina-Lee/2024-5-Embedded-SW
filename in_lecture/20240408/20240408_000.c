void MyApp20240408_001(){
	*(volatile unsigned int*)(0x40023830) |= 0x01U<<6;

	*(volatile unsigned int*)(0x40021800) |= 0x01U<<24;
	*(volatile unsigned int*)(0x40021808) |= 0x03U<<24;
	*(volatile unsigned int*)(0x4002180C) |= 0x01U<<24;
	*(volatile unsigned int*)(0x40021818)  = 0x01U<<(16+12);

	*(volatile unsigned int*)(0x40021818)  = 0x01U<<12;
}