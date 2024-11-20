#include "timer.h"
#include "led.h"
#include "beep.h"
#include "delay.h"
#include "uart.h"

void TIM3_Int_Init(u16 arr, u16 psc){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能计时器时钟
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);		//初始化计时器
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);				//使能定时器中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			//中断优先级分组
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);							//初始化并使能中断分组
	
	TIM_Cmd(TIM3, ENABLE);									//使能计时器
}

void TIM3_PWM_Remap_Init(u16 arr, u16 psc){
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能计时器时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能引脚时钟
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);						//初始化引脚
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//使能复用时钟
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);	//配置重映射
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);		//初始化计时器
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC2Init(TIM3, &TIM_OCInitStruct);					//初始化计时器通道二输出比较
	
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);		//配置预加载
	
	TIM_Cmd(TIM3, ENABLE);									//使能计时器
}

void TIM3_CH1_Cap_Init(u16 arr,u16 psc){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能引脚时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能计时器时钟
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);						//初始化引脚
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);		//初始化计时器
	
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICFilter = 0x00;
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM3, &TIM_ICInitStruct);					//初始化输入捕获
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			//中断优先级分组
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);							//初始化并使能中断分组
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);
	
	TIM_Cmd(TIM3, ENABLE); 	//使能定时器3
}

u8 TM3CH1_CAPTURE_STA = 0;
u16 TM3CH1_CAPTURE_VAL;

void TIM3_IRQHandler(void){
	if((TM3CH1_CAPTURE_STA & 0x80) == 0){
		if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET){
			if((TM3CH1_CAPTURE_STA & 0x40) != 0){
				if(TM3CH1_CAPTURE_STA >= 0x7F){
					TM3CH1_CAPTURE_VAL = 0xFFFF;
					TM3CH1_CAPTURE_STA |= 0x80;
					TIM_OC1PolarityConfig(TIM3, TIM_OCPolarity_High);
				}
				else TM3CH1_CAPTURE_STA++;
			}
		}
		if(TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET){
			if((TM3CH1_CAPTURE_STA & 0x40) != 0){
				TM3CH1_CAPTURE_VAL = TIM_GetCapture1(TIM3);
				TM3CH1_CAPTURE_STA |= 0x80;
				TIM_OC1PolarityConfig(TIM3, TIM_OCPolarity_High);
			}
			else {
				TIM_SetCounter(TIM3, 0);
				TM3CH1_CAPTURE_STA |= 0x40;
				TIM_OC1PolarityConfig(TIM3, TIM_OCPolarity_Low);
			}
		}
	}
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
}

void TIM5_CH2_Cap_Init(u16 arr,u16 psc){
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
//	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能引脚时钟
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);						//初始化引脚
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//使能计时器时钟
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStruct);		//初始化计时器
	
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStruct.TIM_ICFilter = 0x00;
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM5, &TIM_ICInitStruct);					//初始化输入捕获
	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			//中断优先级分组
//	
//	NVIC_InitStruct.NVIC_IRQChannel = TIM5_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
//	NVIC_Init(&NVIC_InitStruct);							//初始化并使能中断分组
	
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	TIM_ITConfig(TIM5, TIM_IT_CC2, ENABLE);
	
	TIM_Cmd(TIM5, ENABLE); 	//使能定时器5
}

void TIM5_CH1_Cap_Init(u16 arr,u16 psc){
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能引脚时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//使能计时器时钟
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);						//初始化引脚
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStruct);		//初始化计时器
	
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICFilter = 0x00;
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM5, &TIM_ICInitStruct);					//初始化输入捕获
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			//中断优先级分组
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);							//初始化并使能中断分组
	
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	TIM_ITConfig(TIM5, TIM_IT_CC1, ENABLE);
	
	TIM_Cmd(TIM5, ENABLE); 	//使能定时器5
}

u8 TM5CH1_CAPTURE_STA = 0;
u16 TM5CH1_CAPTURE_VAL;

u8 TM5CH2_CAPTURE_STA;
u16 TM5CH2_CAPTURE_VAL;

void TIM5_IRQHandler(void){
	if(TIM_GetFlagStatus(TIM5, TIM_IT_Update) == SET){
		Send_Num(USART1, 1);
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	}
	if(TIM_GetFlagStatus(TIM5, TIM_FLAG_CC2) == SET){
		Send_Num(USART1, 2);
		TIM_ClearITPendingBit(TIM5, TIM_FLAG_CC2);
	}
}


















