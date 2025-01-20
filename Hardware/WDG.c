#include "stm32f10x.h"                  // Device header

void WDG_Init(uint8_t prc,uint16_t rlv)
{
	//�ر�д����
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	
	//����Ԥ��Ƶ��ֵ��prc��
	IWDG_SetPrescaler(prc);
	
	//������װ����ֵ��rlv��
	IWDG_SetReload(rlv);
	
	//�ѼĴ���ֵ�ŵ���������
	IWDG_ReloadCounter();
	
	IWDG_Enable();
}

void IWDG_Feed(void)
{
	IWDG_ReloadCounter();
}
