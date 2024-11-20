#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f10x.h"

//psc = 7199  time = 0.1ms
void TIM3_Int_Init(u16 arr, u16 psc);
void TIM3_PWM_Remap_Init(u16 arr, u16 psc);
void TIM3_CH1_Cap_Init(u16 arr,u16 psc);
void TIM5_CH1_Cap_Init(u16 arr,u16 psc);
void TIM5_CH2_Cap_Init(u16 arr,u16 psc);
void TIM5_IRQHandler(void);
void TIM3_IRQHandler(void);

#endif
