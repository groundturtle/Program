/*
 * @Author: avert-win
 * @Date: 2022-06-07 15:02:45
 * @LastEditTime: 2022-06-07 21:04:37
 * @FilePath: /os/chapter5_syscall.c
 * @Description: exec(), fork(), wait(), and pid.
 * @LastEditors: avert-win
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/wait.h>
#include<string.h>
#include"syswrap.hpp"

int main(int argc, char  *argv[])
{
    printf("pid: %d\n", (int)getpid());
    int ret = Fork();
    if(ret == 0)
    {
        printf("Child pid: %d\n", (int)getpid());
        printf("Child's parent's pid: %d\n", (int)getppid());

        // if no any child, return -1.
        ret = wait(0);
        printf("child wait return %d.\n", ret);
        // load a new program.
        // note the type of args and the first element must be equal to the first argument.
        char *args[4];
        args[0] = strdup("ls");     // strdup(): copy string.
        args[1] = strdup("-l");
        args[2] = strdup("-a");
        args[3] = NULL;
        execvp(args[0], args);
        printf("this will never be print out.");
    }
    else
    {
        printf("Parent pid: %d\n", (int)getpid());
        //param=0: child with group ID(getpid());  param=-1: child;   param<-1: child group ID(abs(param))
        ret = (int)wait(0);
        // waitpid(pid_t pid);
        printf("reap child: %d", ret);
    }
}