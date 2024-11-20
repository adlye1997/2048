#ifndef __LCD_H
#define __LCD_H

#include "stm32f10x.h"

/*
PG12		FSMC_NE4		LCD_CS	0 == act
PG0			FSMC_A10		RS		0 == order	1 == data
PD5			FSMC_NWE		WR/CLK	write
PD4			FSMC_NOE		RD		read
PD14		FSMC_D0			DB1
PD15		FSMC_D1			DB2
PD0			FSMC_D2			DB3
PD1 		FSMC_D3			DB4
PE7			FSMC_D4			DB5
PE8			FSMC_D5			DB6
PE9			FSMC_D6			DB7
PE10		FSMC_D7			DB8
PE11		FSMC_D8			DB10
PE12		FSMC_D9			DB11
PE13		FSMC_D10		DB12
PE14		FSMC_D11		DB13
PE15		FSMC_D12		DB14
PD8			FSMC_D13		DB15
PD9			FSMC_D14		DB16
PD10		FSMC_D15		DB17
PB0			LCD_BL			BL		1 == light_on
PB2			T_MISO			MISO	NC
PF9			T_MOSI			MOSI	IIC_SDA
PF10		T_PEN			T_PEN	INT
PF11		T_CS			T_CS	RST
PB1			T_SCK			CLK		IIC_SCL
*/

#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F	//洋红色
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF	//蓝绿色
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色

#define Set_Drection_Order 0x3600
#define L_R_U_D 0x0000
#define L_R_D_U 0x0080
#define R_L_U_D 0x0040

typedef struct{
	u16 width;			//LCD 宽度								480
	u16 height;			//LCD 高度								800
	u8  dir;			//横屏还是竖屏控制：0，竖屏；1，横屏。	0
	u16	wramcmd;		//开始写gram指令						0X2C00
	u16  setxcmd;		//设置x坐标指令							0X2A00
	u16  setycmd;		//设置y坐标指令							0X2B00
}_lcd_dev;

extern _lcd_dev lcddev;
extern u16 POINT_COLOR;	//默认黑色
extern u16 BACK_COLOR; 	//背景颜色.默认为白色

typedef struct{
	vu16 LCD_REG;
	vu16 LCD_RAM;
} LCD_TypeDef;

#define LCD_BASE        ((u32)(0x6C000000 | 0x000007FE))
#define LCD             ((LCD_TypeDef *) LCD_BASE)

void LCD_Init(void);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_Clear(u16 Color);
void LCD_SetCursor(u16 Xpos, u16 Ypos);
void LCD_ShowChar(u16 x, u16 y, u8 num, u8 size, u8 mode);
void LCD_WriteRAM_Prepare(void);
void LCD_ShowChar(u16 x, u16 y, u8 num, u8 size, u8 mode);
void g2048_ShowChar(u16 x,u16 y,u32 num,u8 len,u16 point_color,u16 back_color);
void LCD_Fast_DrawPoint(u16 x, u16 y, u16 color);
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p,u16 point_color,u16 back_color);
void LCD_Color_Fill(u16 sx,u16 ex,u16 sy,u16 ey,u16 color);
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size,u16 point_color,u16 back_color);

void LCD_WR_REG(u16 LCD_Reg);
void LCD_WR_RAM(u16 LCD_RAM);
void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RAM);
u16 LCD_ReadReg(u16 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);
u32 LCD_Pow(u8 m,u8 n);
#endif
























