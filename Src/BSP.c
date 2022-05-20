/*
 * @Date: 2022-05-18 10:20:15
 * @LastEditors: kimiyang
 * @LastEditTime: 2022-05-19 22:30:23
 * @FilePath: \DCP202_SevSeg\Src\BSP.c
 * @Description: 
 * 
 */

#include "BSP.h"

// ʱ�ӽ���
__IO uint32_t _sysTicks_inc = 0;	

/****************************************************************************
* ��    �ƣ�void sysTick_increase(void)
* ��    �ܣ�ʱ�ӽ�������
* ��ڲ�������
* ���ڲ�������
* ˵    �����˷����� systick��ʱ���ж����ڵ���
* ���÷������� 
****************************************************************************/  
void sysTick_increase(void)
{
	_sysTicks_inc ++;
}


/*��ȡϵͳʱ�ӽ�������*/
uint32_t getSysTicks(void)
{
	return _sysTicks_inc;	
}

/****************************************************************************
* ��    �ƣ�void delay_ticks
* ��    �ܣ�����systick��ʱ������ʱ����
* ��ڲ�����dtime ��ʱʱ�䣬��λmS
* ���ڲ�������
* ˵    �����˷����� systick��ʱ���ж����ڵ���
* ���÷������� 
****************************************************************************/  

void delay_ticks(uint16_t dtime)
{
	uint32_t timestamp;
	timestamp = getSysTicks();
	while(getSysTicks() - timestamp < dtime);
}





extern void SMG_Refresh(void);
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval : None
  */
void SysTick_Handler(void)
{
  sysTick_increase();

}




/************************************************/
/*								GPIO                          */
void BSP_Configuration(void)
{
	GPIO_InitTypeDef GPIOInit;
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	
	// beep Pin init
	GPIOInit.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOInit.GPIO_Pin = GPIO_Pin_13;
	GPIOInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIOInit);
	
	// LED1 and LED2 Init
	GPIOInit.GPIO_Mode	 	= GPIO_Mode_Out_PP;
	GPIOInit.GPIO_Pin 		= GPIO_Pin_7|GPIO_Pin_9;
	GPIOInit.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIOInit);
	GPIO_WriteBit(GPIOC,GPIOInit.GPIO_Pin,(BitAction)1);

}



void Beep_On(uint16_t onTime)
{
	GPIO_WriteBit(GPIOC,GPIO_Pin_13,1);
	delay_ticks(onTime);
	GPIO_WriteBit(GPIOC,GPIO_Pin_13,0);
}





