#include "stm32f10x.h"
#include "uart.h"
#include "math.h"

void UART1_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//使能引脚时钟
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);							//初始化引脚
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);							//初始化引脚
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);		//使能串口时钟
	
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = (USART_Mode_Tx | USART_Mode_Rx);
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStruct);						//初始化串口
	USART_Cmd(USART1, ENABLE);									//使能串口
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);				//配置串口中断模式
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//配置中断优先级分组
	
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);								//初始化中断分组
}

void USART1_IRQHandler(){
	
}

void UART2_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//使能引脚时钟
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);							//初始化引脚
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);							//初始化引脚
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);		//使能串口时钟
	
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = (USART_Mode_Tx | USART_Mode_Rx);
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2, &USART_InitStruct);						//初始化串口
	USART_Cmd(USART2, ENABLE);									//使能串口
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);				//配置串口中断模式
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//配置中断优先级分组
	
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);								//初始化中断分组
}

void USART2_IRQHandler(){
	
}

void UART3_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//使能引脚时钟
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);							//初始化引脚
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);							//初始化引脚
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);		//使能串口时钟
	
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = (USART_Mode_Tx | USART_Mode_Rx);
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART3, &USART_InitStruct);						//初始化串口
	USART_Cmd(USART3, ENABLE);									//使能串口
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);				//配置串口中断模式
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//配置中断优先级分组
	
	NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);								//初始化中断分组
}

void USART3_IRQHandler(){
	
}

void UART4_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);		//使能引脚时钟
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);							//初始化引脚
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);							//初始化引脚
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);		//使能串口时钟
	
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = (USART_Mode_Tx | USART_Mode_Rx);
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(UART4, &USART_InitStruct);						//初始化串口
	USART_Cmd(UART4, ENABLE);									//使能串口
	
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);				//配置串口中断模式
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//配置中断优先级分组
	
	NVIC_InitStruct.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);								//初始化中断分组
}

void UART4_IRQHandler(){
	
}

void UART5_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);		//使能引脚时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);		//使能引脚时钟
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);							//初始化引脚
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStruct);							//初始化引脚
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);		//使能串口时钟
	
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = (USART_Mode_Tx | USART_Mode_Rx);
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(UART5, &USART_InitStruct);						//初始化串口
	USART_Cmd(UART5, ENABLE);									//使能串口
	
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);				//配置串口中断模式
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//配置中断优先级分组
	
	NVIC_InitStruct.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);								//初始化中断分组
}

void UART5_IRQHandler(){
	
}

void Send_Num(USART_TypeDef* USARTx, u32 num){
	u8 i, flag;
	u32 temp;
	flag = 0;
	for(i=0; i<10; i++){
		temp = (num / pow(10,9-i));
		temp %= 10;
		if((temp != 0)||(flag == 1)||(i == 9)){
			flag = 1;
			Send_Data(USARTx, (temp + 0x30));
		}
		if((i%3 == 0)&&(flag == 1)&&(i != 9))
			Send_Data(USARTx, ' ');
	}
}

void Send_Data(USART_TypeDef* USARTx, u16 Data){
	USART_SendData(USARTx, Data);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
}

void Send_Str(USART_TypeDef* USARTx, u8 *Str){
	u8 i;
	for(i = 0; Str[i] != '\0'; i++)
			Send_Data(USARTx, Str[i]);
}
