

## 实现线程切换

### 环境

如果`make`之后出现无法编译的情况, 那么可能缺少了`-m32`条件的环境.

#### 解决

缺少链接32位的环境, ubuntu中需要下载

```shell
sudo apt-get install build-essential module-assistant
sudo apt-get install gcc-multilib g++-multilib
```

需要使用32位环境时, 在gcc选项中加上`-m32`就行.



### 文件

`mythread0` 是函数调用, 理解函数调用进而理解线程调用

`mythread1`最开始的线程调用

`mythread2`加上了简单的封装

`mythread3`添加了pthread_join功能

`mythread4`线程定时, 遗憾的是没有加上真正的时间片, 只能用定时来代替时间片



### CSDN博客

https://blog.csdn.net/Function_Dou/article/list/1
