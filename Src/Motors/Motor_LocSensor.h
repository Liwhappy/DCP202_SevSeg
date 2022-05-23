/*
 * @Date: 2022-05-22 14:29:03
 * @LastEditors: kimiyang
 * @LastEditTime: 2022-05-22 23:48:59
 * @FilePath: \DCP202_SevSeg\Src\Motors\Motor_LocSensor.h
 * @Description: motor Location sensor
 *        ���λ�û�ȡ������װ
 *     - �������������: 1.������ 
 *                      2.����ʽ������ 
 *                      3.MEMS������ 
 *                      4.���������
 */
#ifndef __MOTOR_LOCATION_SENSOR_H_
#define __MOTOR_LOCATION_SENSOR_H_

    #include <stm32f10x_conf.h>
		
    #include "Motor_HPWM.h"
    
    #include "Sensor_Encoder.h"     // ������������
    
    #define NULL 0

    #define MOTOR_POSLOC_MAX        0xFFFF

    
    /**
     * @brief : ��X�ᴫ������Ӧ�ĵ��
     * @description: 
     * @param  pMotx: {motorInfo_def*}X ��������
     * @return {*}
     */
//		 
    void locSensor_MorotX_Bind(motorInfo_def* pMotx);
		
    void locSensor_MorotY_Bind(motorInfo_def* pMoty);
    

#endif
