#include "led.h"
#include "stm32f10x.h"

void LED0_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能引脚时钟
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);					//初始化引脚
	
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
}

void LED1_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	//使能引脚时钟
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStruct);					//初始化引脚
	
	GPIO_SetBits(GPIOE, GPIO_Pin_5);
}

void LED_Init(void){
	LED0_Init();
	LED1_Init();
}

void LED0_On(void){
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}

void LED1_On(void){
	GPIO_ResetBits(GPIOE, GPIO_Pin_5);
}

void LED0_Off(void){
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
}

void LED1_Off(void){
	GPIO_SetBits(GPIOE, GPIO_Pin_5);
}
