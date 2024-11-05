//pa8
//pb4 - ard3

//pc7 - ard0

/*
	1.	고급 제어 타이머 (Advanced-control Timers):
	•	TIM1: 16-bit 타이머, 고급 제어 기능 포함 (PWM, Dead-time generation 등)
	•	TIM8: 16-bit 타이머, 고급 제어 기능 포함
	2.	일반 타이머 (General-purpose Timers):
	•	TIM2: 32-bit 타이머
	•	TIM3: 16-bit 타이머
	•	TIM4: 16-bit 타이머
	•	TIM5: 32-bit 타이머
	•	TIM9: 16-bit 타이머
	•	TIM10: 16-bit 타이머
	•	TIM11: 16-bit 타이머
	•	TIM12: 16-bit 타이머
	•	TIM13: 16-bit 타이머
	•	TIM14: 16-bit 타이머
	3.	기본 타이머 (Basic Timers):
	•	TIM6: 16-bit 타이머
	•	TIM7: 16-bit 타이머
	4.	저전력 타이머 (Low-power Timers):
	•	LPTIM1: 16-bit 타이머
	•	LPTIM2: 16-bit 타이머
*/

/*
TIM1 타이머
	•	TIM1_CH1: PA8, PE9
	•	TIM1_CH2: PA9, PE11
	•	TIM1_CH3: PA10, PE13
	•	TIM1_CH4: PA11, PE14
TIM2 타이머
	•	TIM2_CH1: PA0, PA5, PA15
	•	TIM2_CH2: PA1, PB3
	•	TIM2_CH3: PA2, PB10
	•	TIM2_CH4: PA3, PB11
TIM3 타이머
	•	TIM3_CH1: PA6, PB4, PC6
	•	TIM3_CH2: PA7, PB5, PC7
	•	TIM3_CH3: PB0, PC8
	•	TIM3_CH4: PB1, PC9
TIM4 타이머
	•	TIM4_CH1: PB6, PD12
	•	TIM4_CH2: PB7, PD13
	•	TIM4_CH3: PB8, PD14
	•	TIM4_CH4: PB9, PD15
TIM5 타이머
	•	TIM5_CH1: PA0, PH10
	•	TIM5_CH2: PA1, PH11
	•	TIM5_CH3: PA2, PH12
	•	TIM5_CH4: PA3, PI0
TIM8 타이머
	•	TIM8_CH1: PC6, PI5
	•	TIM8_CH2: PC7, PI6
	•	TIM8_CH3: PC8, PI7
	•	TIM8_CH4: PC9, PI2
TIM9 타이머
	•	TIM9_CH1: PA2, PE5
	•	TIM9_CH2: PA3, PE6
TIM10 타이머
	•	TIM10_CH1: PB8, PF6
TIM11 타이머
	•	TIM11_CH1: PB9, PF7
TIM12 타이머
	•	TIM12_CH1: PB14, PH6
	•	TIM12_CH2: PB15, PH9
TIM13 타이머
	•	TIM13_CH1: PA6, PF8
TIM14 타이머
	•	TIM14_CH1: PA7, PF9
*/

/*
case 0: //PC7   timer3
case 1: //PC6   timer3, timer8
case 2: //PG6
case 3: //PB4   timer3
case 4: //PG7
case 5: //PA8   timer8
case 6: //PA2   timer2, timer5, timer9
case 7: //PC1
case 8: //PC2
case 9: //PA3   timer2, timer5, timer9
case 10: //PB9  timer4, timer11
case 11: //PB15 timer12
case 12: //PB14 timer12
case 13: //PA9  timer1
*/

/*
TIMx_CNT
TIMx_PSC
TIMx_ARR
*/

/*
TIMx_CR1
TIM3
address offset 0x00
reset value 0x0000

pb4 arduino digital pin3
timer3, ch1
*/

// #include "stm32f7xx.h"

// 주파수를 맞추기 위한 프리스케일러 값 계산
#define PRESCALER_VALUE ((uint32_t)(SystemCoreClock / 1000000) - 1) // 1 MHz 타이머 클럭

// PWM 주기를 설정하기 위한 자동 재로드 레지스터 값
#define PERIOD_VALUE (20000 - 1) // 20 ms 주기 (50 Hz PWM 신호)


//RCC : 0x4002_3800

//AHB1ENR : 0x30
//1번비트

//APB1ENR : 0x40
//timer3 : 1번비트

//GPIO_B : 0x4002_0400

//MODER
//offet : 0x00
//reset : 0x0000_0280

//AFRL
//offset : 0x20
//reset : 0x0000_0000
//AFR4 : 19~16
//value : 0x02 -> 0010

//TIM3 : 4000_0400
//PSC : 0x28
//ARR : 0x2C
//CCR1 : 0x34
//CCMR1 : 0x18
    //reset : 0x0000
//CCER : 0x20
//CR1 : 0x00
    //CEN : 0번 비트


// void GPIO_Config(void)
// {
//   // GPIOB 클럭 활성화
//   //RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
//     *(volatile unsigned int*)(0x40023830) |= 0x01U<<1;
//   // GPIOB 핀 4를 AF 모드로 설정
// //   GPIOB->MODER &= ~(GPIO_MODER_MODER4);
// //   GPIOB->MODER |= (GPIO_MODER_MODER4_1);
//     *(volatile unsigned int*)(0x40020400) |= 0x02U<<(4*2);
//   // PB4를 AF2 (TIM3_CH1)으로 설정
// //   GPIOB->AFR[0] &= ~(GPIO_AFRL_AFRL4);
// //   GPIOB->AFR[0] |= (2 << GPIO_AFRL_AFRL4_Pos);
//     *(volatile unsigned int*)(0x40020420) |= 0x02U<<(4*4);
// }

void GPIO_Config_TIM3_PB4_ARD3_PWM(void)
{
    *(volatile unsigned int*)(0x40023830) |= 0x01U<<1;
    *(volatile unsigned int*)(0x40020400) |= 0x02U<<(4*2);
    *(volatile unsigned int*)(0x40020420) |= 0x02U<<(4*4);
}

// void TIM3_Config(void)
// {
//   // 타이머 3 클럭 활성화
// //   RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
//     *(volatile unsigned int*)(0x40023840) |= 0x01U<<1;
//   // 프리스케일러 설정 (1 MHz 타이머 클럭)
// //   TIM3->PSC = PRESCALER_VALUE;
//     *(volatile unsigned int*)(0x40000428) = PRESCALER_VALUE;
//   // 자동 재로드 레지스터 설정 (20 ms 주기)
// //   TIM3->ARR = PERIOD_VALUE;
//     *(volatile unsigned int*)(0x4000042C) = PERIOD_VALUE;
//   // CCR1 초기 값 설정 (1.5 ms 듀티 사이클)
// //   TIM3->CCR1 = 1500;
//     *(volatile unsigned int*)(0x40000434) = 1500;
//   // PWM 모드 1 설정, 채널 1 활성화
// //   TIM3->CCMR1 &= ~(TIM_CCMR1_OC1M);
// //   TIM3->CCMR1 |= (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2);
//     *(volatile unsigned int*)(0x40000418) |= 0x06U<<4;
//   // OC1 출력 활성화
// //   TIM3->CCER |= TIM_CCER_CC1E;
//     *(volatile unsigned int*)(0x40000420) |= 0x01U<<0;
//   // 타이머 활성화
// //   TIM3->CR1 |= TIM_CR1_CEN;
//     *(volatile unsigned int*)(0x40000400) |= 0x01U<<0;
// }

void TIM3_PB4_ARD3_PWM_Config(void)
{
    *(volatile unsigned int*)(0x40023840) |= 0x01U<<1;
    *(volatile unsigned int*)(0x40000428) = PRESCALER_VALUE;
    *(volatile unsigned int*)(0x4000042C) = PERIOD_VALUE;
    *(volatile unsigned int*)(0x40000434) = 1500;
    *(volatile unsigned int*)(0x40000418) |= 0x06U<<4;
    *(volatile unsigned int*)(0x40000420) |= 0x01U<<0;
    *(volatile unsigned int*)(0x40000400) |= 0x01U<<0;
}

int main(void)
{
  // System 초기화
  SystemInit();

  // GPIO 설정
  GPIO_Config_TIM3_PB4_ARD3_PWM();

  // TIM3 설정
  TIM3_PB4_ARD3_PWM_Config();

  // TIM3 시작
//   TIM3->CR1 |= TIM_CR1_CEN; // 타이머 카운터 활성화
    *(volatile unsigned int*)(0x40000400) |= 0x01U<<0;

  while (1)
  {
    for (int pulse = 1000; pulse <= 2000; pulse += 10)
    {
    //   TIM3->CCR1 = pulse; // 듀티 사이클 설정
        *(volatile unsigned int*)(0x40000434) = pulse;
        for(volatile int i = 0; i < 100000; i++); // 지연
    }

    for (int pulse = 2000; pulse >= 1000; pulse -= 10)
    {
    //   TIM3->CCR1 = pulse; // 듀티 사이클 설정
        *(volatile unsigned int*)(0x40000434) = pulse;
        for(volatile int i = 0; i < 100000; i++); // 지연
    }
  }
}

#if 01

#define PRESCALER_VALUE ((uint32_t)(SystemCoreClock / 1000000) - 1)
#define PERIOD_VALUE (20000 - 1)


void GPIO_Config_TIM3_PB4_ARD3_PWM(void)
{
    *(volatile unsigned int*)(0x40023830) |= 0x01U<<1;
    *(volatile unsigned int*)(0x40020400) |= 0x02U<<(4*2);
    *(volatile unsigned int*)(0x40020420) |= 0x02U<<(4*4);
}

void TIM3_PB4_ARD3_PWM_Config(void)
{
    *(volatile unsigned int*)(0x40023840) |= 0x01U<<1;
    *(volatile unsigned int*)(0x40000428) = PRESCALER_VALUE;
    *(volatile unsigned int*)(0x4000042C) = PERIOD_VALUE;
    *(volatile unsigned int*)(0x40000434) = 1500;
    *(volatile unsigned int*)(0x40000418) |= 0x06U<<4;
    *(volatile unsigned int*)(0x40000420) |= 0x01U<<0;
    *(volatile unsigned int*)(0x40000400) |= 0x01U<<0;
}

void GPIO_Config_TIM3_PC7_ARD0_PWM(void){
    *(volatile unsigned int*)(0x40023830) |= 0x01U<<2;
    *(volatile unsigned int*)(0x40020800) |= 0x02U<<(7*2);
    *(volatile unsigned int*)(0x40020820) |= 0x02U<<(7*4);
}

void TIM3_PC7_ARD0_PWM_Config(void){
    *(volatile unsigned int*)(0x40023840) |= 0x01U<<2;
    *(volatile unsigned int*)(0x40000428) = PRESCALER_VALUE;
    *(volatile unsigned int*)(0x4000042C) = PERIOD_VALUE;
    *(volatile unsigned int*)(0x40000438) = 1500;
    *(volatile unsigned int*)(0x40000418) |= 0x06U<<12;
    *(volatile unsigned int*)(0x40000420) |= 0x01U<<4;
    *(volatile unsigned int*)(0x40000400) |= 0x01U<<0;
}

#endif