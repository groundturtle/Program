/*
 * @Author: avert-win
 * @Date: 2022-06-07 21:58:00
 * @LastEditTime: 2022-06-09 10:47:34
 * @FilePath: /os/chapter30_cond.c
 * @Description: 
 *      调用pthread_cond_signal()发送信号时，只有一个线程会收到信号（且随机），因此有pthread_cond_broadcast()来代替；
 *      调用pthread_cond_wait()时，总是假设已经得到了锁、并将在其内部得到信号前释放锁、得到信号后重新加回锁并重新判断执行条件。
 * @LastEditors: avert-win
 */
#include<stdio.h>
#include<assert.h>
#include"syswrap.hpp"
#include"produ_consu.hpp"

static pthread_cond_t space, fill;     // 缓冲区有新空余信号和缓冲区有新元素信号；
static pthread_mutex_t mutex;

/**
 * @description: 
 *      in each loop, first lock, and try putting element. If buffer filled, 
 *      release the lock and wait for space signal.
 *      once get signal, lock(in wait) and check space again. If still any 
 *      space, put an element, unlock, and go to next loop.
 * @param {void} *arg: the number of elements producer should put in buffer.
 * @return {*}
 */
void *producer(void *arg)
{
    int loops = (int)arg;
    for(int i=0; i<loops; i++)
    {
        Pthread_mutex_lock(&mutex);
        while(count == MAX)
            Pthread_cond_wait(&space, &mutex);
        put(i);
        Pthread_cond_signal(&fill);
        Pthread_mutex_unlock(&mutex);
    }
}

/**
 * @description: 
 *      in each loop, first lock, and try getting element. If buffer filled, 
 *      release the lock and wait for space signal.
 *      once get signal, lock(in wait) and check element again. If still
 *      any element, get one from buffer, unlock, and go to next loop.
 * @param {void} *arg: the number of elements consumer should get from buffer.
 * @return {*}
 */
void *consumer(void *arg)
{
    int loops = (int)arg;
    for(int i=0; i<loops; i++)
    {
        Pthread_mutex_lock(&mutex);
        while(count == 0)
            Pthread_cond_wait(&fill, &mutex);
        int tmp = get();
        Pthread_cond_signal(&space);
        Pthread_mutex_unlock(&mutex);
        printf("get: %d from buffer.\n", tmp);
    }
}

int main()
{
    pthread_t p1, p2;
    Pthread_create(&p1, NULL, producer, (void*)10000);
    Pthread_create(&p2, NULL, consumer, (void*)10000);
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);
}