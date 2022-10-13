/*
 * @Author: avert-win
 * @Date: 2022-06-09 10:18:42
 * @LastEditTime: 2022-06-09 16:04:46
 * @FilePath: /os/chapter31_sema.c
 * @Description: 简介
 * @LastEditors: avert-win
 */
#include<semaphore.h>
#include"produ_consu.hpp"
#include"syswrap.hpp"

#define INIT 1

// sem_wait() 减少信号量的值，等待其恢复为非负；调用者依时间排序。
// sem_post() 增加信号量的值。
// sem_init(sem_t*, pshared, value)
    // 第一个是要初始化的信号量指针，第二个0指明多线程共享，第三个为初始值。
    // 要保证让哪个线程先运行起来，决定了需要设置的初始值。

/*
 * 1
 * 信号量用作锁（二值信号量）
 * 将信号量的值初始化为1，即可保证任何线程正在临界区运行时，另一线程对信号量的
 * sem_wait()操作都会引起信号量的值减一到-1，从而该线程休眠等待其他线程的sem_post().
 */

/*
 * 2
 * 信号量用作条件变量
 * 当一个线程需要等待另一个线程完成某些操作时，就可以使用条件变量或信号量。
 * 通过设置信号量的初始值，可以实现特定的等待顺序。例如若要子线程先运行，
 * 则使用0作为初始值，并让父进程调用sem_wait()等待。
 * 
 ? 用信号量实现条件变量的功能比想象起来更复杂、更容易出现缺陷。
 */

/* 
 * 3
 * 信号量用于生产者/消费者问题 
 * 用一个信号量表示空余、一个信号量表示拥有，其总和相当于一个线程安全、准确无误的的计数器。
 * 使用一个额外的二值信号量作为锁，以保证对缓冲区的正确操作。
 */

/*
 * 4
 * 读者/写者问题
 * 对于读者而言，只要没有写者在工作，就能够并发地进行；否则需要等待写者工作完成；
 * 但对于写者而言，不但要等待其它写者工作完，还要等待读者也全部工作完，因此需要等待两个信号量。
 * 在书上的实现中，对于读者的等待，由（第一个）读者对写锁的获取和（最后一个）读者对写锁的释放完成，因此写者不需要关心读者工作。
 */

/*
 * 5
 * 哲学家就餐问题
 * 假设有五个哲学家围着圆桌，每两人间有一支叉子，只有停下思考且同时拿到两只叉子的人才能
 * 吃到饭。如何设计程序，使尽可能多的哲学家能够同时吃饭、并且保证没有任何人被饿死（除非他
 * 自己的思考出了问题）？
 * 显然，如果让每个哲学家依次拿取左右两只叉，就可能会出现每个人手里只有一只叉的死锁情况。
 * 一种简单的解决办法是直接让哲学家们以不同的顺序拿叉，例如让第5人先拿右再拿左，其它人照旧。
 ? 类似的问题有很多，未必具有什么实用意义，但肯定有助于理解并发的本意。
 */
sem_t empty;
sem_t full;
sem_t mutex;

void *producer(void *arg)
{
    for(int i=0; i<(int)arg; i++)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        put(i);
        sem_post(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *arg)
{
    for(int i=0; i<(int)arg; i++)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        int tmp = get();
        sem_post(&mutex);
        sem_post(&empty);
        printf("get: %d.\n", tmp);
    }
}

int main(int argc, char *argv[])
{
    /*
     注意信号量的初始化：只能在主函数中、创建新线程前；信号量的初始值因用途而异。
     empty信号量代表剩余空位，因此一开始就应该是最大值；
     full信号量代表缓冲区所有元素，因此开始应该是0；注意这并不代表有多个线程可以同时
        向缓冲区填充东西，对缓冲区的操作仍然需要另外的锁(mutex).
     mutex信号量用作锁，因此初始化应该是1，即只有一个线程能首先通过它的允许得到运行，
        当第二个线程试图运行时，sem_wait()首先使其减一，此时就为负了，不可运行。
    */
    //!如果不对信号量进行初始化，可能会出现意想不到的情况！
    sem_init(&empty, 0, MAX);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    pthread_t p1, p2, p3;
    Pthread_create(&p1, NULL, producer, (void*)10000);
    Pthread_create(&p2, NULL, consumer, (void*)5000);
    Pthread_create(&p3, NULL, consumer, (void*)5000);
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);
    Pthread_join(p3, NULL);
}