#include "ST_Include.h"

//OSC = 8MHz. System has already initialized HSE  to 168MHz(SYSCLK) .Look  "system_stm32F4xx.c" for further info. 
//APB1 42M  APB2 84M   AHB 168M
//pwm对应的TIM的输出引脚有好多种组合 具体用到直接进pwm.c里面修改对应的io配置
//flash 写进去 因为必须要擦除整个扇区  后面几个扇区都是128k的  擦着贼慢。。。要整整1s。。。还是想想办法用eeprom吧  我这种数据量小擦写频繁的 不合适用片上flash。。



/*  外设使用AHB  APB1 APB2 在rcc.h里面查看 */
//STM32F4 很多外设的时钟来源，即两个总线桥： APB1 和 APB2，其中 APB1是低速总线（最高 42Mhz），APB2 是高速总线（最高 84Mhz）。
/*另外*///定时器 /*部分，如果所在总线（ APB1/APB2）的分频系数为 1，那么就不倍频，如果不为 1（比如 2/4/8/16），那么就会 2 倍频后，作为定时器时钟输入。
//简单点说，举个APB1的例子，系统时钟是168Mhz,APB1分频系数为4（system_stm32f4xx.c配置），
//则APB1速度为42Mhz,但是挂靠在该总线上的定时器3，由于分频系数4而不是1，因此定时器输入频率为42Mhz x 2 =84 Mhz*/
u32 now,time,time1;
u8 ptr[255]={0,0,0};

u8 flag=0;
int main(void)
{
	ST_SysTick_Configuration();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
    //ST_SerialCom_Init(ST_USART1,460800);
	ST_LED_Init();
	//ST_ADC_Init(AD_CH13);
	//ST_USB_VCP_Init();
	//ST_DAC_Init(DA_CH1);//开了输出缓存  有一定的带载能力 （？）用万用表测量没问题  用自带ad测试有问题 时好时坏 原因不明// 不开输出缓存adc通道0读取电压值不正常  原因未知   
	//ST_TIM3_PWM_Init(5000,PWM_Polarity_Low);//频率5khz  比较输出极性低 //led灯低电平亮 输出的是低电平  
	//ST_TIM5_Timer_Init(4999,8399);	//84M时钟    84,000,000/8400=10,000       10K count/1s    5k=0.5s   
	//ST_FLASH_Write(FLASH_SAVE_ADDR,(u32*)ST_FlashValue,SIZE);//贼慢
//	ST_NRF24L01_Init();  //硬件SPI  速度好像比软件模拟spi快得多的样子（？？)
//	while(ST_NRF24L01_Check());
//	ST_NRF24L01_RX_Mode();
    
  while(1)
	{
        static unsigned char i=0;
        i++;
        
        time++;
		LED0=!LED0;//工作灯
		ST_Delay_ms(1000);
//    now=ST_GetSysTime_us();
//    for(int i=0;i<1000;i++)
//        printf("%c",ptr[i]);
//    time=ST_GetSysTime_us()-now;
//    now=ST_GetSysTime_us();
//    ST_USART1_Send(ptr ,255);
//    time1=ST_GetSysTime_us()-now;
		//usb_printf("usb_vcp_test\r\n");
	}
}


