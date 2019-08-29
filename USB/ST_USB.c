#include "ST_USB.h"
void ST_USB_VCP_Init(void)
{
	usbd_cdc_vcp_Init();
}

//usb虚拟串口,printf 函数
//确保一次发送数据不超USB_USART_REC_LEN字节
u8  USART_PRINTF_Buffer[200];	//usb_printf发送缓冲区
void usb_printf(char* fmt,...)  
{  
	u16 i,j;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART_PRINTF_Buffer,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART_PRINTF_Buffer);//此次发送数据的长度
	for(j=0;j<i;j++)//循环发送数据
	{
		VCP_DataTx(USART_PRINTF_Buffer[j]); 
	}
} 

void ST_USB_Send(u8* buf, u8 len)
{
	for(u8 i=0; i<len; i++)//循环发送数据
	{
		VCP_DataTx(buf[i]); 
	}
}
void ST_USB_Receive(u8 data)
{
	//if(data==0xaa)LED2=!LED2;
	//ST_Data_Receive_Prepare(u8 data);
}

