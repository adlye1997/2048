#include "tpad.h"
#include "timer.h"
#include "stm32f10x.h"
#include "calculate.h"
#include "delay.h"

void Tpad_Init(){
	TIM5_CH2_Cap_Init(65535, 71);
}

u32 Tpad_Get_Base_Val(){
	u8 i;
	u32 num[10];
	u16 sum;
	for(i = 0; i < 10; i++){
		num[i] = Tpad_Get_Val();
	}
	Sort_Down(num, 10);
	sum = 0;
	for(i = 2; i < 8; i++){
		sum += num[i];
	}
	sum /= 6;
	return sum;
}

void Tpad_Reset(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);						//初始化引脚
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	delay_ms(10);
	TIM_ClearITPendingBit(TIM5, TIM_IT_CC2 | TIM_IT_Update);
	TIM_SetCounter(TIM5, 0);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStruct);						//初始化引脚
}

u32 Tpad_Get_Val(void){
	Tpad_Reset();
	while(TIM_GetFlagStatus(TIM5, TIM_IT_CC2) == RESET){
		if(TIM_GetCounter(TIM5) >= 0xFFF0)
			return 0xFF;
	}
	return TIM_GetCapture2(TIM5);
//	return 1;
}

u16 Tpad_Scan(void){
	u16 i, max, temp;
	max = 0;
	for(i = 0; i < 10; i++){
		temp = Tpad_Get_Val();
		if(temp > max)
			max = temp;
	}
	return max;
}
