#include "rtc.h"
#include "stm32f10x.h"
#include "delay.h"
#include "stm32f10x_rtc.h"
#include "lcd.h"

const u8 mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};

u8 RTC_Init(void){
	u8 temp=0;
	delay_init();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//使能PWR和BKP外设时钟
	PWR_BackupAccessCmd(ENABLE);												//使能后备寄存器访问
	if (BKP_ReadBackupRegister(BKP_DR1) != 0x0830){								//从指定的后备寄存器中读出数据:读出了与写入的指定数据不相乎
		BKP_DeInit();															//复位备份区域 	
		RCC_LSEConfig(RCC_LSE_ON);												//设置外部低速晶振(LSE),使用外设低速晶振
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET && temp < 250){		//检查指定的RCC标志位设置与否,等待低速晶振就绪
			temp++;
			delay_ms(10);
		}
		if(temp>=250){
			LCD_ShowString(116, 766, 364, 24, 24, "RTC_Init ERROR",BLACK,YELLOW);
			delay_ms(1000);
			return 0;															//初始化时钟失败,晶振有问题
		}
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);									//设置RTC时钟(RTCCLK),选择LSE作为RTC时钟
		RCC_RTCCLKCmd(ENABLE);													//使能RTC时钟
		RTC_WaitForLastTask();													//等待最近一次对RTC寄存器的写操作完成
		RTC_WaitForSynchro();													//等待RTC寄存器同步
		RTC_ITConfig(RTC_IT_SEC, ENABLE);										//使能RTC秒中断
		RTC_WaitForLastTask();													//等待最近一次对RTC寄存器的写操作完成
		RTC_EnterConfigMode();													//允许配置
		RTC_SetPrescaler(32767); 												//设置RTC预分频的值
		RTC_WaitForLastTask();													//等待最近一次对RTC寄存器的写操作完成
		RTC_Set(2021,8,30,22,16,00);  											//设置时间
		RTC_ExitConfigMode(); 													//退出配置模式
		BKP_WriteBackupRegister(BKP_DR1, 0X0830);								//向指定的后备寄存器中写入用户程序数据
	}
	else{																		//系统继续计时
		RTC_WaitForSynchro();													//等待最近一次对RTC寄存器的写操作完成
		RTC_ITConfig(RTC_IT_SEC, ENABLE);										//使能RTC秒中断
		RTC_WaitForLastTask();													//等待最近一次对RTC寄存器的写操作完成
	}
	RTC_NVIC_Config();								//RCT中断分组设置		    				     
	RTC_Get();										//更新时间
	LCD_ShowString(400,10,80,16,16,"    -  -  ",BLACK,YELLOW);
	LCD_ShowString(400,26,80,16,16,"  :  :  ",BLACK,YELLOW);
	LCD_ShowString(116, 766, 364, 24, 24, "RTC_Init DONE",BLACK,YELLOW);
	return 1; //ok
}

u8 RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec){
	u16 t;
	u32 seccount=0;
	if(syear<2000||syear>2099)
		return 0;
	for(t = 2000; t < syear; t++){								//把所有年份的秒钟相加
		if(Is_Leap_Year(t))
			seccount += 31622400;								//闰年的秒钟数
		else seccount += 31536000;			  					//平年的秒钟数
	}
	smon -= 1;
	for(t = 0; t < smon; t++){	   								//把前面月份的秒钟数相加
		seccount += (u32)mon_table[t]*86400;					//月份秒钟数相加
		if(Is_Leap_Year(syear) && t==1)
			seccount+=86400;									//闰年2月份增加一天的秒钟数	   
	}
	seccount += (u32)(sday-1)*86400;							//把前面日期的秒钟数相加
	seccount += (u32)hour*3600;									//小时秒钟数
    seccount += (u32)min*60;	 								//分钟秒钟数
	seccount += sec;											//最后的秒钟加上去

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);		//使能PWR和BKP外设时钟  
	PWR_BackupAccessCmd(ENABLE);													//使能RTC和后备寄存器访问 
	RTC_SetCounter(seccount);														//设置RTC计数器的值

	RTC_WaitForLastTask();										//等待最近一次对RTC寄存器的写操作完成  	
	return 0;	    
}


u8 Is_Leap_Year(u16 year){			  
	if(year%4==0){ 								//必须能被4整除
		if(year%100==0){
			if(year%400==0)
				return 1;						//如果以00结尾,还要能被400整除 	   
			else return 0;
		}
		else return 1;
	}
	else return 0;
}

static void RTC_NVIC_Config(void){
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;					//RTC全局中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		//先占优先级1位,从优先级3位
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;				//先占优先级0位,从优先级4位
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//使能该通道中断
	NVIC_Init(&NVIC_InitStructure);									//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}

u8 RTC_Get(void){
	static u16 daycnt = 0;
	u32 timecount = 0; 
	u32 temp = 0;
	u16 temp1 = 0;	  
    timecount = RTC_GetCounter();
 	temp = timecount/86400;   										//得到天数(秒钟数对应的)
	if(daycnt != temp){												//超过一天了
		daycnt = temp;
		temp1 = 2000;	  											//从2000年开始
		while(temp >= 365){				 
			if(Is_Leap_Year(temp1)){								//是闰年
				if(temp >= 366)
					temp -= 366;									//闰年的秒钟数
				else{
					temp1++;//******************************************异议						
					break;
				}
			}
			else
				temp -= 365;	  									//平年 
			temp1++;  
		}
		calendar.w_year = temp1;									//得到年份
		temp1=0;
		while(temp >= 28){											//超过了一个月
			if(Is_Leap_Year(calendar.w_year) && temp1 == 1){		//当年是不是闰年/2月份
				if(temp>=29)
					temp-=29;										//闰年的秒钟数
				else break;
			}
			else{
				if(temp >= mon_table[temp1])
					temp -= mon_table[temp1];						//平年
				else break;
			}
			temp1++;  
		}
		calendar.w_month = temp1+1;									//得到月份
		calendar.w_date = temp+1;  									//得到日期 
	}
	temp = timecount%86400;     									//得到秒钟数   	   
	calendar.hour = temp / 3600;     								//小时
	calendar.min = (temp % 3600) / 60; 								//分钟	
	calendar.sec = (temp % 3600) % 60; 								//秒钟
	return 0;
}

void RTC_IRQHandler(void){
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET){						//秒钟中断
		RTC_Get();													//更新时间
		LCD_ShowNum(400,10,calendar.w_year,4,16,BLACK,YELLOW);
		LCD_ShowNum(440,10,calendar.w_month,2,16,BLACK,YELLOW);
		LCD_ShowNum(464,10,calendar.w_date,2,16,BLACK,YELLOW);
		LCD_ShowNum(400,26,calendar.hour,2,16,BLACK,YELLOW);									  
		LCD_ShowNum(424,26,calendar.min,2,16,BLACK,YELLOW);									  
		LCD_ShowNum(448,26,calendar.sec,2,16,BLACK,YELLOW);
 	}
	if(RTC_GetITStatus(RTC_IT_ALR)!= RESET){						//闹钟中断
		RTC_ClearITPendingBit(RTC_IT_ALR);							//清闹钟中断
  	}
	RTC_ClearITPendingBit(RTC_IT_SEC|RTC_IT_OW);		//清闹钟中断
	RTC_WaitForLastTask();	  	    						 	   	 
}
