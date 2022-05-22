/*
 * @Date: 2022-05-20 09:21:18
 * @LastEditors: kimiyang
 * @LastEditTime: 2022-05-21 14:01:46
 * @FilePath: \DCP202_SevSeg\Src\appSMG_UI.h
 * @Description: ������û������˻��ӿڽ������
 * 
 */
#ifndef __APP_UI_SMG_H__
#define __APP_UI_SMG_H__

#include "KeyPad4x4.h"
#include "BSP.h"
#include "Bsp_sevseg.h"
#include "string.h"
#include "stdlib.h"

#include "ctype.h"

#define  ENTER_TYPE_NUM     0x00
#define  ENTER_TYPE_ALL     0x01



char* ui_WaitEnter(uint8_t entPos, uint8_t maxEnter, uint8_t keyEvent,  uint8_t EnterType);
// char* ui_WaitEnter(uint8_t entPos, uint8_t maxEnter, uint8_t EnterType);

/**
 * @description: ��ȡUI�������ݻ�������������
 * @return {*}
 */
uint8_t get_entBuff_length(void);

/**
 * @description: ��հ�������������
 * @return {*}
 */
void enterBuff_clean(void);



#endif
