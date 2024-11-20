#ifndef __2048_H
#define __2048_H
#include "stm32f10x.h"
#include "lcd.h"
#include "sys.h"

/*
#define Color_Back 0x8451
#define Color_Box_Back 0xce78
#define Color_2 0xf79c
#define Color_4	0xeef9
#define Color_8 0xddd0
#define Color_16 0xf52c
#define Color_32 0xfbea
#define Color_64 0xf800
#define Color_128 0xeef0
#define Color_256 0xfea0
#define Color_512 0xfe04
#define Color_1024 0xfdc4
#define Color_2048 0xed61
#define Color_4096 0xffff
#define Num_1
*/
#define Creat_2_Point 0.9
#define Creat_4_Point 0.1
#define Empty_Point 0.1
#define Monotony_Point 2
#define Max_Point 0.3
#define Min_Point 0.7
#define Max_Times 3

typedef struct{
	u16 num[16];
	u16 point;
	u8 empty;
	u8 start_num;
	u8 start_box;
	u8 up;
	u8 down;
	u8 left;
	u8 right;
}Game_;
extern Game_ game_;





typedef struct{
	u8 empty;
	u16 sx;
	u16 ex;
	u16 sy;
	u16 ey;
	u16 num;
	u16 color;
	u8 flag;
}Box;
extern Box box[16];

typedef struct{
	u16 empty;
	u8 start_num;
	u8 start_box;
	u8 up;
	u8 down;
	u8 left;
	u8 right;
	u16 point;
}Game;
extern Game game;

typedef struct{
	u16 num[16];
	u8 flag[16];
	u16 max;
	u8 empty;
	u8 up;
	u8 down;
	u8 left;
	u8 right;
	u16 point;
}Point;







void g2048_Init(void);
void g2048_Refresh(void);
void g2048_Lcd_Refresh(void);
void g2048_Game(u8 Direction);//1=up,2=down,3=left,4=right
void g2048_Creat_And_Lcd_Refresh(void);
Point g2048_Point_Game(Point p, u8 Direction);//1=up,2=down,3=left,4=right
Point g2048_Point_Refresh(Point p);
float g2048_Get_Monotony_Point(Point p);
float g2048_Get_Empty_Point(Point p);
float g2048_Only_Get_Point(Point p);
u16 g2048_Get_Direction(Point p);
float g2048_Get_Point(Point p, u8 times);

void g2048_Direction_Judge_And_Game(void);
void g2048_Unauto_Creat(u8 cbox,u16 num);

#endif


















