/*
 * @Author: Aolun Xie
 * @Date: 2020-06-11 15:38:50
 * @Last Modified by: Aolun Xie
 * @Last Modified time: 2020-06-12 16:49:50
 */

#ifndef _OUT_PRINT_H
#define _OUT_PRINT_H

#include "Pre_operation.h"

//输出寄存器此时状态
int Out_print_register(int ID, REGISTER *reg);

//输出代码段内存
int Out_print_code(MEMORY *sta);

//输出数据段内存
int Out_print_data(MEMORY *sta);

//释放内存并摧毁互斥锁
void Out_end(void);

#endif
