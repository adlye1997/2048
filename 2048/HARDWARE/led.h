#ifndef __LED_H
#define __LED_H

#include "sys.h"

#define LED0 PBout(5)
#define LED1 PEout(5)

void LED0_Init(void);
void LED1_Init(void);
void LED_Init(void);
void LED0_On(void);
void LED1_On(void);
void LED0_Off(void);
void LED1_Off(void);

#endif
