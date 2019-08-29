#include "ST_delay.h"
#include "ST_IOport.h"

volatile uint32_t sysTickUptime = 0;

#define TICK_PER_SECOND 1000 
#define TICK_US	(1000000/TICK_PER_SECOND)

void  ST_SysTick_Configuration(void)              //8M¾§Õñ
{
	RCC_ClocksTypeDef  rcc_clocks;
	uint32_t         cnts;

	RCC_GetClocksFreq(&rcc_clocks);

	cnts = (uint32_t)rcc_clocks.HCLK_Frequency / TICK_PER_SECOND;
	cnts = cnts / 8;

	SysTick_Config(cnts);
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

uint32_t ST_GetSysTime_us(void) 
{
	register uint32_t ms;
	u32 value;
	ms = sysTickUptime;
	value = ms * TICK_US + (SysTick->LOAD - SysTick->VAL) * TICK_US / SysTick->LOAD;
	return value;
}

void ST_Delay_us(uint32_t us)
{
    uint32_t now = ST_GetSysTime_us();
    while (ST_GetSysTime_us() - now < us);
}

void ST_Delay_ms(uint32_t ms)
{
    while (ms--)
        ST_Delay_us(1000);
}




void SysTick_Handler(void)
{
	sysTickUptime++;
  
	if(sysTickUptime%1000==0)
  {
       //printf("LED0");
       LED1=!LED1;
  }
}

























