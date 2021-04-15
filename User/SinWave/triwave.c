#include "triwave.h"

void SinWave_GPIO_Init(void) // PA9
{
	GPIO_InitTypeDef GPIO_Initsturt;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_Initsturt.GPIO_Mode=GPIO_Mode_AF_PP;  // ����������� 
	GPIO_Initsturt.GPIO_Pin=GPIO_Pin_9;
	GPIO_Initsturt.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_Initsturt);
}

void TriangleWave_GPIO_Init(void) // PA4  DAC1    PA5  DAC2
{
	GPIO_InitTypeDef GPIO_Initsturt;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_Initsturt.GPIO_Mode=GPIO_Mode_AIN;  // ģ������
	GPIO_Initsturt.GPIO_Pin=GPIO_Pin_4 | GPIO_Pin_5;
	
	GPIO_Init(GPIOA, &GPIO_Initsturt);
}





void TriangleWave_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	DAC_InitTypeDef DAC_InitStructure;
	
	TriangleWave_GPIO_Init();  // ��ʼ��GPIO
	
	 	
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);   	//ʹ��DACʱ��	   
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);    //ʹ��TIM2ʱ��
 
	/* ����DAC���ǲ�ģʽ */
	/*
	DAC->CR |= 1 << 2;	 // �������ǲ�����ʹ��DAC���� TEN1=1   ����������
	DAC->CR |= 2 << 6;   // DACͨ��1  ����WAVE1[1:0]  ѡ�����ǲ�����
	DAC->CR |= 12 << 8;  // DACͨ��1  ����MAMP1[3:0]  1011   11���������4095
	DAC->CR |= 4 << 3;	 // DAC1 ����ѡ�� ����TSEL1[2:0] TIM2 TRGO�¼�,����ҪTEN1=1����
	
	DAC->CR |= 0 << 12;	 // DAC1 DMA��ʹ��
	DAC->CR |= 1 << 1;	 // DAC1 ������治ʹ�� BOFF1=1
	
	DAC->CR |= 1 << 0;	 // ʹ��DACͨ��1
	*/
	
	/* ����TIM2��Ϊ����DAC�Ĵ���Դ */
	/*
	TIM2->ARR |= arr;       // ��װ��
	TIM2->PSC |= psc;       // Ԥ��Ƶ
	TIM2->CR2 |= 2<<4;      // ѡ�� �����¼� ��Ϊ���������TRGO��  
	TIM2->CR1 |= 0x01;      // ʹ��TIM2
	*/
	
	
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//��ʼ��DACʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//��ʼ��TIM2��ʱ��
	

	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;//DAC�Ĵ���ԴΪTIM2
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_Triangle;//������ǲ�
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_2047;//���ǲ��ķ�ֵ��Ӧ��������Ϊ2047����1.65V��Ƶ��Ϊ72M/100/2048/2=175Hz����(��ʵ�����Ƶ����һ�����)
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;//������DAC�������
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);//��ʼ��DAC��CH1

	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_1023;//���ǲ��ķ�ֵ��Ӧ��������Ϊ1023����0.825V��Ƶ��Ϊ72M/100/1024/2=252Hz����(��ʵ�����Ƶ����һ�����)
	DAC_Init(DAC_Channel_2, &DAC_InitStructure);//��ʼ��DAC��CH2

	DAC_Cmd(DAC_Channel_1, ENABLE);//��DAC��CH1
	DAC_Cmd(DAC_Channel_2, ENABLE);//��DAC��CH2
	DAC_SetDualChannelData(DAC_Align_12b_R, 0x00, 0x00);//����DAC����ͨ���������Ҷ��룬���ȶ�Ӧ�����������Ϊ0,0



	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//��ʼ��ʱ���ṹ��
	TIM_TimeBaseStructure.TIM_Period = 100;//����ֵΪ100
	TIM_TimeBaseStructure.TIM_Prescaler = 0;//��Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;//ʱ�Ӳ���Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//������
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//��ʼ��TIM2

	TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);//���ô���ԴΪ���´�������������һ�Σ��򴥷�һ��DACת��
	TIM_Cmd(TIM2, ENABLE);//�򿪶�ʱ��
	
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_15);
}














/*************************************************************
Function : TriangleWave_GPIO_Init
Description: ���ǲ���Ӧ�����ų�ʼ��
Input : none
return : none
*************************************************************/
static void TriangleWave_GPIO_Init2(void)
{
GPIO_InitTypeDef GPIO_InitStructure;

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//��ʼ������ʱ��

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;//��ʼ��DAC��CH1��CH2��Ӧ������
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//ģ������
GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*************************************************************
Function : TriangleWave_TIM_Init
Description: ���Ų���Ҫ�Ķ�ʱ����ʼ��
Input : none
return : none
*************************************************************/
static void TriangleWave_TIM_Init(void)
{
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//��ʼ��TIM2��ʱ��

TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//��ʼ��ʱ���ṹ��
TIM_TimeBaseStructure.TIM_Period = 100;//����ֵΪ100
TIM_TimeBaseStructure.TIM_Prescaler = 0;//��Ԥ��Ƶ
TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;//ʱ�Ӳ���Ƶ
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//������
TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//��ʼ��TIM2

TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);//���ô���ԴΪ���´�������������һ�Σ��򴥷�һ��DACת��
TIM_Cmd(TIM2, ENABLE);//�򿪶�ʱ��
}

/*************************************************************
Function : TriangleWave_DAC_Init
Description: ���ǲ���Ҫ��DAC��ʼ��
Input : none
return : none
*************************************************************/
static void TriangleWave_DAC_Init(void)
{
DAC_InitTypeDef DAC_InitStructure;

RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//��ʼ��DACʱ��

DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;//DAC�Ĵ���ԴΪTIM2
DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_Triangle;//������ǲ�
DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_2047;//���ǲ��ķ�ֵ��Ӧ��������Ϊ2047����1.65V��Ƶ��Ϊ72M/100/2048/2=175Hz����(��ʵ�����Ƶ����һ�����)
DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;//������DAC�������
DAC_Init(DAC_Channel_1, &DAC_InitStructure);//��ʼ��DAC��CH1

DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_1023;//���ǲ��ķ�ֵ��Ӧ��������Ϊ1023����0.825V��Ƶ��Ϊ72M/100/1024/2=252Hz����(��ʵ�����Ƶ����һ�����)
DAC_Init(DAC_Channel_2, &DAC_InitStructure);//��ʼ��DAC��CH2

DAC_Cmd(DAC_Channel_1, ENABLE);//��DAC��CH1
DAC_Cmd(DAC_Channel_2, ENABLE);//��DAC��CH2

DAC_SetDualChannelData(DAC_Align_12b_R, 0x00, 0x00);//����DAC����ͨ���������Ҷ��룬���ȶ�Ӧ�����������Ϊ0,0
}

/*************************************************************
Function : TriangleWave_Init
Description: ���ǲ���ʼ��
Input : none
return : none
*************************************************************/

void TriangleWave_Init2(void)
{
TriangleWave_GPIO_Init2();
TriangleWave_TIM_Init();
TriangleWave_DAC_Init();
}
