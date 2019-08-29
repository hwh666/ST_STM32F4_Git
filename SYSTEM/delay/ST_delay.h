#ifndef __DELAY_H
#define __DELAY_H 			   
#include <sys.h>	  
//////////////////////////////////////////////////////////////////////////////////  
extern volatile uint32_t sysTickUptime;
////////////////////////////////////////////////////////////////////////////////// 	 
void  ST_SysTick_Configuration(void);
uint32_t ST_GetSysTime_us(void);
void ST_Delay_us(uint32_t us);
void ST_Delay_ms(uint32_t ms);
#endif





























