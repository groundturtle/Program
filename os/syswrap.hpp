/*
 * @Author: avert-win
 * @Date: 2022-06-07 21:01:55
 * @LastEditTime: 2022-06-09 10:17:37
 * @FilePath: /os/syswrap.hpp
 * @Description: 简介
 * @LastEditors: avert-win
 */
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>      // fork(), excevp(),
#include<string.h>
#include<errno.h>
#include<stdio.h>

int Fork()
{
    int ret = fork();
    if(ret < 0)
    {
        printf("fork error! %s\n", strerror(errno));
    }
    return ret;
}

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

// to recieve value returned by thread, you must pass a void** 
// type variable as argument, and the argument's value must be
// the address of the address.
int Pthread_join(pthread_t p, void **thread_return)
{
    int ret = pthread_join(p, thread_return);
    if(ret!=0)
    {
        printf("thread_join failed: %s.\n", strerror(errno));
    }
    return ret;
}

int Pthread_mutex_init(pthread_mutex_t *mutex, void *attr)
{
    int ret = pthread_mutex_init(mutex, attr);
    if(ret!=0)
    {
        printf("mutex init fail: %s.\n", strerror(errno));
    }
    return ret;
}

int Pthread_mutex_lock(pthread_mutex_t *mutex)
{
    int ret = pthread_mutex_lock(mutex);
    if(ret!=0)
    {
        printf("lock failed: %s.\n", strerror(errno));
    }
    return ret;
}

int Pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    int ret = pthread_mutex_unlock(mutex);
    if(ret!=0)
    {
        printf("unlock failed: %s.\n", strerror(errno));
    }
    return ret;
}

int Pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    int ret = pthread_cond_wait(cond, mutex);
    if(ret!=0)
    {
        printf("condition wait failed: %s.\n", strerror(errno));
    }
    return ret;
}

int Pthread_cond_signal(pthread_cond_t *cond)
{
    int ret = pthread_cond_signal(cond);
    if(ret!=0)
    {
        printf("condition signal failed: %s.\n", strerror(errno));
    }
    return ret;
}

int Pthread_cond_broadcast(pthread_cond_t* cond)
{
    int ret = pthread_cond_broadcast(cond);
    if(ret != 0)
    {
        printf("condition broadcast failed: %s.\n", strerror(errno));
    }
    return ret;
}