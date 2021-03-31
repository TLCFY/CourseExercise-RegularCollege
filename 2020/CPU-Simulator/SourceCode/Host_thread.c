/*
 * @Author: Aolun Xie
 * @Date: 2020-06-11 16:07:49
 * @Last Modified by: Aolun Xie
 * @Last Modified time: 2020-06-12 16:51:49
 */

#include "Main.h"

int main(void)
{
    //预备
    memory = Pre_memory_creat(sizeof(MEMORY), LENTH_OF_MEMORY);
    *(memory + ORIGIN_OF_DATA / 2) = TICKETS_NUM; //设定初始值为10;
    HANDLE hthread1,hthread2;
    unsigned a = 1, b = 2; //the thread_id;
    //运行
    hthread1 = (HANDLE)_beginthreadex(NULL, 0, Main_core1, NULL, 0, &a); //start core1 thread;
    hthread2 = (HANDLE)_beginthreadex(NULL, 0, Main_core2, NULL, 0, &b); //start core2 thread;
    WaitForSingleObject(hthread1, INFINITE);
    CloseHandle(hthread1);
    WaitForSingleObject(hthread2, INFINITE);
    CloseHandle(hthread2);
    //输出
    Out_print_code(memory);
    Out_print_data(memory);
    //结束
    Out_end();
    return 0;
}
