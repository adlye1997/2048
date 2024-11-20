#include "iic.h"
#include "stm32f10x.h"
#include "delay.h"
void IIC_SDA_Out(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void IIC_SDA_In(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void IIC_SCL_Up(void){
	GPIO_SetBits(GPIOB, GPIO_Pin_6);
}

void IIC_SDA_Up(void){
	GPIO_SetBits(GPIOB, GPIO_Pin_7);
}

void IIC_SCL_Down(void){
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);
}

void IIC_SDA_Down(void){
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);
}

void IIC_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	
	delay_init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_6 | GPIO_Pin_7);
}

void IIC_Start(){
	IIC_SDA_Out();
	IIC_SDA_Up();
	IIC_SCL_Up();
	delay_us(5);
 	IIC_SDA_Down();//START:when CLK is high,DATA change form high to low 
	delay_us(5);
	IIC_SCL_Down();//钳住I2C总线，准备发送或接收数据
}

void IIC_Stop(void){
	IIC_SDA_Out();//sda线输出
	IIC_SCL_Up(); 
	IIC_SDA_Down();//STOP:when CLK is high DATA change form low to high
 	delay_us(5);
	IIC_SDA_Up();//发送I2C总线结束信号
	delay_us(5);					
}

u8 IIC_Send(u8 byte){
	u8 t;
	IIC_SDA_Out();
    IIC_SCL_Down();//拉低时钟开始数据传输
    for(t=0;t<8;t++){
		if((byte & 0x80) != 0)
			IIC_SDA_Up();
		else IIC_SDA_Down();
        IIC_SCL_Up();
		delay_us(5);
		IIC_SCL_Down();
		delay_us(5);
		byte <<= 1;
    }
	return IIC_Waitack();
}

u8 IIC_Read(void){
	u8 i;
	u8 receive = 0;
	IIC_SDA_In();
	for(i=0;i<8;i++){
		receive <<= 1;
		IIC_SCL_Up();
		delay_us(5);
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) != 0)
			receive |= 1;
		IIC_SCL_Down();
		delay_us(5);
	}
	IIC_Sendack(0);
	return receive;
}

u8 IIC_Waitack(void){
	u8 ack;
	IIC_SCL_Up();
	delay_us(5);
	ack = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7);;
	IIC_SCL_Down();
	delay_us(5);
	return ack;
}

void IIC_Sendack(u8 ack){
	IIC_SDA_Out();
	if(ack == 1)
		IIC_SDA_Up();
	else IIC_SDA_Down();
	IIC_SCL_Up();
	delay_us(5);
	IIC_SCL_Down();
	delay_us(5);
}

void IIC_Single_Send(u8 addr, u8 byte){
	IIC_Start();
	IIC_Send(addr);
	IIC_Send(byte);
	IIC_Stop();
}
