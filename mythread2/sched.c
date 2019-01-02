/*************************************************************************
    > File Name: sched.c
    > Author: Function_Dou
    > Mail: NOT
    > Created Time: 2019年01月02日 星期三 00时01分41秒
 ************************************************************************/

#if 0

最终写完应该会有所感觉, 应该将pthread_create()等除了sched()函数写在一个文件里面, 比如: thread.c 中,
毕竟他们功能主要是执行线程创建, 而不是调度, 与该文本名有一点不搭.

最重要的是执行后你会发现 thread_start() 函数被调用, 但是函数下面的操作并没有被执行, 所以原本线程被调度之后还能被重新执行. 同时你也应该注意到 申请的空间也并没有被释放, 
会造成内存泄漏, 因该在 thread_start() 中同时释放掉内存.

同时调度也没有真正的封装好, 让用户直接去调用我们的 switch_to() 调用函数总的还是不安全, 也很暴露我们
实现过程, 需要对调度有一个简单的封装, 封装就肯定使用函数来封装罗.


以上都是现在的不足, 所以我们下一个版本就来解决这些问题

#endif

#include "sched.h"
#include <stdlib.h>

#define EX 8

/*-------- 全局变量 ----*/

// init_struct : 建立的一个空的线程, 当没有其他可执行的线程的时候就可以执行它
task_struct	  init_struct = {0,NULL,  0, {0}};

// 当前执行的线程
task_struct * current = &init_struct;	

// 建立一个线程表, 最多允许 TASK_SIZE 个线程被创建
task_struct * task_table[TASK_SIZE] = {&init_struct};	



/*----------- 函数 ---------*/

// 线程调度
task_struct * sched()
{
    int tid = current->id;
    while(1)
    {
        tid = (tid+1 < TASK_SIZE) ? tid+1 : (tid+1)%TASK_SIZE;
        if(task_table[tid])
        {
            break;
        }
    }
    return task_table[tid];
}

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

    new_thread->id = tid;
    new_thread->esp = (int)(new_thread->stack + STACK_SIZE - 11);
    new_thread->thread_func = thread_func;

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

// 线程启动
void thread_start(task_struct *task)
{
    task->thread_func();
    printf("start\n");
    task_table[task->id] = NULL;
    switch_to(sched());
}
