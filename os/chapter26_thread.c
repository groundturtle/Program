/*
 * @Author: avert-win
 * @Date: 2022-06-07 17:12:47
 * @LastEditTime: 2022-06-07 19:09:18
 * @FilePath: /os/chapter26_thread.c
 * @Description: pthread_create(), pthread_join(), strerror(), and system call's wrappint.
 *      to pass things between threads, use type `void*`.
 *      `thread_join()` get value returned by start_routine and copy it into the second param.
 * @LastEditors: avert-win
 */
#include<stdio.h>
#include<assert.h>
#include<pthread.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>  // getpid(): implicit declaration.
#include<string.h>  // strerror: implicit declaration.

// claiming volatile cannot prevent the concurrent modifying error.
volatile int counter = 0;

/**
 * @description: pthread_create with error message print.
 * @param (pthread_t *thread, NULL, void *start_routine, void *arg)
 *  `void *start_routine` means a function pointer which function returns a void pointer.
 *  `void *start_routine(void *arg)` means a function pointer which function returns a void pointer 
 *      and takes a void pointer as param. For argument, it's not neccesary.
 * @return {*}
 */
int Pthread_create(pthread_t *p, const pthread_attr_t *attr,
                    void *start_routine,  void *arg)
{
    int ret = pthread_create(p, attr, start_routine, arg);
    if(ret!=0)
    {
        printf("creat thread failed: %s.\n", strerror(errno));
    }
    return ret;
}

/**
 * @description: thread's start routine. you can get a return value of thread from this function by using `pthread_join()`.
 * @param {void} *arg
 * @return {*}
 */
void *run(void *arg)
{
    printf("get arg: %s.\n", (char*)arg);
    // counter would not be wrong until i up to 1.0e+8.
    for(int i=0; i<100000000; i++)
        counter++;
    return (void*)-1;
}

int main()
{
    pthread_t p1, p2;
    int ret=0, result=0;
    printf("main begin, pid: %d.\n", getpid());
    ret = Pthread_create(&p1, NULL, run, "A");
    assert(ret==0);
    ret = Pthread_create(&p2, NULL, run, "B");
    assert(ret==0);
    ret = pthread_join(p1, NULL);
    assert(ret==0);
    ret = pthread_join(p2, (void**)&result);
    assert(ret==0);
    printf("child return: %d.\n", result);
    printf("counter: %d.\n", counter);
}