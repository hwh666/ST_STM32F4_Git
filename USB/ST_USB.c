#include "ST_USB.h"
void ST_USB_VCP_Init(void)
{
	usbd_cdc_vcp_Init();
}

//usb���⴮��,printf ����
//ȷ��һ�η������ݲ���USB_USART_REC_LEN�ֽ�
u8  USART_PRINTF_Buffer[200];	//usb_printf���ͻ�����
void usb_printf(char* fmt,...)  
{  
	u16 i,j;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART_PRINTF_Buffer,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART_PRINTF_Buffer);//�˴η������ݵĳ���
	for(j=0;j<i;j++)//ѭ����������
	{
		VCP_DataTx(USART_PRINTF_Buffer[j]); 
	}
} 

void ST_USB_Send(u8* buf, u8 len)
{
	for(u8 i=0; i<len; i++)//ѭ����������
	{
		VCP_DataTx(buf[i]); 
	}
}
void ST_USB_Receive(u8 data)
{
	//if(data==0xaa)LED2=!LED2;
	//ST_Data_Receive_Prepare(u8 data);
}

