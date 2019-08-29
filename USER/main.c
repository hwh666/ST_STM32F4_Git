#include "ST_Include.h"

//OSC = 8MHz. System has already initialized HSE  to 168MHz(SYSCLK) .Look  "system_stm32F4xx.c" for further info. 
//APB1 42M  APB2 84M   AHB 168M
//pwm��Ӧ��TIM����������кö������ �����õ�ֱ�ӽ�pwm.c�����޸Ķ�Ӧ��io����
//flash д��ȥ ��Ϊ����Ҫ������������  ���漸����������128k��  ��������������Ҫ����1s��������������취��eeprom��  ������������С��дƵ���� ��������Ƭ��flash����



/*  ����ʹ��AHB  APB1 APB2 ��rcc.h����鿴 */
//STM32F4 �ܶ������ʱ����Դ�������������ţ� APB1 �� APB2������ APB1�ǵ������ߣ���� 42Mhz����APB2 �Ǹ������ߣ���� 84Mhz����
/*����*///��ʱ�� /*���֣�����������ߣ� APB1/APB2���ķ�Ƶϵ��Ϊ 1����ô�Ͳ���Ƶ�������Ϊ 1������ 2/4/8/16������ô�ͻ� 2 ��Ƶ����Ϊ��ʱ��ʱ�����롣
//�򵥵�˵���ٸ�APB1�����ӣ�ϵͳʱ����168Mhz,APB1��Ƶϵ��Ϊ4��system_stm32f4xx.c���ã���
//��APB1�ٶ�Ϊ42Mhz,���ǹҿ��ڸ������ϵĶ�ʱ��3�����ڷ�Ƶϵ��4������1����˶�ʱ������Ƶ��Ϊ42Mhz x 2 =84 Mhz*/
u32 now,time,time1;
u8 ptr[255]={0,0,0};

u8 flag=0;
int main(void)
{
	ST_SysTick_Configuration();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
    //ST_SerialCom_Init(ST_USART1,460800);
	ST_LED_Init();
	//ST_ADC_Init(AD_CH13);
	//ST_USB_VCP_Init();
	//ST_DAC_Init(DA_CH1);//�����������  ��һ���Ĵ������� �����������ñ����û����  ���Դ�ad���������� ʱ��ʱ�� ԭ����// �����������adcͨ��0��ȡ��ѹֵ������  ԭ��δ֪   
	//ST_TIM3_PWM_Init(5000,PWM_Polarity_Low);//Ƶ��5khz  �Ƚ�������Ե� //led�Ƶ͵�ƽ�� ������ǵ͵�ƽ  
	//ST_TIM5_Timer_Init(4999,8399);	//84Mʱ��    84,000,000/8400=10,000       10K count/1s    5k=0.5s   
	//ST_FLASH_Write(FLASH_SAVE_ADDR,(u32*)ST_FlashValue,SIZE);//����
//	ST_NRF24L01_Init();  //Ӳ��SPI  �ٶȺ�������ģ��spi��ö�����ӣ�����)
//	while(ST_NRF24L01_Check());
//	ST_NRF24L01_RX_Mode();
    
  while(1)
	{
        static unsigned char i=0;
        i++;
        
        time++;
		LED0=!LED0;//������
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


