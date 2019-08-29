#ifndef __IIC
#define __IIC
#include "ST_Include.h"
extern volatile u8 IIC_FastMode;
#define SCL_H         IIC_GPIO->BSRRL = IIC_SCL_PIN
#define SCL_L         IIC_GPIO->BSRRH = IIC_SCL_PIN
#define SDA_H         IIC_GPIO->BSRRL = IIC_SDA_PIN
#define SDA_L         IIC_GPIO->BSRRH = IIC_SDA_PIN
#define SCL_read      IIC_GPIO->IDR  & IIC_SCL_PIN
#define SDA_read      IIC_GPIO->IDR  & IIC_SDA_PIN

#define RCC_IIC RCC_AHB1Periph_GPIOB
#define IIC_GPIO  GPIOB
#define IIC_SCL_PIN GPIO_Pin_10
#define IIC_SDA_PIN GPIO_Pin_11

void ST_SoftIIC_IO_Init(void);

u8 ST_IIC_Start(void);
void ST_IIC_Stop(void);
void ST_IIC_Ask(void);
void ST_IIC_NoAsk(void);
u8 ST_IIC_WaitAsk(void);

void ST_IIC_SendByte(u8 SendByte);
u8 ST_IIC_ReadByte(u8 ask);
u8 ST_IIC_Write_1Byte(u8 SlaveAddress,u8 REG_Address,u8 REG_data);
u8 ST_IIC_Read_1Byte(u8 SlaveAddress,u8 REG_Address,u8 *REG_data);
u8 ST_IIC_Write_nByte(u8 SlaveAddress, u8 REG_Address, u8 len, u8 *buf);
u8 ST_IIC_Read_nByte(u8 SlaveAddress, u8 REG_Address, u8 len, u8 *buf);
#endif

