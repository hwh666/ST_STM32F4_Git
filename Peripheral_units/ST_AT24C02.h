#ifndef __24C02
#define __24C02
#include "ST_Include.h"
void ST_AT24C02_Init(void);
u8 ST_AT24C02_ReadOneByte(u16 ReadAddr);
void ST_AT24C02_WriteOneByte(u16 WriteAddr,u8 DataToWrite);
void ST_AT24C02_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len);
u32 ST_AT24C02_ReadLenByte(u16 ReadAddr,u8 Len);
u8 ST_AT24C02_Check(void);
void ST_AT24C02_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead);
void ST_AT24C02_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite);
#endif

