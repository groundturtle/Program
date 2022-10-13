/*
 * @Author: avert-win
 * @Date: 2022-06-07 19:10:52
 * @LastEditTime: 2022-06-09 10:29:42
 * @FilePath: /os/chapter27_mutex.c
 * @Description: 
 *      pthread_join() must take a `pthread_t` to indicate which thread to
 *      wait, while pthread_create takes a `pthread_t*` as param to assignment.
 *      pthread_join() take a `void**` type param to set return value, while 
 *      pthread_create() take `void*` as start routine and arguments.
 *      可简单记为pthread_create全部需要一个指针，pthread_join需要一个线程号和一个二重指针。
 * @LastEditors: avert-win
 */
#include<pthread.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<stdio.h>
#include"syswrap.hpp"

//* 注意锁的初始化。条件变量不需要。
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

//! never return pointer that pointing things on thread's stack!
void *start(void *arg)
{
    printf("arg: %s\n", (char*)arg);
    char *tmp = strndup((char*)arg, 2);
    char *ret = malloc(3);
    memset((void*)ret, 0, 3);
    for(int i=0; i<2; i++)
    {
        ret[i] = tmp[i];
    }
    return (void*)ret;
}

void count(int *x)
{
    Pthread_mutex_lock(&lock);
    for(int i=0; i<100000000; i++)
        (*x)++;
    Pthread_mutex_unlock(&lock);
}

int main()
{
    pthread_t p1, p2, p3;
    int counter = 0;
    /* return value */
    char *arg1 = "abcdefg";
    char *ret1 = NULL;
    Pthread_create(&p1, NULL, (void*)start, (void*)arg1);
    Pthread_join(p1, (void**)&ret1);
    printf("thread 1 return: %s.\n", (char*)ret1);

    /* lock and unlock */
    Pthread_create(&p2, NULL, count, &counter);
    Pthread_create(&p3, NULL, count, &counter);
    Pthread_join(p2, NULL);
    Pthread_join(p3, NULL);
    printf("counter = %d.\n", counter);
}