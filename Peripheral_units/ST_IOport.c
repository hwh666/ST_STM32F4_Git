#include "ST_IOport.h"
/* use this  .c  file  for a led or a beep etc.operate io port directly. */
void ST_LED_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	LED0=LED_OFF;
    LED1=LED_OFF;
//	RGB_R=LED_OFF;
//	RGB_G=LED_OFF;
//	RGB_B=LED_OFF;
}



