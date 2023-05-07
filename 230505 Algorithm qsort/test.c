//
//  test.c
//  230505 Algorithm qsort
//
//  Created by 한설 on 2023/05/06.
//

#include "quicksort.h"
#define MAX_CHAR_PER_LINE 100

static int *filelead(char *name, int *n);
static void filesave(char name[], int *a, int n);

void TC1_Twonumber(void)
{
    printf("TC1_Twonumber: \n");
    int *arr;
    int n = 0;
    
    arr = filelead("data1.txt", &n);
    
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    printf("정렬 후\n");
    q_sort(arr, 0, n - 1);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    filesave("result1.txt", arr, n);
}

void TC2_fiftynumber(void)
{
    printf("TC2_fiftynumber: \n");
    int *arr;
    int n = 0;
    
    arr = filelead("data2.txt", &n);
    
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    printf("정렬 후\n");
    q_sort(arr, 0, n - 1);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    filesave("result2.txt", arr, n);
}

void TC3_hundrednumber(void)
{
    printf("TC2_hundrednumber: \n");
    int *arr;
    int n = 0;
    
    arr = filelead("data3.txt", &n);
    
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    printf("정렬 후\n");
    q_sort(arr, 0, n - 1);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    filesave("result3.txt", arr, n);
}


int *filelead(char *name, int *n)
{
    int count = 1;
    char str[100], *a;
    int num, *arr;
    FILE *fp;                                   //파일 포인터
    fp = fopen(name, "r");                          //파일 읽기
    arr = (int*)malloc(sizeof(int) * 3);        //3칸 메모리 할당
    if (fp == NULL)
        printf("파일이 없습니다.\n");
    else if(fp != NULL) {
        while(fgets(str, MAX_CHAR_PER_LINE, fp)) {    //한줄씩 읽어들이고
            a = strtok(str, " ");
            while (a != NULL) {
                if ((*n % 3) == 0 && !(*n == 0)) {      //n을 3으로 나눴을 때 나머지가 없고, (3의 배수) n이 0이 아닐 때
                    count += 1; //count를 1 늘리고
                    arr = realloc(arr, sizeof(int) * (count * 3));    //초기값이 3칸이므로 조건을 처음 만족했을 때 6칸 다음은 9칸. 3의 배수로 칸을 늘려간다.
                }
                num = atoi(a);                      //Ascii형태 int형으로 형변환
                *(arr + *n) = num;                    //arr배열의 n번째 칸에 point 대입
                *n = *n + 1;                            //반복할때마다 +1 (숫자 개수 파악)
                a = strtok(NULL, " ");                   //공백기준 토큰화
            }
        }
        fclose(fp);
    }
    return arr;
}

void filesave(char name[], int *a, int n)
{
    char **ia;
    ia = (char**)malloc(sizeof(char*) * n);
    for (int i = 0; i < n; i++)
    {
        ia[i] = (char*)malloc(sizeof(char) * 10);
    }
    for (int i = 0; i < n; i++)
        sprintf(ia[i], "%d", a[i]);
    FILE *fp = fopen("result.txt", "w");    //파일 쓰기 모드로 open
    for(int i = 0; i < n; i++)
    {
        fputs(ia[i], fp);
        fputs(" ", fp);
    }
    fclose(fp); //파일 닫기
    free(a);
}
