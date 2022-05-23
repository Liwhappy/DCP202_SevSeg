#ifndef __TIM_AND_PWM_H__
#define __TIM_AND_PWM_H__

#include "stm32f10x.h"


#define TIM_TASK_MAX	4		//���嶨ʱ�����������

typedef void (*tim_Period_Fun)();

typedef struct timFun_List
{
	tim_Period_Fun tFun;
	uint16_t PeriodTick;
	void *param;
} timFunList_def;


/**
 * @brief : �����ʼ����
 * @description: 
 * @return {void}
 */
void TimTask_Init(void);

/**
 * @brief ��ʱ�����ڵ��� �������
 * @param _fun: ��Ҫ���ȵ�������,����ָ��
 * @param period_t:  �������ĵ������� 100��ʾÿ100msִ��һ��
 * @param parm : �������Ĵ��ݲ�����û�������� NULL �� 0
 * @return (uint8_t)taskId: ��������ID 
 */
uint8_t tim2_addTask(tim_Period_Fun _fun, uint16_t period_t, void *parm);

/**
 * @brief : ��ʱ����ɾ������
 * @description: 
 * @param _fun :��Ҫɾ����������ָ��
 * @return {void}
 */
void tim2_delTask(tim_Period_Fun _fun);




#endif
