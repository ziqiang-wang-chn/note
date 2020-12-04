#include "stdio.h"
#include "stdlib.h"
/**
 * kmp的prefix数组的求法
 *  1. 当两符号相同，则数组此处值等于前指针的下标值+1，并且两指针同时后移
 *  2. 当两符号不同，前指针只能回退到大于0的位置，这时候比较，如果不同则数组此处值=0，并只后移后指针
 *                                                   如果相同则数组此处值=前指针的下标值+1，并后移两指针
 **/
void getPrefixArr(char* char_arr, int* prefix_arr, int size) {
    int i = 0, j = 1;
    prefix_arr[0] = 0;
    while (j < size)
    {
        while (char_arr[i] != char_arr[j] && i > 0)
        {
            i = prefix_arr[i-1];
        }
        if(char_arr[i] == char_arr[j]) {
            prefix_arr[j] = i + 1;
            i++;
            j++;
        }else {
            prefix_arr[j] = 0;
            j++;
        }
    }
}

int main (void) {
    int x[9];
    getPrefixArr("aabaabaaa", x, 9);

    return 0;
}