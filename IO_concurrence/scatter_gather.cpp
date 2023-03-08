/**
 * @file scatter_gather.cpp
 * @author avert-win (avert@hnu.edu.cn)
 * @brief 从分散的多处读，或写到分散的多处，如果依次进行，会导致较多的系统调用和更大的代码量。
 *      使用结构体iovec（的数组）和一系列配套函数（如writev(), readv()）实现快速分散/聚集数据的I/O。
 * @version 0.1
 * @date 2023-03-08
 * @complexity:
 */

/**
 struct iovec{
    ptr_t iov_base;
    size_t iov_len;
 } 
 */

#include<stdio.h>
#include<unistd.h>
#include<sys/uio.h>

#define BUFSIZE 100

int main(){
    char buf1[BUFSIZE] = {0};
    char buf2[BUFSIZE] = {0};
    iovec iov[2];

    iov[0].iov_base = buf1;
    iov[1].iov_base = buf2;
    iov[0].iov_len = 3;         // 第一个缓冲区只接受3个字符（注意不是字节！）；
    iov[1].iov_len = BUFSIZE;   // 第二个缓冲区接满为止。

    int n = readv(STDIN_FILENO, iov, 3);    // 一次读入并分散到多处；
    printf("buf1: %s\n", buf1);
    printf("buf2: %s\n", buf2);

    return 0;
}