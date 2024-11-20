#ifndef __HC_SR04_H
#define __HC_SR04_H

#include "sys.h"

void HCSR04_Init(void);
void HCSR04_Power_On(void);
u32 HCSR04_Con(u32 time);
void HCSR04_Work(void);






#endif

