//
//  main.c
//  230505 Algorithm qsort
//
//  Created by 한설 on 2023/05/05.
//

#include "quicksort.h"

extern void TC1_Twonumber(void);
extern void TC2_fiftynumber(void);
extern void TC3_hundrednumber(void);
static void checktime(void(*func)(void));

int main(int argc, const char * argv[]) {
    checktime(TC1_Twonumber);
    checktime(TC2_fiftynumber);
    checktime(TC3_hundrednumber);
    return 0;
}

void checktime(void(*func)(void))
{
    clock_t start, finish;
    double duration;
    start = clock();
    (*func)();
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("\n================%lf초입니다.================\n", duration);
}
