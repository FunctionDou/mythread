/*************************************************************************
    > File Name: mytime.c
    > Author: Function_Dou
    > Mail: NOT
    > Created Time: 2019年01月02日 星期三 15时33分34秒
 ************************************************************************/

#include "mytime.h"

#include <stdio.h>

// 获取当前的时间
mytime_t getmytime()
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL) != 0)
        error_exit("gettimeofday error\n");

    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
