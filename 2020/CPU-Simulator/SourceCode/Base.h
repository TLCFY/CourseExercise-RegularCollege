/*
 * @Author: Aolun Xie
 * @Date: 2020-06-12 16:48:47
 * @Last Modified by:   Aolun Xie
 * @Last Modified time: 2020-06-12 16:48:47
 */

#ifndef _BASE_H
#define _BASE_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>

#define MAX_HUMTEX 279
/*
 *这个常量为：本程序可申请的，内存互斥锁最大数量;
 *当申请数超过这个常量时，gcc-x86将会报错：[Unknown/Just-In-Time compiled code] (未知源:0);
 *尚不清楚这个常量存在的原理，猜测其与编译器/操作系统有关;
*/

#define TICKETS_NUM 100                     //数据段内存起始单元中存放的数字，此处意为“火车票数”

#define LENTH_OF_MEMORY 20000               //内存单元数量
#define ORIGIN_OF_INSTRUCTION1 0            //子线程1指令段内存的起点为0
#define ORIGIN_OF_INSTRUCTION2 256          //子线程2指令段内存的起点为256
#define ORIGIN_OF_DATA 16384                //数据端内存的起点为16384(10)  4000(16)
#define HUMTEX_NUM 256                      //申请的dataSegment互斥锁数量。
#define MEMORY short                        //内存的变量类型

//指令解码后的结构
typedef struct INSTRUCTION
{
    short oper_code;                        //操作码
    short oper_num1;                        //操作对象1
    short oper_num2;                        //操作对象2
    short num;                              //立即数
} INSTRUCTION;
//传递寄存器的结构
typedef struct REGISTER
{
    short *ip;
    short *flag;
    short *ir;
    int *ax;
    int *istop;
} REGISTER;

MEMORY *memory = NULL;  //模拟内存的起始地址;
HANDLE printmutex;      //寄存器输出互斥锁
HANDLE hmutex[128];     //datasegment互斥锁;



#endif
