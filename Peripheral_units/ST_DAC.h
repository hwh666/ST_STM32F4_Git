#ifndef __DAC
#define __DAC
#include "ST_Include.h"
#define DA_CH1 1
#define DA_CH2 2
void ST_DAC_SetVol(float vol,u8 ch);
void ST_DAC_Init(u8 ch);
#endif

