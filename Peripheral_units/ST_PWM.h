#ifndef __PWM
#define __PWM
#include "ST_Include.h"
#define PWM_Polarity_High  1
#define PWM_Polarity_Low  0

void ST_TIM2_PWM_Init(u16 freq,u8 mode);
void ST_TIM3_PWM_Init(u16 freq,u8 mode);
void ST_TIM4_PWM_Init(u16 freq,u8 mode);
void ST_TIM5_PWM_Init(u16 freq,u8 mode);

void ST_PWM2_Set(u16 CH1_Value,u16 CH2_Value,u16 CH3_Value,u16 CH4_Value);
void ST_PWM3_Set(u16 CH1_Value,u16 CH2_Value,u16 CH3_Value,u16 CH4_Value);
void ST_PWM4_Set(u16 CH1_Value,u16 CH2_Value,u16 CH3_Value,u16 CH4_Value);
void ST_PWM5_Set(u16 CH1_Value,u16 CH2_Value,u16 CH3_Value,u16 CH4_Value);
#endif

