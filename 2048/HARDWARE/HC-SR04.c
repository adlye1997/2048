#include "HC-SR04.h"
#include "timer.h"
#include "stm32f10x.h"
#include "delay.h"

#define Trig PAout(5)

void HCSR04_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能引脚时钟
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);						//初始化引脚
	
	TIM3_CH1_Cap_Init(65535, 71);
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	GPIO_ResetBits(GPIOA, GPIO_Pin_6);
}

void HCSR04_Power_On(void){
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
	delay_us(20);
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
}

u32 HCSR04_Con(u32 time){
	time *= 170;
	time /= 10000;
	return time;
}
