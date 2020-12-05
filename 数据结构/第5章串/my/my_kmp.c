#include "stdio.h"
#include "stdlib.h"
#include "string.h"
/**
 * kmp的prefix数组的求法
 *  1. 当两符号相同，则数组此处值等于前指针的下标值+1，并且两指针同时后移
 *  2. 当两符号不同，前指针只能回退到大于0的位置，这时候比较，如果不同则数组此处值=0，并只后移后指针
 *                                                   如果相同则数组此处值=前指针的下标值+1，并后移两指针
 * 
 * @param source: 源串
 * @param prefix_arr: 串的前缀表 （next_arr）
 * @param size: 前缀表的大小；源串的长度
 **/
void getPrefixArr(char* source, int* prefix_arr, int size) {
    int i = 0, j = 1;
    prefix_arr[0] = 0;
    while (j < size)
    {
        while (source[i] != source[j] && i > 0)
        {
            i = prefix_arr[i-1];
        }
        if(source[i] == source[j]) {
            prefix_arr[j] = i + 1;
            i++;
            j++;
        }else {
            prefix_arr[j] = 0;
            j++;
        }
    }
}

/**
 * kmp循环比较部分
 *      1. 当源串和目标串字符相等时，同时后移指针
 *      2. 当源串和目标串字符不等时，分两种情况，若j是指向的目标串的第一个字符，则指向源串的指针需要后移，因为这时候j已经无路可退，只能从源串的下一个字符开始比较
 *                                         若j不是指向目标穿的第一个字符，则j需要跳到j前面一个元素所代表值的位置开始比较，依据就是prefix_arr
 *      3. 当循环结束，若源串中存在目标串，则指向目标串的指针应该已经累加到与目标串相等，代表j已经把目标串遍历了一遍，此时i代表已经走到了在源串中的目标串的结尾位置，
 *                                                  j代表目标串的结尾位置，返回（i-j）是基于下标的值，返回(i-j+1)是基于位序的值，循环结束后i和j的指向如下
 * 
 *                                                                            i
 *                                                  source_index: 0 1 2 3 4 5 6 7 8 9
 *                                                        source: a a a b c a a b c a
 *                                                                        j
 *                                                       pattern: a b c a a
 *                                                 pattern_index: 0 1 2 3 4
 *                                                    prefix_arr: 0 0 0 1 0                res->  位序：(i-j+1) 下标：(i-j)
 * 
 *                   若原醋暗中不存在目标串，则j是不可能大于目标串的长度的，因为j根本就没有遍历完一遍目标串，此时代表匹配失败，返回-1即可
 * 
 * @param source： 源串
 * @param pattern: 目标串（匹配串）
 * @param prefix_arr: next_arr, 前缀表
 **/
int kmp(char* source, char* pattern, int* prefix_arr) {
    int i = 0, j = 0;
    while (i < strlen(source) && j < strlen(pattern))
    {
        if(source[i] == pattern[j]) {
            i++;
            j++;
        }else if(!j) {
            i++;
        }else {
            j = prefix_arr[j - 1];
        }
    }
    if(j >= strlen(pattern))
        return i - j + 1;
        else
        return -1;
}

int main (void) {
    char source[] = "aaabacaabvf";
    char pattern[] = "bacaa"; 
    int prefix_arr[strlen(pattern)];
 
    getPrefixArr(pattern, prefix_arr, strlen(pattern));
    printf("prefix arr : ");
    for (int i = 0; i < strlen(pattern); i++)
    {
        printf("%d ", prefix_arr[i]);
    }
    printf("\n");

    int res = kmp(source, pattern, prefix_arr);
    printf("res = %d", res);
    return 0;
}