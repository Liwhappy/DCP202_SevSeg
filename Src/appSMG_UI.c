#include "appSMG_UI.h"

#define ENTER_BUFFER_SIZE 10
// char enterBuffer[ENTER_BUFFER_SIZE];
// uint8_t enterId = 0;

typedef struct
{
    char buff[ENTER_BUFFER_SIZE];
    uint8_t size;
} enterBuff_typedef;

enterBuff_typedef entBuff;

/***�����ַ�ӳ���***/
const uint8_t KeyMap[16] = {
    'F', '7', '8', '9',
    'S', '4', '5', '6',
    '<', '1', '2', '3',
    '>', 'D', '0', 'E'};


// ���������б��л�ȡ�İ����ַ���
uint8_t get_entBuff_length(void)
{
    return entBuff.size;
}

/***����������ת��Ϊ�����ַ�ӳ���***/
uint8_t _getKeyMap(uint8_t keyID)
{
    if (keyID > 0 && keyID <= 16)
    {
        return KeyMap[keyID - 1];
    }
    else
    {
        return 0;
    }
}

/***�������ַ�ӳ�䣬ת��Ϊ��������***/
uint8_t _keyMap2KeyID(uint8_t kMapStr)
{
    uint8_t i = 0;
    for (i = 0; i < 16; i++)
    {
        if (KeyMap[i] == kMapStr)
        {
            return i + 1;
        }
    }
    return 0;
}

void setCursor(uint8_t curId)
{
    if (curId >= SMG_ITEMS)
        return;

    SMG_BuffWrite(SMG_ITEMS - curId - 1, ~0x08);
}

/**
 * @description: ��������buffer�ڴ�������
 * @param str:���뱣����ַ�
 * @return {*}
 */
void enterBuff_add(char str)
{
    if (entBuff.size < 8)
    {
        entBuff.buff[entBuff.size++] = str;
    }
}

/**
 * @description: ��������buffer��ɾ��1������
 * @return {*}
 */
void enterBuff_backspace(void)
{
    if (entBuff.size > 0)
    {
        entBuff.buff[entBuff.size--] = 0;
    }
}

/**
 * @description: ����������ݻ����ڵ�����
 * @return {*}
 */
void enterBuff_clean(void)
{
    memset(entBuff.buff, 0, ENTER_BUFFER_SIZE); // ������뻺��
    entBuff.size = 0;
}

/**
 * @brief  ��������ȴ�����
 * @param  entPos:������ʼλ
 * @param  maxEnter:��������ַ�����
 * @param  keyEvent:��ǰ����ֵ������ getKeyLast()������ȡ
 * @param  EnterType:�������ַ�����
 *      @arg ENTER_TYPE_ALL: ��������
 *      @arg ENTER_TYPE_NUM: ֻ������������
 * @retval None
 */
char *ui_WaitEnter(uint8_t entPos, uint8_t maxEnter, uint8_t keyEvent, uint8_t EnterType)
{
    uint8_t keyMapChar;

    // �״ε���ִ��
    if (entBuff.size == 0)
    {
        enterBuff_clean();
        SMG_CleanPos(entPos, maxEnter);
        setCursor(entPos);
    }
    // ת��Ϊ�����ַ�����
    keyMapChar = _getKeyMap(keyEvent);

    switch (keyMapChar)
    {
    case 0:
        // 0 Ϊû�а�������������
        break;
    case 'D': // �˸�ɾ��
        enterBuff_backspace();
        break;
    case 'E': // ȷ������
        if (entBuff.size > 0)
        {
            entBuff.size = 0;
            return entBuff.buff;
        }
        else
        {
            return NULL;
        }
        break;

    default: // ������case���⣬��Ҫ���밴�������ڵ��ַ�
        if (entBuff.size < maxEnter)
        {
            // �ַ������֣�����������ΪALL �������ӵ�buff
            if (isdigit(keyMapChar) ||
                EnterType == ENTER_TYPE_ALL)
            {
                enterBuff_add(keyMapChar);
            }
        }
        break;
    }

    // ˢ����ʾ
    if (keyMapChar != 0)
    {
        SMG_CleanPos(0,maxEnter);
        SMG_print(entBuff.buff, entPos);
        if(entBuff.size < maxEnter)
            setCursor(entPos + entBuff.size);
        Beep_On(5);
    }
    
    return NULL;
}
/*****************************************
char* ui_WaitEnter(uint8_t entPos, uint8_t maxEnter, uint8_t EnterType)
{
    uint8_t i=0,exit = 0;
    uint8_t keyMapChar;

    enterId = 0;

    SMG_CleanPos(0,maxEnter);
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
            if(i<maxEnter)
            {
                if(EnterType == ENTER_TYPE_NUM)
                {
                    if( isdigit(keyMapChar))
                    {
                        enterBuff_add(keyMapChar);
                        i++;
                    }
                }
                else if(EnterType == ENTER_TYPE_ALL)
                {
                    enterBuff_add(keyMapChar);
                    i++;
                }
            }
            break;
        }
        if(keyMapChar != 0)
        {
            SMG_CleanPos(0,maxEnter);
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
*/


