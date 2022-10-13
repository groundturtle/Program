/*
 * @Author: avert-win
 * @Date: 2022-06-09 16:05:55
 * @LastEditTime: 2022-06-09 16:25:42
 * @FilePath: /os/chapter31_imple_sem.c
 * @Description: 
 ?  利用条件变量和锁，实现一个没有负计数功能的信号量（符合现代linux系统）。
 * @LastEditors: avert-win
 */
#include<stdlib.h>
#include"syswrap.hpp"

/**
 * What a semaphore need is just a set of a value, a condition, and a lock. 
 */
typedef struct zem_t
{
    int value;
    pthread_cond_t cond;
    pthread_mutex_t lock;
} zem_t;

/**
 * @brief init the semaphore. 
 * Init the value, lock and condition of semaphore.
 * There is always only one thread that call this function, which usually is main.
 * @param s 
 * @param value 
 */
void zem_init(zem_t *s, int value)
{
    s->value = value;
    pthread_cond_init(&s->cond, NULL);
    Pthread_mutex_init(&s->lock, NULL);
}

/**
 * @brief lock and wait the condition.
 * because you lock first, that exist no more than one thread can be in waiting
 * the condition(or say its signal), so you can make sure that the thread call
 * this funtion earliest will be the first that get the signal.
 * Once you get the signal, release the lock and allow other threads to wait for
 * semaphore's value being non-negative.
 */
void zem_wait(zem_t *s)
{
    Pthread_mutex_lock(&s->lock);
    while(s->value <= 0)
        Pthread_cond_wait(&s->cond, &s->lock);
    s->value--;
    Pthread_mutex_unlock(&s->lock);
}

/**
 * @brief lock and increase the value of semaphore without waiting, and then send 
 * a signal to one of the threads that are waiting.
 */
void zem_post(zem_t *s)
{
    Pthread_mutex_lock(&s->lock);
    s->value++;
    Pthread_cond_signal(&s->cond);
    Pthread_mutex_lock(&s->lock);
}