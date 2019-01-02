/*************************************************************************
    > File Name: mytime.h
    > Author: Function_Dou
    > Mail: NOT
    > Created Time: 2019年01月02日 星期三 15时30分29秒
 ************************************************************************/

#ifndef INCLUDE_MYTIME
#define	INCLUDE_MYTIME

#include <sys/time.h>
#include "error.h"

#define mytime_t unsigned int

// 获取当前的时间
mytime_t getmytime();


#endif

