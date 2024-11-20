#include "GY30.h"
#include "iic.h"
#include "delay.h"

u8 GY30_Init(u8 addr, u8 mode){
	if(addr != 0x46 && addr != 0xB8)
		return 1;
	if(mode != 0x20 && mode != 0x21 && mode != 0x23 && mode != 0x10 && mode != 0x11 && mode != 0x13)
		return 2;
	IIC_Start();
	IIC_Send(addr);
	IIC_Send(GY30_Power_On);
	IIC_Stop();
	IIC_Start();
	IIC_Send(addr);
	IIC_Send(mode);
	IIC_Stop();
	delay_ms(180);
	return 3;
}

u16 GY30_Get_Data(u8 addr){
	u8 H_Data, L_Data;
	u16 num;
	num = 0;
	if(addr != 0x46 && addr != 0xB8)
		return 0xFFFF;
	IIC_Start();
	IIC_Send(addr+1);
	H_Data = IIC_Read();
	L_Data = IIC_Read();
	IIC_Stop();
	num = H_Data;
	num <<= 8;
	num += L_Data;
	return num;
}
