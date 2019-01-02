/*************************************************************************
    > File Name: pthread.c
    > Author: Function_Dou
    > Mail: NOT
    > Created Time: 2019年01月02日 星期三 12时56分31秒
 ************************************************************************/

#include "pthread.h"
#include <stdlib.h>

#define EX 8

// 线程设置的函数调用
static void thread_start(task_struct *);

/*-------- 全局变量 ----*/

// init_struct : 建立的一个空的线程, 当没有其他可执行的线程的时候就可以执行它
// 新增加了创建时为阻塞态
task_struct	init_struct = {0, NULL, 0,THREAD_BLOCK, 0, {0}};

// 当前执行的线程
task_struct * current = &init_struct;	

// 建立一个线程表, 最多允许 TASK_SIZE 个线程被创建
task_struct * task_table[TASK_SIZE] = {&init_struct};	


// 创建线程
int pthread_create(Pthread_t* thread_t, void (*thread_func)())
{
    int tid = -1;
    task_struct * new_thread = (task_struct *)malloc(sizeof(task_struct));
    if(!new_thread)
        // error_create("pthread_create error\n");
        return -1;

    while(++tid != TASK_SIZE && task_table[tid])
        ;
    if(tid == TASK_SIZE)
        return -1;
    task_table[tid] = new_thread;   // 赋予新的指针
    *thread_t = tid;

    new_thread->status = THREAD_BLOCK;  // 先设置线程的状态为阻塞态
    new_thread->id = tid;
    new_thread->esp = (int)(new_thread->stack + STACK_SIZE - 11);
    new_thread->thread_func = thread_func;
    new_thread->sleep_time = 0; // 线程初始睡眠时间设置为 0


    int *stack = new_thread->stack;
    int j = 1;
    stack[STACK_SIZE - j++] = (int)new_thread;  // 传入函数的参数
    stack[STACK_SIZE - j++] = -1;       // 为ret返回地址用的
    stack[STACK_SIZE - j++] = (int)thread_start;    // 函数的地址
    // 寄存器的值
    for(int i = 0; i < EX; i++)
        stack[STACK_SIZE - j++] = i;

    return 0;
}

void thread_start(task_struct * thread)
{
    if(thread)
    {
        thread->thread_func();
        thread->status = THREAD_EXIT;   // 状态设置为THREAD_EXIT 表示线程退出
    }
    schedule();
}

// 线程调度
int pthread_join(int tid)
{
    while(task_table[tid]->status != THREAD_EXIT)
    {
        schedule();
    }

    free(task_table[tid]);
    task_table[tid] = NULL;

    return 0;
}
