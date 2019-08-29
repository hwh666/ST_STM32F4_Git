#ifndef __INCLUDE
#define __INCLUDE



#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "ST_USART.h"
#include "ST_delay.h"
#include "sys.h"
#include "ST_IOport.h"
#include "ST_Timer.h"
#include "ST_PWM.h"
#include "ST_ADC.h"
#include "ST_DAC.h"
#include "ST_Flash.h"
#include "ST_SPI.h"
#include "ST_NRF24L01.h"
#include "ST_SoftIIC.h"
#include "ST_USB.h"
#define ST_Printf_Use_USARTx  USART1  //USART1  USART2  USART3  UART4  UART5  //定义printf使用哪个串口  //对时间要求严格的应用别用printf或者sprintf  自己写相关函数  printf这东西贼浪费时间 

typedef struct  
{
	u16 Thr;
	u16 Yaw;
	u16 Rol;
	u16 Pit;
}ST_RC_Struct;

#endif

