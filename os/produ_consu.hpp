/*
 * @Author: avert-win
 * @Date: 2022-06-09 10:47:12
 * @LastEditTime: 2022-06-09 10:47:12
 * @FilePath: /os/produ_consu.hpp
 * @Description: 简介
 * @LastEditors: avert-win
 */
#include<assert.h>

#define MAX 10

int buffer[MAX];
int put_n = 0;      // 历史上放入缓冲区的元素总数；
int use = 0;        // 历史上曾经从缓冲区取出的元素总数；
int count = 0;      // 缓冲区现余元素总数；

void put(int value)
{
    assert(count != MAX);
    buffer[put_n] = value;
    put_n = (put_n+1) % MAX;
    count ++;
}

int get()
{
    assert(count != 0);
    int tmp = buffer[use];
    use = (use+1) % MAX;
    count --;
    return tmp;
}
