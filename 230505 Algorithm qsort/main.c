//
//  main.c
//  230505 Algorithm qsort
//
//  Created by 한설 on 2023/05/05.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_CHAR_PER_LINE 100

int *filelead(char *name, int *n);
void filesave(int *a, int n);
void q_sort(int *arr, int l, int r, int n);
int median(int *arr, int l, int r);
int median_of_medians(int *arr, int l, int r);
void swap (int *a, int *b);

int main(int argc, const char * argv[]) {
    int *arr;
    int n = 0;
    
    arr = filelead("test.txt", &n);
    
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    
    q_sort(arr, 0, n - 1, n);


    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    filesave(arr, n);
    
    return 0;
}

int median(int *arr, int l, int r)
{
    int m = (r + l + 1) / 2;
    if (*(arr + l) > *(arr +r))              //l > r
    {
        if (*(arr + l) < *(arr + m))          //m > l > r
            return l;
        else {              //l > r, m <= l
            if(*(arr + m) > *(arr + r))       //r < m <= l
                return m;
            else            //m <= r <= l
                return r;
        }
    }
    else {              //l <= r
        if (*(arr + l) > *(arr + m))      //m < l <= r
            return l;
        else {          //r >= l, m >= l
            if (*(arr + m) < *(arr + r))  //r > m >= l
                return m;
            else        //m >= r >= l
                return r;
        }
    }
}

int median_of_medians(int *arr, int l, int r)
{
    int left, right, mid;
    left = median(arr, l, (l + r + 1) / 3);
    mid = median(arr, (l + r + 1) / 3 + 1, (l + r + 1) / 3 * 2);
    right = median(arr, ((l + r + 1) / 3 * 2) + 1, r + 1);
    if (*(arr + left) > *(arr + right))              //l > r
    {
        if (*(arr + left) < *(arr + mid))          //m > l > r
            return left;
        else {              //l > r, m <= l
            if(*(arr + mid) > *(arr + right))       //r < m <= l
                return mid;
            else            //m <= r <= l
                return right;
        }
    }
    else {              //l <= r
        if (*(arr + left) > *(arr + mid))      //m < l <= r
            return left;
        else {          //r >= l, m >= l
            if (*(arr + mid) < *(arr + right))  //r > m >= l
                return mid;
            else        //m >= r >= l
                return right;
        }
    }
}

void q_sort(int *arr, int l, int r, int n)
{
    int pivot;
    int i, j;
    if (l >= r)
        return;
    pivot = median_of_medians(arr, l, r);
    swap((arr + l), (arr + pivot));
    pivot = l;
    i = pivot + 1;
    j = r;
    while(i <= j){
        // 포인터가 엇갈릴때까지 반복
        while(i <= r && arr[i] <= arr[pivot]){
            i++;
        }
        while(j > l && arr[j] >= arr[pivot]){
            j--;
        }
        
        if(i > j){
            swap(arr + j, arr + pivot);
        }
        else{
            swap(arr + i, arr + j);
        }
    }
    q_sort(arr, l, j - 1, n);
    q_sort(arr, j + 1, r, n);
}

void swap (int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
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

void filesave(int *a, int n)
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
