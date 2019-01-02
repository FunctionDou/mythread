/*************************************************************************
    > File Name: main.c
    > Author: Function_Dou
    > Mail: NOT
    > Created Time: 2019年01月01日 星期二 22时14分07秒
 ************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sched.h"

void thread1()
{
    task_struct * next = NULL;
    while(1)
    {
        printf("thread1\n");
        sleep(1);
        next = sched();
        if(next)
            switch_to(next);
    }
}

void thread2()
{
    task_struct * next = NULL;
    while(1)
    {
        printf("thread2\n");
        sleep(1);
        next = sched();
        if(next)
            switch_to(next);
    }
}


int main()
{
    Pthread_t tid1, tid2;
    pthread_create(&tid1, thread1);
    pthread_create(&tid2, thread2);

    int i = 2;
    while(i--)
    {
        printf("main\n");
        sleep(1);
        task_struct* next = sched();
        if(next)
            switch_to(next);
    }

    exit(EXIT_SUCCESS);
}

