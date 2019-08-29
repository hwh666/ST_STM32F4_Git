#ifndef __ADC
#define __ADC
#include "ST_Include.h"
#define AD_CH0 0
#define AD_CH1 1
#define AD_CH2 2
#define AD_CH3 3
#define AD_CH4 4
#define AD_CH5 5
#define AD_CH6 6
#define AD_CH7 7
#define AD_CH8 8
#define AD_CH9 9 
#define AD_CH10 10
#define AD_CH11 11
#define AD_CH12 12
#define AD_CH13 13
#define AD_CH14 14
#define AD_CH15 15
void ST_ADC_Init(u8 Adc_CH);
u16 ST_GetAdcValue(u8 ch);
#endif


