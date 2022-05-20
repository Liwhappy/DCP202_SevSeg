/*
 * @Date: 2022-05-18 19:57:20
 * @LastEditors: kimiyang
 * @LastEditTime: 2022-05-19 22:58:53
 * @FilePath: \DCP202_SevSeg\Src\TimAndPWM.c
 * @Description: ��ʱ����PMW���ܳ�ʼ��
 * 
 */
#include "TimAndPWM.h"

void TIM2_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseStruct.TIM_Prescaler = 72 - 1;
	TIM_TimeBaseStruct.TIM_Period = 1000 - 1;
	TIM_TimeBaseStruct.TIM_ClockDivision = 0;
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStruct);

	// �����ж����ȼ�
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	// ʹ���ж�
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}

uint8_t tim2Fun_cnt = 0;
timFunList_def timTaskList[4];


/**
 * @description: ��ʱ��2����������ӷ���
 * @param _fun
 * @param period_t
 * @param *parm
 * @return {*}
 */
uint8_t tim2_addTask(tim_Period_Fun _fun, uint16_t period_t, void *parm)
{
	uint8_t i = 0;
	// TODO >>>> �ж��п����б�ռ��������
	_fun(parm);

	for (i = 0; i < 4; i++)
	{
		if (timTaskList[i].tFun == 0)
		{
			timTaskList[i].tFun = _fun;
			timTaskList[i].PeriodTick = period_t;
			timTaskList[i].param = parm;
			break;
		}
	}

	return i;
}

void tim2_delTask(tim_Period_Fun _fun)
{
	uint8_t i = 0;
	for (i = 0; i < 4; i++)
	{
		if (timTaskList[i].tFun == _fun)
		{
			timTaskList[i].tFun = 0;
			timTaskList[i].PeriodTick = 0;
			break;
		}
	}
}

/*******************************************************************************
 * Function Name  : TIM2_IRQHandler
 * Description    : TIM2�жϺ���
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
uint32_t tim2Cnt = 0;
void TIM2_IRQHandler(void)
{
	uint8_t i = 0;
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) // ����ж��Ƿ���;
	{
		tim2Cnt++; // 1ms

		for (i = 0; i < 4; i++)
		{
			if (timTaskList[i].tFun != 0)
			{
				if ((tim2Cnt % timTaskList[i].PeriodTick) == 0)
				{
					timTaskList[i].tFun(timTaskList[i].param);
				}
			}
		}
	}

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // ����жϴ�����λ;
}
