#ifndef __TIMER
#define __TIMER
#include "ST_Include.h"
void ST_TIM2_Timer_Init(u16 arr,u16 psc);
void ST_TIM3_Timer_Init(u16 arr,u16 psc);
void ST_TIM4_Timer_Init(u16 arr,u16 psc);
void ST_TIM5_Timer_Init(u16 arr,u16 psc);

void ST_TIM2_IRQ(void);
void ST_TIM3_IRQ(void);
void ST_TIM4_IRQ(void);
void ST_TIM5_IRQ(void);


#endif

