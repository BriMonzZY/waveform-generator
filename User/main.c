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
 * 输出方波使用TIM1的通道1和4
 * 输出三角波使用DAC和TIM2
 *
 */
 
 
/*

PA8和PA11输出方波
PA9输出正弦波
PA10输出三角波

PB5和PB6控制CH2方波占空比


*/
/* 包含头文件 */
#include "sys.h"

/* 全局变量定义 */


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
 * @brief		主函数
 * 
 * @param		无
 * @return	无
 */
int main(void)
{ 
	delay_init();
	
	
	GPIOA15_Init();
	//OLED_Init();
	//OLED_ShowNumber(0, 0,123,3,14);
	
	//TIM1_PWM_Init(7199,0);   			 //=====初始化PWM 10KHZ
	
	//Set_Pwm(3600, 3600);  // PWM满幅值是7200
	//GPIO_ResetBits(GPIOA, GPIO_Pin_15);
	//TriangleWave_Init(100, 0);
	//TriangleWave_Init2();
	DAC_Mode_Init();  // 目前三角波和正弦波不能同时初始化
	
  while(1)	
	{
		
	}
}
