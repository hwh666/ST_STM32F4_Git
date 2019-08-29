#include "ST_SoftIIC.h"
 /* ��IOģ��IICͨ��*/
volatile u8 IIC_FastMode;

void ST_IIC_delay()
{ 
__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();
	if(!IIC_FastMode)
	{
	u8 i = 15;
		while(i--);
	}
}
void ST_SoftIIC_IO_Init()
{
 GPIO_InitTypeDef  GPIO_InitStructure; 
	RCC_AHB1PeriphClockCmd(RCC_IIC , ENABLE );
	GPIO_InitStructure.GPIO_Pin =  IIC_SDA_PIN | IIC_SCL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(IIC_GPIO, &GPIO_InitStructure);	
}

u8 ST_IIC_Start()
{
	SDA_H;
	SCL_H;
	ST_IIC_delay();
	if(!SDA_read)return 0;	//SDA��Ϊ�͵�ƽ������æ,�˳�
	SDA_L;
	ST_IIC_delay();
	if(SDA_read) return 0;	//SDA��Ϊ�ߵ�ƽ�����߳���,�˳�
	SDA_L;
	ST_IIC_delay();
	return 1;	

}

void ST_IIC_Stop()
{
	SCL_L;
	ST_IIC_delay();
	SDA_L;
	ST_IIC_delay();
	SCL_H;
	ST_IIC_delay();
	SDA_H;
	ST_IIC_delay();
}

void ST_IIC_Ask()
{
	SCL_L;
	ST_IIC_delay();
	SDA_L;
	ST_IIC_delay();
	SCL_H;
	ST_IIC_delay();
	SCL_L;
	ST_IIC_delay();
}

void ST_IIC_NoAsk()
{
	SCL_L;
	ST_IIC_delay();
	SDA_H;
	ST_IIC_delay();
	SCL_H;
	ST_IIC_delay();
	SCL_L;
	ST_IIC_delay();
}

u8 ST_IIC_WaitAsk(void) 	 //����Ϊ:=1��ASK,=0��ASK
{
  u8 ErrTime = 0;
	SCL_L;
	ST_IIC_delay();
	SDA_H;			
	ST_IIC_delay();
	SCL_H;
	ST_IIC_delay();
	while(SDA_read)
	{
		ErrTime++;
		if(ErrTime>50)
		{
			ST_IIC_Stop();
			return 1;
		}
	}
	SCL_L;
	ST_IIC_delay();
	return 0;
}

void ST_IIC_SendByte(u8 SendByte) //���ݴӸ�λ����λ//
{
    u8 i=8;
    while(i--)
    {
        SCL_L;
        ST_IIC_delay();
      if(SendByte&0x80)
        SDA_H;  
      else 
        SDA_L;   
        SendByte<<=1;
        ST_IIC_delay();
		SCL_H;
		ST_IIC_delay();
    }
    SCL_L;
}  

//��1���ֽڣ�ack=1ʱ������ACK��ack=0������NACK
u8 ST_IIC_ReadByte(u8 ask)  //���ݴӸ�λ����λ//
{ 
    u8 i=8;
    u8 ReceiveByte=0;

    SDA_H;				
    while(i--)
    {
      ReceiveByte<<=1;      
      SCL_L;
      ST_IIC_delay();
			SCL_H;
      ST_IIC_delay();	
      if(SDA_read)
      {
        ReceiveByte|=0x01;
      }
    }
    SCL_L;

	if (ask)
		ST_IIC_Ask();
	else
		ST_IIC_NoAsk();  
    return ReceiveByte;
} 


// IICдһ���ֽ�����
u8 ST_IIC_Write_1Byte(u8 SlaveAddress,u8 REG_Address,u8 REG_data)
{
	ST_IIC_Start();
	ST_IIC_SendByte(SlaveAddress<<1);   
	if(ST_IIC_WaitAsk())
	{
		ST_IIC_Stop();
		return 1;
	}
	ST_IIC_SendByte(REG_Address);       
	ST_IIC_WaitAsk();	
	ST_IIC_SendByte(REG_data);
	ST_IIC_WaitAsk();   
	ST_IIC_Stop(); 
	return 0;
}

// IIC��1�ֽ�����
u8 ST_IIC_Read_1Byte(u8 SlaveAddress,u8 REG_Address,u8 *REG_data)
{      		
	ST_IIC_Start();
	ST_IIC_SendByte(SlaveAddress<<1); 
	if(ST_IIC_WaitAsk())
	{
		ST_IIC_Stop();
		return 1;
	}
	ST_IIC_SendByte(REG_Address);     
	ST_IIC_WaitAsk();
	ST_IIC_Start();
	ST_IIC_SendByte(SlaveAddress<<1 | 0x01);
	ST_IIC_WaitAsk();
	*REG_data= ST_IIC_ReadByte(0);
	ST_IIC_Stop();
	return 0;
}	

// IICдn�ֽ�����
u8 ST_IIC_Write_nByte(u8 SlaveAddress, u8 REG_Address, u8 len, u8 *buf)
{	
	ST_IIC_Start();
	ST_IIC_SendByte(SlaveAddress<<1); 
	if(ST_IIC_WaitAsk())
	{
		ST_IIC_Stop();
		return 1;
	}
	ST_IIC_SendByte(REG_Address); 
	ST_IIC_WaitAsk();
	while(len--) 
	{
		ST_IIC_SendByte(*buf++); 
		ST_IIC_WaitAsk();
	}
	ST_IIC_Stop();
	return 0;
}

// IIC��n�ֽ�����
u8 ST_IIC_Read_nByte(u8 SlaveAddress, u8 REG_Address, u8 len, u8 *buf)
{	
	ST_IIC_Start();
	ST_IIC_SendByte(SlaveAddress<<1); 
	if(ST_IIC_WaitAsk())
	{
		ST_IIC_Stop();
		return 1;
	}
	ST_IIC_SendByte(REG_Address); 
	ST_IIC_WaitAsk();
	
	ST_IIC_Start();
	ST_IIC_SendByte(SlaveAddress<<1 | 0x01); 
	ST_IIC_WaitAsk();
	while(len) 
	{
		if(len == 1)
		{
			*buf = ST_IIC_ReadByte(0);
		}
		else
		{
			*buf = ST_IIC_ReadByte(1);
		}
		buf++;
		len--;
	}
	ST_IIC_Stop();
	return 0;
}
