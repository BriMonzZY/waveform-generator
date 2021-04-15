/**
* By BriMon
* 2021.2.6
* 位带操作头文件
* STM32F103VE
*/

#include "stm32f10x.h"

#define GPIOA_ODR_Addr		(GPIOA_BASE + 0x0C)
#define GPIOB_ODR_Addr		(GPIOB_BASE + 0x0C)
#define GPIOC_ODR_Addr		(GPIOC_BASE + 0x0C)
#define GPIOD_ODR_Addr		(GPIOD_BASE + 0x0C)
#define GPIOE_ODR_Addr		(GPIOE_BASE + 0x0C)
#define GPIOF_ODR_Addr		(GPIOF_BASE + 0x0C)
#define GPIOG_ODR_Addr		(GPIOG_BASE + 0x0C)

#define GPIOA_IDR_Addr		(GPIOA_BASE + 0x08)
#define GPIOB_IDR_Addr		(GPIOB_BASE + 0x08)
#define GPIOC_IDR_Addr		(GPIOC_BASE + 0x08)
#define GPIOD_IDR_Addr		(GPIOD_BASE + 0x08)
#define GPIOE_IDR_Addr		(GPIOE_BASE + 0x08)
#define GPIOF_IDR_Addr		(GPIOF_BASE + 0x08)
#define GPIOG_IDR_Addr		(GPIOG_BASE + 0x08)



#define PAout(n)    *(unsigned int *)((GPIOA_ODR_Addr & 0xF0000000) + 0x02000000 + ((GPIOA_ODR_Addr & 0x00FFFFFF) << 5) + (n << 2))
#define PAin(n)     *(unsigned int *)((GPIOA_IDR_Addr & 0xF0000000) + 0x02000000 + ((GPIOA_IDR_Addr & 0x00FFFFFF) << 5) + (n << 2))

#define PBout(n)    *(unsigned int *)((GPIOB_ODR_Addr & 0xF0000000) + 0x02000000 + ((GPIOB_ODR_Addr & 0x00FFFFFF) << 5) + (n << 2))
#define PBin(n)     *(unsigned int *)((GPIOB_IDR_Addr & 0xF0000000) + 0x02000000 + ((GPIOB_IDR_Addr & 0x00FFFFFF) << 5) + (n << 2))

#define PCout(n)    *(unsigned int *)((GPIOC_ODR_Addr & 0xF0000000) + 0x02000000 + ((GPIOC_ODR_Addr & 0x00FFFFFF) << 5) + (n << 2))
#define PCin(n)     *(unsigned int *)((GPIOC_IDR_Addr & 0xF0000000) + 0x02000000 + ((GPIOC_IDR_Addr & 0x00FFFFFF) << 5) + (n << 2))

#define PDout(n)    *(unsigned int *)((GPIOD_ODR_Addr & 0xF0000000) + 0x02000000 + ((GPIOD_ODR_Addr & 0x00FFFFFF) << 5) + (n << 2))
#define PDin(n)     *(unsigned int *)((GPIOD_IDR_Addr & 0xF0000000) + 0x02000000 + ((GPIOD_IDR_Addr & 0x00FFFFFF) << 5) + (n << 2))

#define PEout(n)    *(unsigned int *)((GPIOE_ODR_Addr & 0xF0000000) + 0x02000000 + ((GPIOE_ODR_Addr & 0x00FFFFFF) << 5) + (n << 2))
#define PEin(n)     *(unsigned int *)((GPIOE_IDR_Addr & 0xF0000000) + 0x02000000 + ((GPIOE_IDR_Addr & 0x00FFFFFF) << 5) + (n << 2))

#define PFout(n)    *(unsigned int *)((GPIOF_ODR_Addr & 0xF0000000) + 0x02000000 + ((GPIOF_ODR_Addr & 0x00FFFFFF) << 5) + (n << 2))
#define PFin(n)     *(unsigned int *)((GPIOF_IDR_Addr & 0xF0000000) + 0x02000000 + ((GPIOF_IDR_Addr & 0x00FFFFFF) << 5) + (n << 2))

#define PGout(n)    *(unsigned int *)((GPIOG_ODR_Addr & 0xF0000000) + 0x02000000 + ((GPIOG_ODR_Addr & 0x00FFFFFF) << 5) + (n << 2))
#define PGin(n)     *(unsigned int *)((GPIOG_IDR_Addr & 0xF0000000) + 0x02000000 + ((GPIOG_IDR_Addr & 0x00FFFFFF) << 5) + (n << 2))
