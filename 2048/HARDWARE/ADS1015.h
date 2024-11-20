#ifndef __ADS1015_H
#define __ADS1015_H
#include "stm32f10x.h"

#define ADS1015_REG_POINTER_MASK 0x03
#define ADS1015_Conversion_Register 0x00
#define ADS1015_Config_Register 0x01
#define ADS1015_Lo_thresh_Register 0x02
#define ADS1015_Hi_thresh_Register 0x03
#define ADS1015_L_Slaveaddr 0x90
#define ADS1015_H_Slaveaddr 0x92
#define ADS1015_L_Slaveaddr_Write 0x90
#define ADS1015_L_Slaveaddr_Read 0x91
#define ADS1015_H_Slaveaddr_Write 0x92
#define ADS1015_H_Slaveaddr_Read 0x93

void ADS1015_Init(void);
u16 ADS1015_Get_Data(void);
u16 ADS1015_Get_Register_Data(u8 Register_addr);
void ADS1015_Send_Register_Data(u8 Register_addr, u8 H_Dat, u8 L_Dat);
void ADS1015_Conversation(u16 Dat);

#endif
