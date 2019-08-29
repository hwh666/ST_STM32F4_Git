#include "ST_DAC.h"
void ST_DAC_Init(u8 ch)
{  
GPIO_InitTypeDef  GPIO_InitStructure;
DAC_InitTypeDef DAC_InitType;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//使能DAC时钟
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
	
	DAC_InitType.DAC_Trigger=DAC_Trigger_None;	//不使用触发功能 TEN1=0
	DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//不使用波形发生
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//屏蔽、幅值设置
	DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//DAC1输出缓存打开 
	
	if(ch==1)	   
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
		GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
		DAC_Init(DAC_Channel_1,&DAC_InitType);	 //初始化DAC通道1
		DAC_Cmd(DAC_Channel_1, ENABLE);  //使能DAC通道1	
        DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12位右对齐数据格式设置DAC值
	}
	else if(ch==2)	   
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
		GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
		DAC_Init(DAC_Channel_2,&DAC_InitType);	 //初始化DAC通道2
		DAC_Cmd(DAC_Channel_2, ENABLE);  //使能DAC通道1	
        DAC_SetChannel2Data(DAC_Align_12b_R, 0);  //12位右对齐数据格式设置DAC值
	}
}
//设置dac输出电压
void ST_DAC_SetVol(float vol,u8 ch)
{
	u16 temp;
	vol=vol*4096/3.31f;
	temp=(u16)vol;
	if(ch==1)DAC_SetChannel1Data(DAC_Align_12b_R,temp);
	else if(ch==2)DAC_SetChannel2Data(DAC_Align_12b_R,temp);
}

