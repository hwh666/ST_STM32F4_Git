#include "ST_AT24C02.h"

void ST_AT24C02_Init(void)
{
	ST_SoftIIC_IO_Init();//ST_IIC初始化
}
//在AT24C02指定地址读出一个数据
//ReadAddr:开始读数的地址  
//返回值  :读到的数据
u8 ST_AT24C02_ReadOneByte(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
    ST_IIC_Start();  
	ST_IIC_SendByte(0XA0+((ReadAddr/256)<<1));   //发送器件地址0XA0,写数据 	   
	ST_IIC_WaitAsk(); 
    ST_IIC_SendByte(ReadAddr%256);   //发送低地址
	ST_IIC_WaitAsk();	    
	ST_IIC_Start();  	 	   
	ST_IIC_SendByte(0XA1);           //进入接收模式			   
	ST_IIC_WaitAsk();	 
    temp=ST_IIC_ReadByte(0);		   
    ST_IIC_Stop();//产生一个停止条件	    
	return temp;
}
//在AT24C02指定地址写入一个数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据
void ST_AT24C02_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{				   	  	    																 
    ST_IIC_Start();  
	ST_IIC_SendByte(0XA0+((WriteAddr/256)<<1));   //发送器件地址0XA0,写数据 	 
	ST_IIC_WaitAsk();	   
    ST_IIC_SendByte(WriteAddr%256);   //发送低地址
	ST_IIC_WaitAsk(); 	 										  		   
	ST_IIC_SendByte(DataToWrite);     //发送字节							   
	ST_IIC_WaitAsk();  		    	   
    ST_IIC_Stop();//产生一个停止条件 
	ST_Delay_ms(10);	 
}
//在AT24C02里面的指定地址开始写入长度为Len的数据
//该函数用于写入16bit或者32bit的数据.
//WriteAddr  :开始写入的地址  
//DataToWrite:数据数组首地址
//Len        :要写入数据的长度2,4
void ST_AT24C02_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
{  	
	u8 t;
	for(t=0;t<Len;t++)
	{
		ST_AT24C02_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

//在AT24C02里面的指定地址开始读出长度为Len的数据
//该函数用于读出16bit或者32bit的数据.
//ReadAddr   :开始读出的地址 
//返回值     :数据
//Len        :要读出数据的长度2,4
u32 ST_AT24C02_ReadLenByte(u16 ReadAddr,u8 Len)
{  	
	u8 t;
	u32 temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=ST_AT24C02_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}
//检查AT24C02是否正常
//这里用了24XX的最后一个地址(255)来存储标志字.
//如果用其他24C系列,这个地址要修改
//返回1:检测失败
//返回0:检测成功
u8 ST_AT24C02_Check(void)
{
	u8 temp;
	temp=ST_AT24C02_ReadOneByte(255);//避免每次开机都写AT24C02			   
	if(temp==0X55)return 0;		   
	else//排除第一次初始化的情况
	{
		ST_AT24C02_WriteOneByte(255,0X55);
	    temp=ST_AT24C02_ReadOneByte(255);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

//在AT24C02里面的指定地址开始读出指定个数的数据
//ReadAddr :开始读出的地址 对24c02为0~255
//pBuffer  :数据数组首地址
//NumToRead:要读出数据的个数
void ST_AT24C02_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=ST_AT24C02_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  
//在AT24C02里面的指定地址开始写入指定个数的数据
//WriteAddr :开始写入的地址 对24c02为0~255
//pBuffer   :数据数组首地址
//NumToWrite:要写入数据的个数
void ST_AT24C02_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		ST_AT24C02_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}
