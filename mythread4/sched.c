/*************************************************************************
    > File Name: sched.c
    > Author: Function_Dou
    > Mail: NOT
    > Created Time: 2019年01月02日 星期三 00时01分41秒
 ************************************************************************/

#include "pthread.h"
#include <stdio.h>

/*-------- 声明变量 ----*/

// init_struct : 建立的一个空的线程, 当没有其他可执行的线程的时候就可以执行它
extern task_struct	init_struct;

// 当前执行的线程
extern task_struct * current;	

// 建立一个线程表, 最多允许 TASK_SIZE 个线程被创建
extern task_struct * task_table[TASK_SIZE];	


/*----------- 函数 ---------*/

// 线程调度准备
task_struct * sched()
{
    int tid = current->id;
    while(1)
    {
        tid = (tid+1 < TASK_SIZE) ? tid+1 : (tid+1)%TASK_SIZE;
        if(task_table[tid] && getmytime() >= task_table[tid]->sleep_time &&  task_table[tid]->status != THREAD_EXIT)
        {
            task_table[tid]->sleep_time = 0;
            break;
        }
    }
    return task_table[tid];
}


// 线程调度
void schedule()
{
    task_struct* next = NULL;
    next = sched();
    if(next)
    {
        next->status = THREAD_RUNNING; // 线程被调度时, 将线程状态设置为运行态
        switch_to(next);
    }
}


// 设置线程睡眠时间
void pthread_sleep(mytime_t times)
{
    // 设置睡眠时间和线程的状态
    current->sleep_time = times + getmytime();
    current->status = THREAD_SLEEP;
    schedule();
}
