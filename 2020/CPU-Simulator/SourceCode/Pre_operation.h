/*
 * @Author: Aolun Xie
 * @Date: 2020-06-11 15:38:17
 * @Last Modified by: Aolun Xie
 * @Last Modified time: 2020-06-12 16:49:27
 */

#ifndef _PRE_OPERATION_H
#define _PRE_OPERATION_H

#include "Base.h"

//将 4 字节的int型数据存入 2 个 MEMORY型内存单元中
//将data中数据存入地址为loc,loc+1的内存单元中
int Pre_memory_write(MEMORY *loc, int data);

//从 2 个相邻的MEMORY型内存单元中读取出 1 个 4 字节的int型数据
//地址为loc的单元存放int型数据的0~15位,地址为loc+1的单元存放int型数据的16~31位
int Pre_memory_read(MEMORY *loc);

//将s中的字符串转换为一个整数
//s为从文件中读取的一行 32 位指令
//返回值所对应的 32 位二进制数,与s字符串内容相同
int Pre_translate(char *s);

//从指定文件中加载代码至代码段内存;
//ID为core编号(线程编号)
int Pre_load(FILE *file,int ID );

//创建并初始化模拟内存及dataSegment对应互斥锁
//size_unit:内存单元大小/byte;lenth:内存单元数量/个
MEMORY *Pre_memory_creat(int size_unit, int lenth);

#endif
