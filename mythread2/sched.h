/*************************************************************************
    > File Name: sched.h
    > Author: Function_Dou
    > Mail: NOT
    > Created Time: 2019年01月01日 星期二 23时43分36秒
 ************************************************************************/

#ifndef __INCLUDE_SCHED
#define __INCLUDE_SCHED

#include <stdio.h>

#define STACK_SIZE 1024
#define TASK_SIZE 16

#define Pthread_t int

typedef struct task_struct
{
	int id;
	void (*thread_func)();
	int esp;
	int stack[STACK_SIZE];

}task_struct;





/*---------- 函数 ---------*/ 

void switch_to(task_struct *next);

// 切换线程
task_struct * sched();

// 创建线程
int pthread_create(Pthread_t *, void (*thread_func)());

// 线程启动
void thread_start(task_struct *);

#endif

