

#ifndef __BSP_SEVSEG_H__
#define __BSP_SEVSEG_H__

	
	#include "stm32f10x.h"
	
	#define  SMG_ITEMS	8
	
	#define  SMG_GPIO					GPIOG
	#define  SMG_GPIO_RCC_ENRBIT		RCC_APB2ENR_IOPGEN
	
	// ����ܳ�ʼ������
	void BSP_SMG_Init(void);
	
	void SMG_Refresh(void);
	void SMG_Clear(void);


	void SMG_BuffWrite(uint8_t id,uint8_t buffd);
	void SMG_ShowInt(uint32_t showNUM, uint8_t startPos, uint8_t showBit);

	//�������棬�����������λ����
	void SMG_RotateShift(uint8_t shiftDir);
	void SMG_All_num(uint8_t UpOrDn);

#endif
