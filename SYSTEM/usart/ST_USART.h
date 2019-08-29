#ifndef __USART_H
#define __USART_H
#include "ST_Include.h" 
//////////////////////////////////////////////////////////////////////////////////	 
#define ST_USART1  1 
#define ST_USART2  2 
#define ST_USART3  3 
#define ST_UART4   4 
#define ST_UART5   5 



void ST_SerialCom_Init(u8 num,u32 baud);


void ST_USART1_Init(u32 bound);
void ST_USART2_Init(u32 bound);
void ST_USART3_Init(u32 bound);
void ST_UART4_Init (u32 bound);
void ST_UART5_Init (u32 bound);

void ST_USART1_IRQ(void);
void ST_USART2_IRQ(void);
void ST_USART3_IRQ(void);
void ST_UART4_IRQ (void);
void ST_UART5_IRQ (void);

void ST_USART1_Send(unsigned char *DataToSend ,u8 data_num);
void ST_USART2_Send(unsigned char *DataToSend ,u8 data_num);
void ST_USART3_Send(unsigned char *DataToSend ,u8 data_num);
void ST_UART4_Send (unsigned char *DataToSend ,u8 data_num);
void ST_UART5_Send (unsigned char *DataToSend ,u8 data_num);
#endif


