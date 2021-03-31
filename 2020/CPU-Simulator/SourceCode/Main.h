/*
 * @Author: Aolun Xie
 * @Date: 2020-06-11 11:07:27
 * @Last Modified by: Aolun Xie
 * @Last Modified time: 2020-06-12 16:50:10
 */

#ifndef _MAIN_H
#define _MAIN_H

#include "Out_print.h"

/*
 * 函数原型的参数:
 * ID:所在线程的编号;
 * oper1:操作对象1;
 * oper2:操作对象2;
 * num:立即数;
 * reg:所在处理核的寄存器,含停机变量;
*/

//数据传输指令
int Main_instruction_data(int ID, short oper1, short oper2, short num, REGISTER *reg);

//加法运算指令
int Main_instruction_calculate_1(int ID, short oper1, short oper2, short num, REGISTER *reg);

//减法运算指令
int Main_instruction_calculate_2(int ID, short oper1, short oper2, short num, REGISTER *reg);

//乘法运算指令
int Main_instruction_calculate_3(int ID, short oper1, short oper2, short num, REGISTER *reg);

//整数除法运算指令
int Main_instruction_calculate_4(int ID, short oper1, short oper2, short num, REGISTER *reg);

//逻辑与运算指令
int Main_instruction_bool_and(int ID, short oper1, short oper2, short num, REGISTER *reg);

//逻辑或运算指令
int Main_instruction_bool_or(int ID, short oper1, short oper2, short num, REGISTER *reg);

//逻辑非运算指令
int Main_instruction_bool_not(int ID, short oper1, short oper2, short num, REGISTER *reg);

//比较运算指令
int Main_instruction_compare(int ID, short oper1, short oper2, short num, REGISTER *reg);

//跳转指令
int Main_instruction_jump(int ID, short oper1, short oper2, short num, REGISTER *reg);

//输入指令
int Main_instruction_in(int ID, short oper1, short oper2, short num, REGISTER *reg);

//输出指令
int Main_instruction_out(int ID, short oper1, short oper2, short num, REGISTER *reg);

//锁住立即数指向的内存
int Main_instruction_lock(int ID, short oper1, short oper2, short num, REGISTER *reg);

//解锁立即数指向的内存
int Main_instruction_unlock(int ID, short oper1, short oper2, short num, REGISTER *reg);

//休眠立即数毫秒
int Main_instruction_sleep(int ID, short oper1, short oper2, short num, REGISTER *reg);

//根据程序计数器取指令,分析指令.
INSTRUCTION Main_read_instruction(int ID, REGISTER *reg);

//执行当前程序寄存器中的指令
int Main_run_instruction(int ID, INSTRUCTION ins, REGISTER *reg);

//线程1
unsigned Main_core1(void );

//线程2
unsigned Main_core2(void );

#endif
