#include "ST_NRF24L01.h"
const u8 TX_ADDRESS[TX_ADR_WIDTH]={0xFF,0xFF,0xFF,0xFF,0xFF}; //���͵�ַ
const u8 RX_ADDRESS[RX_ADR_WIDTH]={0xFF,0xFF,0xFF,0xFF,0xFF}; //���͵�ַ
u8 ST_NRF_RX_BUF[32];


void ST_NRF24L01_Init(void)
{  
GPIO_InitTypeDef  GPIO_InitStructure;


	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOB,Gʱ��
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOB, &GPIO_InitStructure);//

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOB, &GPIO_InitStructure);//

	ST_SPI2_Init();    		//��ʼ��SPI  
	
	NRF24L01_CE=0; 			//ʹ��24L01
	NRF24L01_CSN=1;			//SPIƬѡȡ��	 		 	 
}
u8 ST_NRF24L01_Check(void)
{
u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
u8 i; 	 
	ST_NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,buf,5);//д��5���ֽڵĵ�ַ.	
	ST_NRF24L01_Read_Buf(TX_ADDR,buf,5); //����д��ĵ�ַ  
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 1;//���24L01����	
	return 0;		 //��⵽24L01
}
//SPIд�Ĵ���
//reg:ָ���Ĵ�����ַ
//value:д���ֵ
u8 ST_NRF24L01_Write_Reg(u8 reg,u8 value)
{
u8 status;	
	NRF24L01_CSN=0;                 //ʹ��SPI����
	status =ST_SPI2_ReadWriteByte(reg);//���ͼĴ����� 
	ST_SPI2_ReadWriteByte(value);      //д��Ĵ�����ֵ
	NRF24L01_CSN=1;                 //��ֹSPI����	   
	return(status);       			//����״ֵ̬
}
//��ȡSPI�Ĵ���ֵ
//reg:Ҫ���ļĴ���
u8 ST_NRF24L01_Read_Reg(u8 reg)
{
u8 reg_val;	    
	NRF24L01_CSN = 0;          //ʹ��SPI����		
	ST_SPI2_ReadWriteByte(reg);   //���ͼĴ�����
	reg_val=ST_SPI2_ReadWriteByte(0XFF);//��ȡ�Ĵ�������
	NRF24L01_CSN = 1;          //��ֹSPI����		    
	return(reg_val);           //����״ֵ̬
}	
//��ָ��λ�ö���ָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//len:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ 
u8 ST_NRF24L01_Read_Buf(u8 reg,u8 *pBuf,u8 len)
{
u8 status,u8_ctr;	       
	NRF24L01_CSN = 0;           //ʹ��SPI����
	status=ST_SPI2_ReadWriteByte(reg);//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬   	   
	for(u8_ctr=0;u8_ctr<len;u8_ctr++)pBuf[u8_ctr]=ST_SPI2_ReadWriteByte(0XFF);//��������
	NRF24L01_CSN=1;       //�ر�SPI����
	return status;        //���ض�����״ֵ̬
}
//��ָ��λ��дָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//len:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ
u8 ST_NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
{
u8 status,u8_ctr;	    
	NRF24L01_CSN = 0;          //ʹ��SPI����
	status = ST_SPI2_ReadWriteByte(reg);//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬
	for(u8_ctr=0; u8_ctr<len; u8_ctr++)ST_SPI2_ReadWriteByte(*pBuf++); //д������	 
	NRF24L01_CSN = 1;       //�ر�SPI����
	return status;          //���ض�����״ֵ̬
}	
//����NRF24L01����һ������
//txbuf:�����������׵�ַ
//����ֵ:�������״��
u8 ST_NRF24L01_TxPacket(u8 *txbuf)
{
u8 sta;  
	NRF24L01_CE=0;
    ST_NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//д���ݵ�TX BUF  32���ֽ�
 	NRF24L01_CE=1;//��������	   
	while(NRF24L01_IRQ!=0);//�ȴ��������
	sta=ST_NRF24L01_Read_Reg(STATUS);  //��ȡ״̬�Ĵ�����ֵ	   
	ST_NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //���TX_DS��MAX_RT�жϱ�־
	if(sta&MAX_TX)//�ﵽ����ط�����
	{
		ST_NRF24L01_Write_Reg(FLUSH_TX,0xff);//���TX FIFO�Ĵ��� 
		return MAX_TX; 
	}
	if(sta&TX_OK)//�������
	{
		return TX_OK;
	}
	return 0xff;//����ԭ����ʧ��
}
//����NRF24L01����һ������
//txbuf:�������ݴ洢�����׵�ַ
//����ֵ:0��������ɣ��������������
u8 ST_NRF24L01_RxPacket(u8 *rxbuf)
{
	u8 sta;		    							     
	sta=ST_NRF24L01_Read_Reg(STATUS);  //��ȡ״̬�Ĵ�����ֵ    	 
	ST_NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //���TX_DS��MAX_RT�жϱ�־
	if(sta&RX_OK)//���յ�����
	{
		ST_NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//��ȡ����
		ST_NRF24L01_Write_Reg(FLUSH_RX,0xff);//���RX FIFO�Ĵ��� 
		return 0; 
	}	   
	return 1;//û�յ��κ�����
}
//�ú�����ʼ��NRF24L01��RXģʽ
//����RX��ַ,дRX���ݿ��,ѡ��RFƵ��,�����ʺ�LNA HCURR
//��CE��ߺ�,������RXģʽ,�����Խ���������		   
void ST_NRF24L01_RX_Mode(void)
{
	NRF24L01_CE=0;	  
	ST_NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//дRX�ڵ��ַ
	ST_NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);    //ʹ��ͨ��0���Զ�Ӧ��    
	ST_NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);//ʹ��ͨ��0�Ľ��յ�ַ  	 
	ST_NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,0);	     //����RFͨ��Ƶ��		  
	ST_NRF24L01_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//ѡ��ͨ��0����Ч���ݿ�� 	    
	ST_NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);//����TX�������,0db����,2Mbps,���������濪��   
	ST_NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0f);//���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ 
	NRF24L01_CE = 1; //CEΪ��,�������ģʽ 
	ST_Delay_us(10);
}						 
//�ú�����ʼ��NRF24L01��TXģʽ
//����TX��ַ,дTX���ݿ��,����RX�Զ�Ӧ��ĵ�ַ,���TX��������,ѡ��RFƵ��,�����ʺ�LNA HCURR
//PWR_UP,CRCʹ��
//��CE��ߺ�,������RXģʽ,�����Խ���������		   
//CEΪ�ߴ���10us,����������.	 
void ST_NRF24L01_TX_Mode(void)
{														 
	NRF24L01_CE=0;	    
	ST_NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);//дTX�ڵ��ַ 
	ST_NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK
	ST_NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);     //ʹ��ͨ��0���Զ�Ӧ��    
	ST_NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01); //ʹ��ͨ��0�Ľ��յ�ַ  
	ST_NRF24L01_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0x1a);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��
	ST_NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,0);       //����RFͨ��Ϊ40
	ST_NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);  //����TX�������,0db����,2Mbps,���������濪��   
	ST_NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG,0x0e);    //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�
	NRF24L01_CE=1;//CEΪ��,10us����������
	ST_Delay_us(10);
}
