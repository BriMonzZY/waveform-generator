#ifndef __PWM_H
#define __PWM_H


#include "sys.h"
#include "stm32f10x_tim.h" 

#define PWMB   TIM1->CCR4  //PA11
#define PWMA   TIM1->CCR1  //PA8
int myabs(int a);
void Set_Pwm(int ch1,int ch2);
void TIM1_PWM_Init(u16 arr,u16 psc);

#endif
