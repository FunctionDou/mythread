/*************************************************************************
    > File Name: sched.h
    > Author: Function_Dou
    > Mail: NOT
    > Created Time: 2019年01月01日 星期二 23时43分36秒
 ************************************************************************/

#ifndef __INCLUDE_SCHED
#define __INCLUDE_SCHED


#define STACK_SIZE 1024	// 线程栈空间
#define TASK_SIZE 64	// 最大线程数

#define Pthread_t int

enum STATUS
{
	THREAD_RUNNING = 1,
	THREAD_BLOCK = 2,
	THREAD_SLEEP = 3,
	THREAD_EXIT = 4,
};

typedef struct task_struct
{
	int id;
	void (*thread_func)();
	int esp;
	int status;
	int stack[STACK_SIZE];
}task_struct;


/*---------- 函数 ---------*/ 

void switch_to(task_struct *next);

// 切换线程
task_struct * sched();

// 创建线程
int pthread_create(Pthread_t *, void (*thread_func)());

// 线程等待
int pthread_join(int);

// 线程调度
void schedule();

#endif

