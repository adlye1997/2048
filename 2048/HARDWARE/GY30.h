#ifndef __GY30_H
#define __GY30_H
#include "stm32f10x.h"

#define GY30_Power_Down 0x00
#define GY30_Power_On 0x01
#define GY30_Reset 0x07
#define GY30_Continuously_H_Resolution_Mode 0x10 
//Start measurement at 1lx resolution. 		Measurement Time is typically 120ms.
#define GY30_Continuously_H_Resolution_Mode2 0x11
//Start measurement at 0.5lx resolution. 	Measurement Time is typically 120ms.
#define GY30_Continuously_L_Resolution_Mode 0x13
//Start measurement at 4lx resolution. 		Measurement Time is typically 16ms.
#define GY30_OneTime_H_Resolution_Mode 0x20
//Start measurement at 1lx resolution. 		Measurement Time is typically 120ms. 
//It is automatically set to Power Down mode after measurement.
#define GY30_OneTime_H_Resolution_Mode2 0x21
//Start measurement at 0.5lx resolution. 	Measurement Time is typically 120ms. 
//It is automatically set to Power Down mode after measurement.
#define GY30_OneTime_L_Resolution_Mode 0x23
//Start measurement at 4lx resolution. 		Measurement Time is typically 16ms. 
//It is automatically set to Power Down mode after measurement.
#define GY30_L_Slaveaddr 0x46
#define GY30_H_Slaveaddr 0xB8
#define GY30_L_Slaveaddr_Write 0x46
#define GY30_L_Slaveaddr_Read 0x47
#define GY30_H_Slaveaddr_Write 0xB8
#define GY30_H_Slaveaddr_Read 0xB9

u8 GY30_Init(u8 addr, u8 mode);
u16 GY30_Get_Data(u8 addr);

#endif
