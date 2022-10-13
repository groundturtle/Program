/*
 * @Author: avert-win
 * @Date: 2022-06-07 15:57:48
 * @LastEditTime: 2022-06-07 18:56:15
 * @FilePath: /os/chapter14_memory.c
 * @Description: malloc(), free(), and strcpy().
 * @LastEditors: avert-win
 */
#include<stdlib.h>     // only for checking, not necessary.
#include<stdio.h>
#include<string.h>

int main()
{
    int *arr = malloc(20*sizeof(int));
    char *tmp = "abc";
    //! never change pointer from malloc before calling free!
    char *s = malloc(strlen(tmp)+1);
    // without initialize, there may be something strange but not zero(which is safe).
    memset(s, 0, strlen(tmp)+1);
    // strcpy before malloc can cause overflow(or not), never do!
    strcpy(s, tmp);
    // malloc get a param of size, but free not.
    free(s);
    printf("%s\n",s);
}