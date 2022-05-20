#include "appSMG_UI.h"

char enterBuffer[10];
uint8_t enterId = 0;

/***�����ַ�ӳ���***/
const uint8_t KeyMap[16] = {
    'F','7','8','9',
    'S','4','5','6',
    '<','1','2','3',
    '>','D','0','E'
};

/***����������ת��Ϊ�����ַ�ӳ���***/
uint8_t _getKeyMap(uint8_t keyID)
{
    if(keyID >0 && keyID <=16)
    {
        return KeyMap[keyID-1];
    }
    else
    {
        return 0;
    }
}

/***�������ַ�ӳ�䣬ת��Ϊ��������***/
uint8_t _keyMap2KeyID(uint8_t kMapStr)
{
    uint8_t i=0;
    for(i=0;i<16;i++)
    {
        if(KeyMap[i] == kMapStr)
        {
            return i+1;
        }
    }
    return 0;
}


void setCursor(uint8_t curId)
{
    if(curId >= SMG_ITEMS) return 0;

    SMG_BuffWrite( SMG_ITEMS - curId - 1, ~0x08 );
}

void enterBuff_add(char str)
{
    if(enterId < 8)
    {
        enterBuffer[enterId++] = str;
    }
}

void enterBuff_backspace()
{
    if(enterId > 0)
    {
        enterBuffer[enterId] = 0;
        enterId --;
    }
}

/**
 * @description: �ȴ���������
 * @param undefined
 * @return {*}
 */
char* ui_WaitEnter(uint8_t entPos, uint16_t wTimeMax)
{
    uint8_t i=0,exit = 0;
    uint8_t keyMapChar;
    memset(enterBuffer,0,10);   // ������뻺��
	enterId = 0;
    
	SMG_Clear();
    setCursor(entPos+i);
    do
    {
        keyMapChar = _getKeyMap( keyPad_Event() );
        switch (keyMapChar)
        {
        case 'D':   // �˸�ɾ��
            enterBuff_backspace();
            if(i>0) i--;
            break;
        case '>':
        case '<':
            exit = 1;
            break;
        case 'E':   // ȷ������
            exit = 1;
            break;  
        
        case 0:
            // 0 Ϊû�а�������������
            break;
        
        default:    // �������水��
            if(i<8)
            {
                enterBuff_add(keyMapChar);
                i++;
            }
            break;
        }
        if(keyMapChar != 0)
        {
            SMG_Clear();
            SMG_print(&enterBuffer[0],entPos);
            setCursor(entPos+i);
            Beep_On(5);
        }

    } while (!exit);
    
    if(keyMapChar == 'E' && enterId !=0 )
    {
        return enterBuffer;
    }
    else
    {
        return NULL;
    }
}


void strtoNum(char *str)
{
    atoi(str);
}

