#include "basic.h"
#include "stm32f10x.h"

void Gpio_Init(){
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
}

void Gpio_Set(void){
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
}

void Gpio_Read(void){
	GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5);
}
