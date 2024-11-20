#ifndef __UART_H
#define __UART_H

#include "stm32f10x.h"

void UART1_Init(void);
void UART2_Init(void);
void UART3_Init(void);
void UART4_Init(void);
void UART5_Init(void);
void Send_Num(USART_TypeDef* USARTx, u32 num);
void Send_Data(USART_TypeDef* USARTx, u16 Data);
void Send_Str(USART_TypeDef* USARTx, u8 *Str);

#endif
