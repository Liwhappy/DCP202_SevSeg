#include "Motor_LocSensor.h"


// void initExit()
// {
//    EXTI_InitTypeDef sEXTI_init;
//    sEXTI_init.EXTI_Mode = EXTI_Mode_Interrupt;
//    sEXTI_init.EXTI_Line = EXTI_Line0 | EXTI_Line1;
//    sEXTI_init.EXTI_Trigger = EXTI_Trigger_Rising;
//    sEXTI_init.EXTI_LineCmd = ENABLE;
//    EXTI_Init(&sEXTI_init);
// }


void locSensor_Init(void)
{
   // ʹ�ñ�����λ�ô�����
   //senEncoder_Init();
}


/**
 * @brief : �������� X��������
 * @description: 
 * @param _pMotorx:{motorInfo_def*} �������ָ��
 * @return {*}
 */
void locSensor_MorotX_Bind(motorInfo_def* pMotx)
{
   senEncoder_Init(pMotx,NULL);
}

void locSensor_MorotY_Bind(motorInfo_def* pMoty)
{
   senEncoder_Init(NULL,pMoty);
}


