//
//  quicksort.c
//  230505 Algorithm qsort
//
//  Created by 한설 on 2023/05/06.
//

#include "quicksort.h"

static int median(int *arr, int l, int r);
static int median_of_medians(int *arr, int l, int r);
static void swap (int *a, int *b);

void q_sort(int *arr, int l, int r)
{
    int pivot;
    int i, j;
    if (l >= r)
        return;
    pivot = median_of_medians(arr, l, r);   //pivot값 설정
    swap((arr + l), (arr + pivot));
    pivot = l;
    i = l + 1;
    j = r;
    while(i <= j){
        while(i <= r && arr[i] <= arr[pivot])
            i++;
        
        while(j > l && arr[j] > arr[pivot])
            j--;
        
        if(i > j){
            swap(arr + j, arr + pivot);
        }
        else{
            swap(arr + i, arr + j);
        }
    }
    
    q_sort(arr, l, j - 1);
    q_sort(arr, j + 1, r);
}

int median(int *arr, int l, int r)
{
    int m = (r + l) / 2;
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
    left = median(arr, l, (r - l) / 3 + l);
    mid = median(arr, (r - l) / 3 + l + 1, (((r - l) / 3 * 2) + l));
    right = median(arr, (((r - l) / 3 * 2) + l) + 1, r);
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

void swap (int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
