/**
 * @project	balance_evo
 * @author	
 * @brief		
 * @version 0.1
 * @date 		2021-04-6
 * 
 * @copyright Copyright (c) 2021
 * 
 *
 * �������ʹ��TIM1��ͨ��1��4
 * ������ǲ�ʹ��DAC��TIM2
 *
 */
 
 
/*

PA8��PA11�������
PA9������Ҳ�
PA10������ǲ�

PB5��PB6����CH2����ռ�ձ�


*/
/* ����ͷ�ļ� */
#include "sys.h"

/* ȫ�ֱ������� */


void GPIOA15_Init(void)
{
	GPIO_InitTypeDef GPIO_Initsturt;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_Initsturt.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initsturt.GPIO_Pin=GPIO_Pin_15;
	GPIO_Initsturt.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_Initsturt);
}

/**
 * @brief		������
 * 
 * @param		��
 * @return	��
 */
int main(void)
{ 
	delay_init();
	
	
	GPIOA15_Init();
	//OLED_Init();
	//OLED_ShowNumber(0, 0,123,3,14);
	
	//TIM1_PWM_Init(7199,0);   			 //=====��ʼ��PWM 10KHZ
	
	//Set_Pwm(3600, 3600);  // PWM����ֵ��7200
	//GPIO_ResetBits(GPIOA, GPIO_Pin_15);
	//TriangleWave_Init(100, 0);
	//TriangleWave_Init2();
	DAC_Mode_Init();  // Ŀǰ���ǲ������Ҳ�����ͬʱ��ʼ��
	
  while(1)	
	{
		
	}
}
