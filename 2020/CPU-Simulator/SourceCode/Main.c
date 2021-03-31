/*
 * @Author: Aolun Xie
 * @Date: 2020-06-11 15:41:46
 * @Last Modified by: Aolun Xie
 * @Last Modified time: 2020-06-12 17:15:30
 */

#include "Main.h"

  //仅有oper1有效时,与立即数运算
unsigned Main_core1(void )
{
    int ax[8] = {0, 0, 0, 0, 0, 0, 0, 0};      //寄存器1~8;
    short ip = 0, flag = 0, ir = 0;            //程序计数器,标志寄存器,指令寄存器;
    int istop = 0;                             //停机变量.值为1时停机;
    REGISTER reg;
    reg.ax = ax, reg.flag = &flag, reg.ip = &ip, reg.ir = &ir, reg.istop = &istop;

    FILE *file = NULL;                         //开始加载指令
    INSTRUCTION ins;
    file = fopen("..\\TestData\\dict1.dic", "r");
    Pre_load(file, 1);
    fclose(file);
    file = NULL;                               //指令加载结束.所有指令都进入内存中

    while (istop != 1)                         //当istop = 0 时,读取指令、分析指令、执行指令、打印寄存器
    {
        ins = Main_read_instruction(1, &reg); //读取并分析指令
        Main_run_instruction(1, ins, &reg);   //执行指令
        Out_print_register(1, &reg);          //打印寄存器
    }

    return 0;
}
unsigned Main_core2(void )
{
    int ax[8] = {0, 0, 0, 0, 0, 0, 0, 0};      //寄存器1~8;
    short ip = 0, flag = 0, ir = 0;            //程序计数器,标志寄存器,指令寄存器;
    int istop = 0;                             //停机变量.值为1时停机;
    REGISTER reg;
    reg.ax = ax, reg.flag = &flag, reg.ip = &ip, reg.ir = &ir, reg.istop = &istop;

    FILE *file = NULL;                         //开始加载指令
    INSTRUCTION ins;
    file = fopen("..\\TestData\\dict2.dic", "r");
    Pre_load(file, 2);
    fclose(file);
    file = NULL;                               //指令加载结束.所有指令都进入内存中

    while (istop != 1)                         //当istop = 0 时,读取指令、分析指令、执行指令、打印寄存器
    {
        ins = Main_read_instruction(2, &reg); //读取并分析指令
        Main_run_instruction(2, ins, &reg);   //执行指令
        Out_print_register(2, &reg);          //打印寄存器
    }

    return 0;
}
int Main_instruction_data(int ID, short oper1, short oper2, short num, REGISTER *reg)
{
    if(oper2 == 0)  //仅有oper1有效时,与立即数运算
    {
        (reg->ax)[oper1 - 1] = num;
    }
    else if(oper1 <= 4)  //oper1为数据寄存器时
    {
        (reg->ax)[oper1 - 1] = *(memory + (reg->ax)[oper2 - 1] / 2);
        return 1;
    }
    else    //oper1为地址寄存器时
    {
        *(memory + (reg->ax)[oper1 - 1] / 2) = (reg->ax)[oper2 - 1];
        return 1;
    }
    return 1;
}
int Main_instruction_calculate_1(int ID, short oper1, short oper2, short num, REGISTER *reg)
{
    if(oper2 == 0)  //仅有oper1有效时,与立即数运算
    {
        (reg->ax)[oper1 - 1] += num;
        return 1;
    }
    else
    {
        (reg->ax)[oper1 - 1] += *(memory + (reg->ax)[oper2 - 1] / 2);
        return 1;
    }
}
int Main_instruction_calculate_2(int ID, short oper1, short oper2, short num, REGISTER *reg)
{
    if(oper2 == 0)  //仅有oper1有效时,与立即数运算
    {
        (reg->ax)[oper1 - 1] -= num;
        return 1;
    }
    else
    {
        (reg->ax)[oper1 - 1] -= *(memory + (reg->ax)[oper2 - 1] / 2);
        return 1;
    }
}
int Main_instruction_calculate_3(int ID, short oper1, short oper2, short num, REGISTER *reg)
{
    if(oper2 == 0)
    {
        (reg->ax)[oper1 - 1] *= num;
        return 1;
    }
    else
    {
        (reg->ax)[oper1 - 1] *= *(memory + (reg->ax)[oper2 - 1] / 2);
        return 1;
    }
}
int Main_instruction_calculate_4(int ID, short oper1, short oper2, short num, REGISTER *reg)
{
    if(oper2 == 0)  //仅有oper1有效时,与立即数运算
    {
        (reg->ax)[oper1 - 1] /= num;
        return 1;
    }
    else
    {
        (reg->ax)[oper1 - 1] /= *(memory + (reg->ax)[oper2 - 1] / 2);
        return 1;
    }
}
int Main_instruction_bool_and(int ID, short oper1, short oper2, short num, REGISTER *reg)
{
    if(oper2 == 0)  //仅有oper1有效时,与立即数运算
    {
        (reg->ax)[oper1 - 1] = ((reg->ax)[oper1 - 1] && num);
        return 1;
    }
    else
    {
        (reg->ax)[oper1 - 1] = ((reg->ax)[oper1 - 1] && *(memory + (reg->ax)[oper2 - 1] / 2));
        return 1;
    }
}
int Main_instruction_bool_or(int ID, short oper1, short oper2, short num, REGISTER *reg)
{
    if(oper2 == 0)  //仅有oper1有效时,与立即数运算
    {
        (reg->ax)[oper1 - 1] = ((reg->ax)[oper1 - 1] || num);
        return 1;
    }
    else
    {
        (reg->ax)[oper1 - 1] = ((reg->ax)[oper1 - 1] || *(memory + (reg->ax)[oper2 - 1] / 2));
        return 1;
    }
}
int Main_instruction_bool_not(int ID, short oper1, short oper2, short num, REGISTER *reg)
{
    if(oper2 == 0)  //仅有oper1有效时,与立即数运算
    {
        (reg->ax)[oper1 - 1] = !(reg->ax)[oper1 - 1];
        return 1;
    }
    else
    {
        *(memory + (reg->ax)[oper2 - 1] / 2) = !*(memory + (reg->ax)[oper2 - 1] / 2);
        return 1;
    }
}
int Main_instruction_compare(int ID, short oper1, short oper2, short num, REGISTER *reg){
    if(oper2 == 0){  //仅有oper1有效时,与立即数运算
        if(oper1 <= 4){
            if((reg->ax)[oper1 - 1] > num){
                *(reg->flag) = 1;
                return 1;
            }
            else if((reg->ax)[oper1 - 1] < num){
                *(reg->flag) = -1;
                return -1;
            }
            else{
                *(reg->flag) = 0;
                return 0;
            }
        }
        else{
            if(*(memory + (reg->ax)[oper1 - 1] / 2) > num){
                *(reg->flag) = 1;
                return 1;
            }
            else if(*(memory + (reg->ax)[oper1 - 1] / 2) < num){
                *(reg->flag) = -1;
                return -1;
            }
            else{
                *(reg->flag) = 0;
                return 0;
            }
        }
    }
    else{  //与地址寄存器指向单元运算
        if((reg->ax)[oper1 - 1] > *(memory + (reg->ax)[oper2 - 1] / 2)){
            *(reg->flag) = 1;
            return 1;
        }
        else if((reg->ax)[oper1 - 1] < *(memory + (reg->ax)[oper2 - 1] / 2)){
            *(reg->flag) = -1;
            return -1;
        }
        else{
            *(reg->flag) = 0;
            return 0;
        }
    }
}
int Main_instruction_jump(int ID, short oper1, short oper2, short num, REGISTER *reg)
{
    switch(oper2)
    {
        case 0:    //无条件跳转
            *reg->ip += num;
            break;
        case 1:    //寄存器为0跳转
            *(reg->flag) == 0 ? (*reg->ip += num) : (*reg->ip += 4);
            break;
        case 2:    //寄存器为1跳转
            *(reg->flag) == 1 ? (*reg->ip += num) : (*reg->ip += 4);
            break;
        case 3:    //寄存器为-1跳转
            *(reg->flag) == -1 ? (*reg->ip += num) : (*reg->ip += 4);
            break;
        default :  //未知的跳转码!程序出错!
            printf("Fail to jump ip! Please check the flag!\n"), *reg->istop = 1;
    }
    return 1;
}
int Main_instruction_in(int ID, short oper1, short oper2, short num, REGISTER *reg)
{
        printf("in:\n");
        scanf("%d", &(reg->ax)[oper1 - 1]);
        return 1;
}
int Main_instruction_out(int ID, short oper1, short oper2, short num, REGISTER *reg)
{
    printf("id = %d    ", ID);//打印ID
    if(oper1 <= 4)
    {
        printf("out: %d", (reg->ax)[oper1 - 1]);
        printf("\n");
        return 1;
    }
    else
    {
        printf("out: %d", *(memory + (reg->ax)[oper1 - 1] / 2));
        printf("\n");
        return 1;
    }
}
int Main_instruction_lock(int ID, short oper1, short oper2, short num, REGISTER *reg)
{
    WaitForSingleObject(hmutex[num - ORIGIN_OF_DATA], INFINITE);
    return 0;
}
int Main_instruction_unlock(int ID, short oper1, short oper2, short num, REGISTER *reg)
{
    ReleaseMutex(hmutex[num - ORIGIN_OF_DATA]);
    return 0;
}
int Main_instruction_sleep(int ID, short oper1, short oper2, short num, REGISTER *reg)
{
    Sleep(num);
    return 0;
}
INSTRUCTION Main_read_instruction(int ID, REGISTER *reg)
{   //利用位运算进行指令的拆分
    INSTRUCTION ins;
    short a = -256; //BIN: 1111 1111 0000 0000   DEC:-256
    short b = 240;  //BIN: 0000 0000 1111 0000   DEC: 240
    short c = 15;   //BIN: 0000 0000 0000 1111   DEC:  15
    if(ID == 1)
    {
        *reg->ir = *(memory + (*reg->ip / 2));          //读取指定指令
        ins.num = *(memory + 1 + (*reg->ip / 2));       //读取立即数
    }
    else
    {
        *reg->ir = *(memory + (*reg->ip / 2) + ORIGIN_OF_INSTRUCTION2 / 2);          //读取指定指令
        ins.num = *(memory + 1 + (*reg->ip / 2) + ORIGIN_OF_INSTRUCTION2 / 2);       //读取立即数
    }
    ins.oper_code = ((a & *reg->ir) >> 8);  //取操作码
    ins.oper_num1 = ((b & *reg->ir) >> 4);  //取操作数1
    ins.oper_num2 = ((c & *reg->ir) >> 0);  //取操作数2
    if(ins.oper_code != 10){
        *reg->ip += 4;      //非跳转指令 ip += 4
    }
    return ins;
}
int Main_run_instruction(int ID, INSTRUCTION ins, REGISTER *reg)
{
    switch(ins.oper_code)  //根据不同的操作码执行对应的指令函数
    {
        case 0:
            *reg->istop = 1;
            break;
        case 1:
            Main_instruction_data(ID, ins.oper_num1, ins.oper_num2, ins.num, reg);
            break;
        case 2:
            Main_instruction_calculate_1(ID, ins.oper_num1, ins.oper_num2, ins.num, reg);
            break;
        case 3:
            Main_instruction_calculate_2(ID, ins.oper_num1, ins.oper_num2, ins.num, reg);
            break;
        case 4:
            Main_instruction_calculate_3(ID, ins.oper_num1, ins.oper_num2, ins.num, reg);
            break;
        case 5:
            Main_instruction_calculate_4(ID, ins.oper_num1, ins.oper_num2, ins.num, reg);
            break;
        case 6:
            Main_instruction_bool_and(ID, ins.oper_num1, ins.oper_num2, ins.num, reg);
            break;
        case 7:
            Main_instruction_bool_or(ID, ins.oper_num1, ins.oper_num2, ins.num, reg);
            break;
        case 8:
            Main_instruction_bool_not(ID, ins.oper_num1, ins.oper_num2, ins.num, reg);
            break;
        case 9:
            Main_instruction_compare(ID, ins.oper_num1, ins.oper_num2, ins.num, reg);
            break;
        case 10:
            Main_instruction_jump(ID, ins.oper_num1, ins.oper_num2, ins.num, reg);
            break;
        case 11:
            Main_instruction_in(ID, ins.oper_num1, ins.oper_num2, ins.num, reg);
            break;
        case 12:
            Main_instruction_out(ID, ins.oper_num1, ins.oper_num2, ins.num, reg);
            break;
        case 13:
            Main_instruction_lock(ID, ins.oper_num1, ins.oper_num2, ins.num, reg);
            break;
        case 14:
            Main_instruction_unlock(ID, ins.oper_num1, ins.oper_num2, ins.num, reg);
            break;
        case 15:
            Main_instruction_sleep(ID, ins.oper_num1, ins.oper_num2, ins.num, reg);
            break;
        default :
            printf("Error instruction!\n"), *reg->istop = 1;    //出现未知的操作码!立即停机.
    }
    return 0;
}
