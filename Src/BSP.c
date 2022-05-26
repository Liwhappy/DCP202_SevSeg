
#include "BSP.h"

// 时钟节拍
__IO uint32_t _sysTicks_inc = 0;	

/****************************************************************************
* 名    称：void sysTick_increase(void)
* 功    能：时钟节拍增量
* 入口参数：无
* 出口参数：无
* 说    明：此方法由 systick定时器中断周期调用
* 调用方法：无 
****************************************************************************/  
void sysTick_increase(void)
{
	_sysTicks_inc ++;
}


/*获取系统时钟节拍数量*/
uint32_t getSysTicks(void)
{
	return _sysTicks_inc;	
}

/****************************************************************************
* 名    称：void delay_ticks
* 功    能：基于systick定时器的延时函数
* 入口参数：dtime 延时时间，单位mS
* 出口参数：无
* 说    明：此方法由 systick定时器中断周期调用
* 调用方法：无 
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
/*								GPIO     
*/

/**
 * @brief : 开发板 板载资源配置，含GPIO systick初始化
 * @description: 
 * @return {*}
 */
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
	

	// NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_2);

	SysTick_Config(SystemCoreClock / 1000);
	// SysTick_Config(72000);
	NVIC_SetPriority(SysTick_IRQn,  
				NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,0 ));

	
}


/**
 * @brief : 蜂鸣器发声
 * @description: 
 * @param onTime: (uint16_t)发声时间，单位ms
 * @return {null}
 */
void Beep_On(uint16_t onTime)
{
	GPIO_WriteBit(GPIOC,GPIO_Pin_13,1);
	delay_ticks(onTime);
	GPIO_WriteBit(GPIOC,GPIO_Pin_13,0);
}




long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



