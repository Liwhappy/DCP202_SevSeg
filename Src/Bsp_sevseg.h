

#ifndef __BSP_SEVSEG_H__
#define __BSP_SEVSEG_H__

	
	#include "stm32f10x.h"
	#include "ctype.h"
	
	#define  SMG_ITEMS					8
	
	#define  SMG_GPIO					GPIOG
	#define  SMG_GPIO_RCC_ENRBIT		RCC_APB2ENR_IOPGEN
	
	/**
	 * @brief :����ܳ�ʼ���������������� 
	 * @description: 
	 * @return {void}
	 */
	void SMG_BSP_Init(void);
	
	void SMG_Refresh(void);		// �ж���������
	void SMG_CleanAll(void);
	void SMG_CleanPos(uint8_t Spos,uint8_t len);

	void SMG_BuffWrite(uint8_t id,uint8_t buffd);

	/**
	 * @description: �������ʾ��������
	 * @param showNUM: {uint32_t} ��Ҫ��ʾ������ֵ
	 * @param startPos: {uint8_t} ��λ����ʾ���Ҳ����ĸ�λ��
	 * @param  showBit: {uint8_t} ��ʾ��λ��Ч����
	 * @return {void}
	 */
	void SMG_ShowInt(uint32_t showNUM, uint8_t startPos, uint8_t showBit);
	
	/**
	 * @brief : ���ַ�����ʽ��ʾ����ܷ���
	 * @param str :{char*}  �ַ���ָ�� ��:"hello"
	 * @param startPos: {uint8_t}��࿪ʼ����ʼλ��
	 * @return {void}
	 */
	void SMG_print(char *str , uint8_t startPos);



	//�������棬�����������λ����
	void SMG_RotateShift(uint8_t shiftDir);
	void SMG_All_num(uint8_t UpOrDn);

#endif



/*******************************************
 * ʹ����ʾ
 * 
 * #include "Bsp_sevseg.h"
 * int main()
 * {
 * 		SMG_BSP_Init();	//���ó�ʼ������
 * 
 * 		SMG_ShowInt(123,0,3);	//����������Ҳ���ʾ123
 * 		SMG_print("Hello",0);	//�����������һλ��ʼ��ʾ"hello"�ַ�
 * 
 * 		while(1)
 * 		{
 * 			SMG_Refresh();		//����ˢ����ʾ����ܣ��Ƽ��ڶ�ʱ���ж��е���
 * 		}
 * 
 * }
 * 
 * **********************************************/

