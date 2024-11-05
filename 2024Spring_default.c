
#if 01

*(volatile unsigned int*)(0x40023830U)|=0x00000050U;
*((V_UINT32*)(0x40021000U)) |= 0x00000100U; //[offser: 0x00] MODER12�� output ���(01)�� ����
*((V_UINT32*)(0x40021008U)) |= 0x00000C00U; //[offset: 0x08] OSPEEDR�� veryhigh(11)�� ����
*((V_UINT32*)(0x4002100cU)) |= 0x00000400U; //[offser: 0xoc] PUPDR�� pull up(01)�� ����
*((V_UINT32*)(0x40021018U)) |= 0x00000020U; //[offser: 0x18] BSRR�� reset

*((V_UINT32*)(0x40021800U)) |=0x00100000U;

*((V_UINT32*)(0x40021808U)) |= 0x00300000U;

*((V_UINT32*)(0x4002180cU)) |= 0x00100000U;

*((V_UINT32*)(0x40021818U)) |= 0x04000000U; //[offser: 0x18] BSRR�� reset

#endif
