#ifndef __TPAD_H
#define __TPAD_H

#include "sys.h"

void Tpad_Init(void);
u32 Tpad_Get_Base_Val(void);
u32 Tpad_Get_Val(void);
void Tpad_Reset(void);
u16 Tpad_Scan(void);


#endif
