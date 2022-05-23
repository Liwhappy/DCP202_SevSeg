#include "Sensor_Encoder.h"


motorInfo_def* psMotorX;   //X��������ָ��
motorInfo_def* psMotorY;   //Y��������ָ��


/**
 * @brief : TIM3 ���벶�� CH3 CH4 ͨ����ʼ��
 * @description: ����ch3 ch4 ����ͨ�������벶���ж�
 * @return {void}
 */
void TIM3_Cap_Init(void)
{
   GPIO_InitTypeDef sGPIO_Init;
   TIM_TimeBaseInitTypeDef sTIMBase_Init;
   TIM_ICInitTypeDef sTIM_ICInit;
   NVIC_InitTypeDef  sNVIC_Init;
   
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
   RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM3EN,   ENABLE);

   sGPIO_Init.GPIO_Mode = GPIO_Mode_IPU;
   sGPIO_Init.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
   GPIO_Init(GPIOB,&sGPIO_Init);
   GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1);

   sTIMBase_Init.TIM_ClockDivision = TIM_CKD_DIV1;
   sTIMBase_Init.TIM_CounterMode = TIM_CounterMode_Up;
   sTIMBase_Init.TIM_Period = 0xFFFF;        //ARR-�Զ�����ֵ
   sTIMBase_Init.TIM_Prescaler = 72 -1;
   TIM_TimeBaseInit(TIM3,&sTIMBase_Init);
   
   TIM_ICStructInit(&sTIM_ICInit);
   sTIM_ICInit.TIM_Channel = TIM_Channel_3;
   TIM_ICInit(TIM3,&sTIM_ICInit);

   sTIM_ICInit.TIM_Channel = TIM_Channel_4;
   TIM_ICInit(TIM3,&sTIM_ICInit);

   // �ж�����
   sNVIC_Init.NVIC_IRQChannel = TIM3_IRQn;
   sNVIC_Init.NVIC_IRQChannelPreemptionPriority = 0;
   sNVIC_Init.NVIC_IRQChannelSubPriority = 3;
   sNVIC_Init.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&sNVIC_Init);

   TIM_ITConfig(TIM3,TIM_IT_CC3|TIM_IT_CC4,ENABLE);
   TIM_Cmd(TIM3,ENABLE);

}


void senEncoder_Init(motorInfo_def* motX,motorInfo_def* motY)
{
    if(psMotorX == NULL && psMotorY == NULL)
    {
        TIM3_Cap_Init();
    }
    psMotorX = motX;
    psMotorY = motY;

}


/*******************************************************************************
 * Function Name  : TIM3_IRQHandler
 * Description    : TIM3���岶���жϷ������;TIM3_CH3, TIM3_CH4;
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET) // GPIOB0 �����������벶���ź�
    {
        if(psMotorX != NULL)
        {
            if (psMotorX->Dir == MOTOR_RUN_Dir_Forward)
            {
                if (psMotorX->location < MOTOR_POSLOC_MAX)
                    psMotorX->location++;
            }
            else if(psMotorX->Dir == MOTOR_RUN_Dir_Forward)
            {
                if(psMotorX->location > 0)
                {
                    psMotorX->location --;
                }
            }
        }
    }

    if (TIM_GetITStatus(TIM3, TIM_IT_CC4) != RESET) // GPIOB0 �����������벶���ź�
    {
        if(psMotorY != NULL)
        {
            if (psMotorY->Dir == MOTOR_RUN_Dir_Forward)
            {
                if (psMotorY->location < MOTOR_POSLOC_MAX)
                    psMotorY->location++;
            }
            else if(psMotorY->Dir == MOTOR_RUN_Dir_Forward)
            {
                if(psMotorY->location > 0)
                {
                    psMotorY->location --;
                }
            }
        }
    }
}
