#include "stm32f10x.h"
#include "delay.h"
#include "lcd.h"
#include "sys.h"
#include "2048.h"
#include "uart.h"
#include "rtc.h"
#include "uart.h"
#include "key.h"

#define DEBUG 1

_calendar_obj calendar;

int main(void){
	u8 i, j;
	Point p;
	delay_init();
	delay_ms(100);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LCD_Init();
	RTC_Init();
	g2048_Init();
	while(1){
		for(i=0;i<16;i++){
			p.num[i] = box[i].num;
		}
		p.point = game.point;
		p = g2048_Point_Refresh(p);
		j = g2048_Get_Direction(p);
		g2048_Game(j);
		g2048_Refresh();
		g2048_Creat_And_Lcd_Refresh();
	}
}

























