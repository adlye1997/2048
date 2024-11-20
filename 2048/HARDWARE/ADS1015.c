#include "ADS1015.h"
#include "iic.h"
#include "uart.h"
#include "math.h"

u16 ADS1015_Get_Data(){
	u16 F_Data;
	u8 H_Data, L_Data;
	IIC_Start();
	IIC_Send(ADS1015_L_Slaveaddr);
	IIC_Send(ADS1015_Conversion_Register);
	IIC_Stop();
	IIC_Start();
	IIC_Send(ADS1015_L_Slaveaddr+1);
	H_Data = IIC_Read();
	L_Data = IIC_Read();
	IIC_Stop();
	F_Data = H_Data;
	F_Data <<= 8;
	F_Data |= L_Data;
	return F_Data;
}

u16 ADS1015_Get_Register_Data(u8 Register_addr){
	u16 F_Data;
	u8 H_Data, L_Data;
	IIC_Start();
	IIC_Send(ADS1015_L_Slaveaddr);
	IIC_Send(Register_addr);
	IIC_Stop();
	IIC_Start();
	IIC_Send(ADS1015_L_Slaveaddr+1);
	H_Data = IIC_Read();
	L_Data = IIC_Read();
	IIC_Stop();
	F_Data = H_Data;
	F_Data <<= 8;
	F_Data |= L_Data;
	return F_Data;
}

void ADS1015_Send_Register_Data(u8 Register_addr, u8 H_Dat, u8 L_Dat){
	IIC_Start();
	IIC_Send(ADS1015_L_Slaveaddr);
	IIC_Send(Register_addr);
	IIC_Send(H_Dat);
	IIC_Send(L_Dat);
}

void ADS1015_Init(){
	ADS1015_Send_Register_Data(ADS1015_Config_Register, 0x84, 0x83);
}

void ADS1015_Conversation(u16 Dat){
	float C_Dat;
	if((Dat & 0x8000) == 0x8000)
		Send_Data(USART1, '-');
	else Send_Data(USART1, '+');
	Dat &= 0x7FFF;
	C_Dat = Dat / pow(2,15) * 2.048;
	Dat = C_Dat;
	Send_Num(USART1, Dat);
	Send_Data(USART1, '.');
	C_Dat *= 10;
	Dat = C_Dat;
	Send_Data(USART1, Dat%10+0x30);
	C_Dat *= 10;
	Dat = C_Dat;
	Send_Data(USART1, Dat%10+0x30);
	C_Dat *= 10;
	Dat = C_Dat;
	Send_Data(USART1, Dat%10+0x30);
	Send_Data(USART1, '\r');
	Send_Data(USART1, '\n');
}
