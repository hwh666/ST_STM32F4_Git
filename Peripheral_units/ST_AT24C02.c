#include "ST_AT24C02.h"

void ST_AT24C02_Init(void)
{
	ST_SoftIIC_IO_Init();//ST_IIC��ʼ��
}
//��AT24C02ָ����ַ����һ������
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
u8 ST_AT24C02_ReadOneByte(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
    ST_IIC_Start();  
	ST_IIC_SendByte(0XA0+((ReadAddr/256)<<1));   //����������ַ0XA0,д���� 	   
	ST_IIC_WaitAsk(); 
    ST_IIC_SendByte(ReadAddr%256);   //���͵͵�ַ
	ST_IIC_WaitAsk();	    
	ST_IIC_Start();  	 	   
	ST_IIC_SendByte(0XA1);           //�������ģʽ			   
	ST_IIC_WaitAsk();	 
    temp=ST_IIC_ReadByte(0);		   
    ST_IIC_Stop();//����һ��ֹͣ����	    
	return temp;
}
//��AT24C02ָ����ַд��һ������
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������
void ST_AT24C02_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{				   	  	    																 
    ST_IIC_Start();  
	ST_IIC_SendByte(0XA0+((WriteAddr/256)<<1));   //����������ַ0XA0,д���� 	 
	ST_IIC_WaitAsk();	   
    ST_IIC_SendByte(WriteAddr%256);   //���͵͵�ַ
	ST_IIC_WaitAsk(); 	 										  		   
	ST_IIC_SendByte(DataToWrite);     //�����ֽ�							   
	ST_IIC_WaitAsk();  		    	   
    ST_IIC_Stop();//����һ��ֹͣ���� 
	ST_Delay_ms(10);	 
}
//��AT24C02�����ָ����ַ��ʼд�볤��ΪLen������
//�ú�������д��16bit����32bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ
//Len        :Ҫд�����ݵĳ���2,4
void ST_AT24C02_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
{  	
	u8 t;
	for(t=0;t<Len;t++)
	{
		ST_AT24C02_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

//��AT24C02�����ָ����ַ��ʼ��������ΪLen������
//�ú������ڶ���16bit����32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����
//Len        :Ҫ�������ݵĳ���2,4
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
//���AT24C02�Ƿ�����
//��������24XX�����һ����ַ(255)���洢��־��.
//���������24Cϵ��,�����ַҪ�޸�
//����1:���ʧ��
//����0:���ɹ�
u8 ST_AT24C02_Check(void)
{
	u8 temp;
	temp=ST_AT24C02_ReadOneByte(255);//����ÿ�ο�����дAT24C02			   
	if(temp==0X55)return 0;		   
	else//�ų���һ�γ�ʼ�������
	{
		ST_AT24C02_WriteOneByte(255,0X55);
	    temp=ST_AT24C02_ReadOneByte(255);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

//��AT24C02�����ָ����ַ��ʼ����ָ������������
//ReadAddr :��ʼ�����ĵ�ַ ��24c02Ϊ0~255
//pBuffer  :���������׵�ַ
//NumToRead:Ҫ�������ݵĸ���
void ST_AT24C02_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=ST_AT24C02_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  
//��AT24C02�����ָ����ַ��ʼд��ָ������������
//WriteAddr :��ʼд��ĵ�ַ ��24c02Ϊ0~255
//pBuffer   :���������׵�ַ
//NumToWrite:Ҫд�����ݵĸ���
void ST_AT24C02_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		ST_AT24C02_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}
