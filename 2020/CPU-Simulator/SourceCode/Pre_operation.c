/*
 * @Author: Aolun Xie
 * @Date: 2020-06-11 10:25:33
 * @Last Modified by: Aolun Xie
 * @Last Modified time: 2020-06-11 15:38:39
 */

#include "Pre_operation.h"
extern MEMORY* memory;

int Pre_memory_write(MEMORY *loc, int data)
{
    *(loc) = (data >> 16);  // 将前16位存入*(loc)中.
    *(loc + 1) = (data);    // 将后16位存入*(loc+10)中.
    return 1;
}

int Pre_memory_read(MEMORY *loc)
{   // 65 535 = 0000 0000 0000 0000 1111 1111 1111 1111.
    int result1, result2, a = 65535;
    result1 = *(loc), result2 = *(loc + 1);
    return ((result1 << 16) + (result2 & a));
}   // result2 & a 是为了负数类型转换时,0~15位产生的影响.

int Pre_translate(char *s)
{
    int i, translate = 0;
    for (i = 0; i < 32; i ++ )
    {
        translate = 2 * translate + s[i] - '0';
    }
    return translate;
}

int Pre_load(FILE *file,int ID )
{   // translate:存放指令对应的10进制整数; index:计数变量
    char s[35];
    int translate = 1, index = 0;
    rewind(file);
    if(ID == 1)
    {
        while(translate != 0)
        {
            translate = Pre_translate(fgets(s, 34, file));
            Pre_memory_write(memory + index, translate);
            index += 2;
        }
    }
    else
    {
        while(translate != 0)
        {
            translate = Pre_translate(fgets(s, 34, file));
            Pre_memory_write(memory + index + ORIGIN_OF_INSTRUCTION2 / 2, translate);
            index += 2;
        }
    }
    return 1;
}

MEMORY *Pre_memory_creat(int size_unit, int lenth)
{
    MEMORY *memory;
    int i;
    memory = (short *)malloc(size_unit * lenth);
    memset(memory, 0, size_unit * lenth);   // 内存初始值: 0;
    for (i = 0; i < HUMTEX_NUM; i++)    // 建立dataSegment互斥锁
    {
        hmutex[i] = CreateMutex(NULL, FALSE, NULL);
    }
    return memory;
}