/*
 * @Author: Aolun Xie
 * @Date: 2020-06-11 15:39:05
 * @Last Modified by: Aolun Xie
 * @Last Modified time: 2020-06-12 16:54:34
 */

#include "Out_print.h"
extern MEMORY* memory;

int Out_print_register(int ID, REGISTER *reg)
{
    WaitForSingleObject(printmutex, INFINITE);
    int *ax = reg->ax;
    printf("\nid = %d\n", ID);
    printf("ip = %hd\n", *reg->ip);
    printf("flag = %hd\n", *reg->flag);
    printf("ir = %hd\n", *reg->ir);
    printf("ax1 = %d ax2 = %d ax3 = %d ax4 = %d\n", ax[0], ax[1], ax[2], ax[3]);
    printf("ax5 = %d ax6 = %d ax7 = %d ax8 = %d\n", ax[4], ax[5], ax[6], ax[7]);
    ReleaseMutex(printmutex);
    return 1;
}

int Out_print_code(MEMORY *sta)
{
    int i = 0, j = 0;
    printf("\ncodeSegment :\n");
    for (j = 0; j < 16; j++)
        for (i = 0; i < 8; i++)
        {
            printf("%d", Pre_memory_read(sta ));
            sta = sta + 2;
            if(i<7)
                printf(" ");
            else
                printf("\n");
        }
    return 1;
}

int Out_print_data(MEMORY *sta)
{
    sta += ORIGIN_OF_DATA / 2;
    int i = 0, j = 0;
    printf("\ndataSegment :\n");
    for (j = 0; j < 16; j++)
        for (i = 0; i < 16; i++)
        {
            printf("%hd", *(sta ));
            sta++;
            if(i<15)
                printf(" ");
            else
                printf("\n");
        }
    return 1;
}

void Out_end(void)
{
    free(memory);
    memory = NULL;
}