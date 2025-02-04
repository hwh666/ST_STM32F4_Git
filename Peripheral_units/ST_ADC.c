#include "ST_ADC.h"
void ST_ADC_Init(u8 Adc_CH)
{
GPIO_InitTypeDef       GPIO_InitStructure;
ADC_CommonInitTypeDef  ADC_CommonInitStructure;
ADC_InitTypeDef        ADC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //使能ADC1时钟	
	if(Adc_CH<=7)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
		switch (Adc_CH)
        {
        	case 0:GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//PA0 通道0  下同
        		break;
        	case 1:GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
        		break;
			case 2:GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        		break;
			case 3:GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
        		break;
			case 4:GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
        		break;
			case 5:GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
        		break;
			case 6:GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
        		break;
			case 7:GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
        		break;
        	default:
        		break;
        }
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
		GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化  
	}
	else if((Adc_CH==8)||(Adc_CH==9))
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOB时钟
		if(Adc_CH==8)  
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;   //通道8
		else           
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;   //通道9
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
		GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化 
	}
	else if(Adc_CH>9)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOC时钟
		switch (Adc_CH)
        {
        	case 10:GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//PC0 通道10  下同
        		break;
        	case 11:GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
        		break;
			case 12:GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        		break;
			case 13:GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
        		break;
			case 14:GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
        		break;
			case 15:GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
        		break;
        	default:
        		break;
        }
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
		GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化  
	}
	
	
	
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1复位
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//复位结束
	
	
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMA失能
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div6;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
	ADC_CommonInit(&ADC_CommonInitStructure);//初始化

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12位模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//非扫描模式	
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//关闭连续转换
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐	
	ADC_InitStructure.ADC_NbrOfConversion = 1;//1个转换在规则序列中 也就是只转换规则序列1 
	ADC_Init(ADC1, &ADC_InitStructure);//ADC初始化


	ADC_Cmd(ADC1, ENABLE);//开启AD转换器
}
u16 ST_GetAdcValue(u8 ch)   
{
	  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_112Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
  
	ADC_SoftwareStartConv(ADC1);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}

