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

/***按键字符映射表***/
const uint8_t KeyMap[16] = {
    'F', '7', '8', '9',
    'S', '4', '5', '6',
    '<', '1', '2', '3',
    '>', 'D', '0', 'E'};


// 返回输入列表中获取的按键字符数
uint8_t get_entBuff_length(void)
{
    return entBuff.size;
}

/***将按键编码转换为按键字符映射表***/
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

/***将按键字符映射，转换为按键编码***/
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

__WEAK void UI_setCursor(uint8_t curId)
{
    // if (curId >= SMG_ITEMS)
    //     return;

    // SMG_BuffWrite(SMG_ITEMS - curId - 1, ~0x08);
}

/**
 * @description: 键盘输入buffer内存入数据
 * @param str:输入保存的字符
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
 * @description: 键盘输入buffer内删除1个数据
 * @return {*}
 */
void enterBuff_backspace(void)
{
    if (entBuff.size > 0)
    {
        entBuff.buff[entBuff.size-1] = 0;
				entBuff.size --;
    }
}

/**
 * @description: 清除键盘数据缓存内的数据
 * @return {*}
 */
void enterBuff_clean(void)
{
    memset(entBuff.buff, 0, ENTER_BUFFER_SIZE); // 清空输入缓存
    entBuff.size = 0;
}

/**
 * @brief  : 按键输入等待方法
 * @param  entPos: 输入起始位
 * @param  yLine: 用户输入的行号
 * @param  maxEnter: 最大输入字符数量
 * @param  keyEvent: 当前按键值，可由 KeyPad_getLastEvent() 一类函数获取
 * @param  EnterType: 可输入字符类型
 *      @arg ENTER_TYPE_ALL: 所有类型
 *      @arg ENTER_TYPE_NUM: 只允许数字类型
 * @retval char* 返回按键输入字符串数组。如输入为空，则返回NULL
 * @History  // 历史修改记录
      <author>  <time>   <version >   <desc>
      kimiyang  5/30        1.2       添加yLine行号参数，为适配点阵显示屏 
 */
char *ui_WaitEnter(uint8_t entPos, uint8_t yLine , uint8_t maxEnter, uint8_t keyEvent, uint8_t EnterType)
{
    uint8_t keyMapChar;

    // 首次调用执行
    if (entBuff.size == 0)
    {
        enterBuff_clean();
        // SMG_CleanPos(entPos, maxEnter);
        UI_CLEARPOS(entPos,yLine,maxEnter);
        // UI_setCursor(entPos);
        UI_SETCURSOR(entPos + entBuff.size,yLine);
    }
    // 转换为按键字符编码
    keyMapChar = _getKeyMap(keyEvent);

    switch (keyMapChar)
    {
    case 0:
        // 0 为没有按键，不作处理
        break;
    case 'D': // 退格删除
        enterBuff_backspace();
        break;
    case 'E': // 确认输入
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

    default: // 除以上case以外，需要存入按键缓存内的字符
        if (entBuff.size < maxEnter)
        {
            // 字符是数字，或输入类型为ALL 清空下添加到buff
            if (isdigit(keyMapChar) ||
                EnterType == ENTER_TYPE_ALL)
            {
                enterBuff_add(keyMapChar);
            }
        }
        break;
    }

    // 刷新显示
    if (keyMapChar != 0)
    {
        // SMG_CleanPos(0,maxEnter);
        UI_CLEARPOS(entPos,yLine,maxEnter);
        // SMG_print(entBuff.buff, entPos);
        UI_PRINT(entPos,yLine,entBuff.buff);
        if(entBuff.size < maxEnter)
            // UI_setCursor(entPos + entBuff.size);
            UI_SETCURSOR(entPos + entBuff.size,yLine);
        Beep_On(5);
    }
    
    return NULL;
}


