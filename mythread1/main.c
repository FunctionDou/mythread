/*************************************************************************
    > File Name: main.c
    > Author: Function_Dou
    > Mail: NOT
    > Created Time: 2019年01月01日 星期二 22时14分07秒
 ************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int thread[3] = {0};
int current_thread = 0;
void switch_to(int current_thread);

void thread1()
{
    while(1)
    {
        printf("thread1\n");
        sleep(1);
        switch_to(2);
    }
}

void thread2()
{
    while(1)
    {
        printf("thread2\n");
        sleep(1);
        switch_to(1);
    }
}

void thread_start(int current_thread)
{
    if(current_thread == 1)
    {
        thread1();
    }
    else if(current_thread == 2)
    {
        thread2();
    }
}


int main()
{
    // 1024是自己设置的一个值, 1kb的大小足够线程栈使用空间了
    int thread1[1024] = {0};
    int thread2[1024] = {0};
    thread[1] = (int)(thread1+1013);
    thread[2] = (int)(thread2+1013);

    /*--------- 线程1 ---------*/

    // 创建 thread1 线程
    // 初始 switch_to 函数栈帧
    int n = 1013;
    for(int i = 0; i < 8; i++)
        thread1[++n] = i;   // 这一句现在要不要都是一样的, 重要的是下面的三句

    // 返回的是 thread_start 的地址
    // thread_start 函数栈帧，刚进入 thread_start 函数的样子 
    thread1[n++] = (int)thread_start;

    // thread_start 执行结束，线程结束
    thread1[n++] = -1; 

    // thread_start 函数的参数
    thread1[n++] = 1; 
  

    /*----------- 线程2 ----------*/

    // 创建 thread2 线程
    // 初始 switch_to 函数栈帧
    n = 1013;
    for(int i = 0; i < 8; i++)
        thread2[++n] = i;   // 这一句现在要不要都是一样的, 重要的是下面的三句

    // 返回的是 thread_start 的地址
    // thread_start 函数栈帧，刚进入 thread_start 函数的样子 
    thread2[n++] = (int)thread_start;

    // thread_start 执行结束，线程结束
    thread2[n++] = -1; 

    // thread_start 函数的参数
    thread2[n++] = 2; 
  
    switch_to(1);  
}

