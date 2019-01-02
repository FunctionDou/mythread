/*************************************************************************
  > File Name: main.c
  > Author: Function_Dou
  > Mail: NOT
  > Created Time: 2019年01月01日 星期二 22时14分07秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pthread.h"

void thread1()
{
    {
        printf("thread1\n");
        pthread_sleep(5000);
        printf("weakup1\n");
    }
}

void thread2()
{
    {
        printf("thread2\n");
        pthread_sleep(3000);
        printf("weakup2\n");
    }
}


int main()
{
    Pthread_t tid1, tid2;
    pthread_create(&tid1, thread1);
    pthread_create(&tid2, thread2);

    {
        printf("main\n"); 
        pthread_sleep(1000);
        printf("weakup_main\n");
    }
    printf("join\n");
    pthread_join(tid1);
    printf("join1\n");
    pthread_join(tid2);
    printf("join2\n");

    exit(EXIT_SUCCESS);
}

