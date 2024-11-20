#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h"

#define KEY0 PEin(4)

void KEY0_1_Init(void);
void KEY_UP_Init(void);
void KEY_Init(void);
u8 KEY_Scan(u8 mode);//mode == 1允许连续按	mode == 0不允许连续按
//0 = KEY0  1 = KEY1  2 = KEY_UP  3 = None
#endif
