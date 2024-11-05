#ifndef LED_H_
#define LED_H_

#include "def.h"
#include "stm32f7xx_hal.h"
static void SystemClock_Config(void);
void hwInit(void);

#endif

/*
 * MODER        00 input mode, 01 output mode
 * OSPEEDR      11 very high speed
 * PUPDR 0x0C   10 풀다운
 * BSRR         상위16비트 reset, 하위16비트 set
 * AHB1ENR      clock enable, 하위 11비트 GPIOA~K
*/
