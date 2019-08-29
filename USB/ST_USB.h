#ifndef __ST_USB
#define __ST_USB
#include "ST_Include.h"
#include "string.h"	
#include "stdarg.h"	
#include "usbd_cdc_vcp.h"
#define ST_USB_Connected   (bDeviceState==1)

void ST_USB_VCP_Init(void);
void usb_printf(char* fmt,...);
void ST_USB_Send(u8* buf ,u8 len);

void ST_USB_Receive(u8 data);
#endif



