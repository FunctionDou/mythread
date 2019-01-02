/*************************************************************************
  > File Name: main.c
  > Author: Function_Dou
  > Mail: NOT
  > Created Time: 2019年01月01日 星期二 22时14分07秒
 ************************************************************************/

#if 0

这一次我们基本解决了上一个版本的问题, 通过添加了线程的状态实现线程安全的退出和释放. 当然我们这个真正实现是单道批处理的功能, 并不是真正意义上实现的多线程, 所以线程的调用放在了 pthread_join() 函数里面进行调用的, 也就是想要运行线程就一定要调用该函数才行, 而且处理的顺序也跟调用函数的顺序是一致的, 但是我们想要模仿的操作系统中线程调度是没有顺序可言, 是根据线程所占的时间片进行调度啊, 那么在下一节我们就应该来实现基于时间片的调度

#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pthread.h"

void thread1()
{
    printf("thread1\n");
    sleep(1);
    schedule();  // 要调度的话, 每个线程都因该加上
    printf("thread11\n");
}

void thread2()
{
    printf("thread2\n");
    sleep(1);
    schedule();  // 要调度的话, 每个线程都因该加上
    printf("thread22\n");
}


int main()
{
    Pthread_t tid1, tid2;
    pthread_create(&tid1, thread1);
    printf("create1\n");
    pthread_create(&tid2, thread2);
    printf("create2\n");

    int i = 3;
    while(--i)
    {
        printf("main\n"); 
        sleep(1);
        schedule();  // main中可加可不加
    }
    printf("join\n");
    pthread_join(tid1);
    printf("join1\n");
    pthread_join(tid2);
    printf("join2\n");

    exit(EXIT_SUCCESS);
}

