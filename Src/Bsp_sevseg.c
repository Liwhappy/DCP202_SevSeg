#include "Bsp_sevseg.h"


uint8_t Sev_Tab[] = {
			0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xf8,
			0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,
			0x89,0xc7,0xc8,0xc1,0x8c,0xa3,0xbf,0xff
		//	 H	  L    N    U    P    o    -     
};

uint8_t  SMG_BUFFER[SMG_ITEMS];
#define  COM_ALLOFF			0xFF

// ��������ܹ�����:
// ����comID ѡ���ĸ�������ʾ
void SMG_SetCom(uint8_t comId)
{
	// GPIO �˿ڵĵ�8λΪ�����ѡ��λ��bit0��Ч
	if(comId == COM_ALLOFF)
	{
		SMG_GPIO->ODR |= 0xff;
	}
	else{
		SMG_GPIO->ODR |= 0xff;
		SMG_GPIO->ODR &= ~(0x80>>comId);
	}

}


// ������ʾ���룬disSeg �߶�����ֵ
void SMG_setData(uint8_t disSeg)
{
	// GPIO�˿ڵ� ��8λΪ������ʾλ 0Ϊ����
	SMG_GPIO->ODR &= ~(0xFF <<8);
	SMG_GPIO->ODR |= (disSeg << 8);
	
}


// �˿ڳ�ʼ������
void BSP_SMG_Init(void)
{
	uint8_t i=0;
	GPIO_InitTypeDef GpioInit;
	
	// ����GPIO��RCCʱ��ʹ��
	RCC->APB2ENR |= SMG_GPIO_RCC_ENRBIT;
	// ��ʼ��GPIO�ܽ�Ϊ���
	GpioInit.GPIO_Mode 	= GPIO_Mode_Out_PP;
	GpioInit.GPIO_Pin 	= GPIO_Pin_All;
	GpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SMG_GPIO, &GpioInit);
	// ��ʼ���������ʾ��������Ϊ ����
	for(i=0;i<SMG_ITEMS;i++)
	{
		SMG_BUFFER[i] = 0xff;
	}

}




// ����ܶ�̬ˢ�·���
// ��Ҫ���ڵ��á�
void SMG_Refresh(void)
{
	static uint8_t idx;
	
	// ������COM�ر�(������Ӱ)
	SMG_SetCom(COM_ALLOFF);
	// ˢ�� data����
	SMG_setData( SMG_BUFFER[idx] );
	// ����ʾλ����ܹ�����
	SMG_SetCom(idx);
	
	idx ++;
	if(idx >= SMG_ITEMS) idx = 0;

}

void SMG_Clear(void){
	uint8_t i=0;
	for(i=0;i<SMG_ITEMS;i++)
	{
		SMG_BUFFER[i] = 0xff;
	}
}

// ---------------��������ʾ��ط���-------------------------
void SMG_BuffWrite(uint8_t id,uint8_t buffd)
{
	if(id < SMG_ITEMS )		//���id����С�����������
	{
		SMG_BUFFER[id] = buffd;
	}
}




// �������ʾ�������ݺ���
/*
	showNum ����Ҫ��ʾ��������
	
*/
void SMG_ShowInt(uint32_t showNUM, uint8_t startPos, uint8_t showBit)
{
	uint8_t bit;
	uint8_t endPos;
	endPos = startPos + showBit;
	if(endPos > 8 ) endPos = 8;				//�޶�����λ��

	for(bit = startPos; bit < endPos; bit++)
	{
		SMG_BUFFER[ bit ] = Sev_Tab[ showNUM % 10 ];
		showNUM /= 10;
	}
}


/**
 * @description: ���ַ�����ʽ��ʾ����ܷ���
 * @param str   �ַ���ָ��
 * @param startPos  ��࿪ʼ����ʼλ��
 * @return {*}
 */
void SMG_print(char *str , uint8_t startPos)
{
	uint8_t i=0;
	uint8_t strShowSize = 0;
	strShowSize = SMG_ITEMS - startPos;

	for ( i = 0; i < strShowSize; i++)
	{
		
	}
	

}






// ---------------�����ǿ�����ʼ����ʾ����-------------------------
// ����ܿ��ػ�����ʾ
#define SHIFT_Data		12345678
void SMG_RotateShift(uint8_t shiftDir)
{
	static uint32_t sdata = SHIFT_Data;
	SMG_ShowInt(sdata,0,8);
	
	if(shiftDir == 0) // ����
	{
		sdata = (sdata * 10) % 100000000 + (sdata / 10000000); 
	}
	else{		//����
		sdata = (sdata % 10) * 10000000 + (sdata / 10);
	}
}


// ������������ݱ仯
#define DEFAULT_VALUE		99999999
void SMG_All_num(uint8_t UpOrDn)
{
	static uint32_t sdata = DEFAULT_VALUE;
	SMG_ShowInt(sdata,0,8);
	
	if(UpOrDn == 0)
	{
			if(sdata == 0)
			{
				sdata = 99999999;
			}
			else
			{
				sdata -= 11111111;
			}
	}
	else
	{
			if(sdata == 99999999)
			{
				sdata = 0;
			}
			else
			{
				sdata += 11111111;
			}
	}
	
	
}








