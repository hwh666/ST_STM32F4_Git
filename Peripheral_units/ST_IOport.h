#ifndef __io
#define __io 
#include "ST_Include.h"


#define LED0 PAout(6)
#define LED1 PAout(7)
#define LED PCout(9)
#define RGB_R PCout(6)
#define RGB_G PCout(7)
#define RGB_B PCout(8)
#define LED_ON  0
#define LED_OFF 1
void ST_LED_Init(void);



#endif

