/*************************************************************************
    > File Name: error.c
    > Author: Function_Dou
    > Mail: NOT
    > Created Time: 2019年01月02日 星期三 15时39分42秒
 ************************************************************************/

#include "error.h"

void error_exit(const char *str)
{
    fprintf(stderr, "%s", str);
    exit(0);
}
