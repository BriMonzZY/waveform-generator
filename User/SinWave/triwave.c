#include "triwave.h"

void SinWave_GPIO_Init(void) // PA9
{
	GPIO_InitTypeDef GPIO_Initsturt;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_Initsturt.GPIO_Mode=GPIO_Mode_AF_PP;  // 复用推挽输出 
	GPIO_Initsturt.GPIO_Pin=GPIO_Pin_9;
	GPIO_Initsturt.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_Initsturt);
}

void TriangleWave_GPIO_Init(void) // PA4  DAC1    PA5  DAC2
{
	GPIO_InitTypeDef GPIO_Initsturt;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_Initsturt.GPIO_Mode=GPIO_Mode_AIN;  // 模拟输入
	GPIO_Initsturt.GPIO_Pin=GPIO_Pin_4 | GPIO_Pin_5;
	
	GPIO_Init(GPIOA, &GPIO_Initsturt);
}





void TriangleWave_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	DAC_InitTypeDef DAC_InitStructure;
	
	TriangleWave_GPIO_Init();  // 初始化GPIO
	
	 	
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);   	//使能DAC时钟	   
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);    //使能TIM2时钟
 
	/* 设置DAC三角波模式 */
	/*
	DAC->CR |= 1 << 2;	 // 产生三角波必须使能DAC触发 TEN1=1   必须先设置
	DAC->CR |= 2 << 6;   // DAC通道1  设置WAVE1[1:0]  选择三角波功能
	DAC->CR |= 12 << 8;  // DAC通道1  设置MAMP1[3:0]  1011   11，设置振幅4095
	DAC->CR |= 4 << 3;	 // DAC1 触发选择 设置TSEL1[2:0] TIM2 TRGO事件,不过要TEN1=1才行
	
	DAC->CR |= 0 << 12;	 // DAC1 DMA不使能
	DAC->CR |= 1 << 1;	 // DAC1 输出缓存不使能 BOFF1=1
	
	DAC->CR |= 1 << 0;	 // 使能DAC通道1
	*/
	
	/* 设置TIM2作为触发DAC的触发源 */
	/*
	TIM2->ARR |= arr;       // 重装载
	TIM2->PSC |= psc;       // 预分频
	TIM2->CR2 |= 2<<4;      // 选择 更新事件 作为触发输出（TRGO）  
	TIM2->CR1 |= 0x01;      // 使能TIM2
	*/
	
	
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//初始化DAC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//初始化TIM2的时钟
	

	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;//DAC的触发源为TIM2
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_Triangle;//输出三角波
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_2047;//三角波的幅值对应的数字量为2047，即1.65V，频率为72M/100/2048/2=175Hz左右(与实际输出频率有一点出入)
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;//不适用DAC输出缓冲
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);//初始化DAC的CH1

	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_1023;//三角波的幅值对应的数字量为1023，即0.825V，频率为72M/100/1024/2=252Hz左右(与实价输出频率有一点出入)
	DAC_Init(DAC_Channel_2, &DAC_InitStructure);//初始化DAC的CH2

	DAC_Cmd(DAC_Channel_1, ENABLE);//打开DAC的CH1
	DAC_Cmd(DAC_Channel_2, ENABLE);//打开DAC的CH2
	DAC_SetDualChannelData(DAC_Align_12b_R, 0x00, 0x00);//设置DAC两个通道的数据右对齐，波谷对应的数字量风别为0,0



	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//初始化时基结构体
	TIM_TimeBaseStructure.TIM_Period = 100;//周期值为100
	TIM_TimeBaseStructure.TIM_Prescaler = 0;//不预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;//时钟不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//增计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//初始化TIM2

	TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);//设置触发源为更新触发，更新周期一次，则触发一次DAC转换
	TIM_Cmd(TIM2, ENABLE);//打开定时器
	
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_15);
}














/*************************************************************
Function : TriangleWave_GPIO_Init
Description: 三角波对应的引脚初始化
Input : none
return : none
*************************************************************/
static void TriangleWave_GPIO_Init2(void)
{
GPIO_InitTypeDef GPIO_InitStructure;

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//初始化引脚时钟

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;//初始化DAC的CH1与CH2对应的引脚
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入
GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*************************************************************
Function : TriangleWave_TIM_Init
Description: 三脚波需要的定时器初始化
Input : none
return : none
*************************************************************/
static void TriangleWave_TIM_Init(void)
{
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//初始化TIM2的时钟

TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//初始化时基结构体
TIM_TimeBaseStructure.TIM_Period = 100;//周期值为100
TIM_TimeBaseStructure.TIM_Prescaler = 0;//不预分频
TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;//时钟不分频
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//增计数
TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//初始化TIM2

TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);//设置触发源为更新触发，更新周期一次，则触发一次DAC转换
TIM_Cmd(TIM2, ENABLE);//打开定时器
}

/*************************************************************
Function : TriangleWave_DAC_Init
Description: 三角波需要的DAC初始化
Input : none
return : none
*************************************************************/
static void TriangleWave_DAC_Init(void)
{
DAC_InitTypeDef DAC_InitStructure;

RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//初始化DAC时钟

DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;//DAC的触发源为TIM2
DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_Triangle;//输出三角波
DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_2047;//三角波的幅值对应的数字量为2047，即1.65V，频率为72M/100/2048/2=175Hz左右(与实际输出频率有一点出入)
DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;//不适用DAC输出缓冲
DAC_Init(DAC_Channel_1, &DAC_InitStructure);//初始化DAC的CH1

DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_1023;//三角波的幅值对应的数字量为1023，即0.825V，频率为72M/100/1024/2=252Hz左右(与实价输出频率有一点出入)
DAC_Init(DAC_Channel_2, &DAC_InitStructure);//初始化DAC的CH2

DAC_Cmd(DAC_Channel_1, ENABLE);//打开DAC的CH1
DAC_Cmd(DAC_Channel_2, ENABLE);//打开DAC的CH2

DAC_SetDualChannelData(DAC_Align_12b_R, 0x00, 0x00);//设置DAC两个通道的数据右对齐，波谷对应的数字量风别为0,0
}

/*************************************************************
Function : TriangleWave_Init
Description: 三角波初始化
Input : none
return : none
*************************************************************/

void TriangleWave_Init2(void)
{
TriangleWave_GPIO_Init2();
TriangleWave_TIM_Init();
TriangleWave_DAC_Init();
}
