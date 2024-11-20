#ifndef __IIC_H
#define __IIC_H
#include "stm32f10x.h"

void IIC_SDA_Out(void);
void IIC_SDA_In(void);
void IIC_SCL_Up(void);
void IIC_SDA_Up(void);
void IIC_SCL_Down(void);
void IIC_SDA_Down(void);
void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
u8 IIC_Send(u8 byte);
u8 IIC_Read(void);
u8 IIC_Waitack(void);
void IIC_Sendack(u8 ack);
void IIC_Single_Send(u8 addr, u8 byte);


#endif
