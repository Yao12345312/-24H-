#include "stm32f10x.h"                  // Device header

void WDG_Init(uint8_t prc,uint16_t rlv)
{
	//关闭写保护
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	
	//设置预分频器值（prc）
	IWDG_SetPrescaler(prc);
	
	//设置重装载器值（rlv）
	IWDG_SetReload(rlv);
	
	//把寄存器值放到计数器中
	IWDG_ReloadCounter();
	
	IWDG_Enable();
}

void IWDG_Feed(void)
{
	IWDG_ReloadCounter();
}
