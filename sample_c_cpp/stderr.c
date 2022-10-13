/*
 * @Author: avert-win
 * @Date: 2022-05-26 21:46:43
 * @LastEditTime: 2022-05-26 21:58:08
 * @FilePath: \ProgramDaily\c_cppSample\stderr.c
 * @Description: 简介
 * @LastEditors: avert-win
 */
#include<unistd.h>  //fork
#include<errno.h>   //errno
#include<stdio.h>   //stderr

void unix_error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

pid_t Fork(void)
{
    pid_t pid;
    if((pid=fork()) <0 )
    {
        unix_error("fork error");
    }
    return pid;
}

int Write(int fd, char *msg, int size)
{
    int ret;
    if((ret=write(fd, msg, size)) < 0)
    {
        unix_error("write error");
    }
    return ret;
}

int main()
{
    pid_t pid = Fork();
}