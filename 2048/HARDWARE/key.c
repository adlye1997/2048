#include "stm32f10x.h"
#include "key.h"
#include "delay.h"

void KEY0_1_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	//使能引脚时钟
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = (GPIO_Pin_4 | GPIO_Pin_3);
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStruct);						//初始化引脚
}

void KEY_UP_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能引脚时钟
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);						//初始化引脚
}

void KEY_Init(void){
	KEY0_1_Init();
	KEY_UP_Init();
}

u8 KEY_Scan(u8 mode){//1 = 允许连续按	0 = 不允许连续按
	static u8 key = 0;
	if((GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 0)||(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 0)||(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1)){
		delay_ms(10);
		if(mode == 0 && key != 0)
			return 3;
		else if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 0){
			key++;
			return 0;
		}
		else if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 0){
			key++;
			return 1;
		}
		else if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1){
			key++;
			return 2;
		}
	}
	else
		key = 0;
	return 3;
}//0 = KEY0  1 = KEY1  2 = KEY_UP  3 = None




