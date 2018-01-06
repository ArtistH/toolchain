# 1. strace && ltrace简介
    / strace	跟踪程序的每个系统调用
    \ ltrace	跟踪程序的库函数调用

    eg. 
	strace ./a.out
	ltrace ./a.out
	 
    同样的ltrace也可以把系统调用都打印出来, 使用-S参数
	ltrace -S ./a.out
  
 
# 2. ltrace/strace的耗时
 
    ## ltrace -c dd if=/dev/urandom of=/dev/null count=1000
    1000+0 records in
    1000+0 records out
    512000 bytes (512 kB) copied, 2.31346 seconds, 221 kB/s
    % time     seconds  usecs/call     calls      function
    ------ ----------- ----------- --------- --------------------
    84.88    4.942763        4942     1000 read
    9.41    0.548195         548      1000 write
    5.06    0.294716         294      1001 memcpy
    0.11    0.006365        2121         3 __fprintf_chk
    0.09    0.004969        4969         1 dcgettext
    0.08    0.004850         808         6 strlen
    0.05    0.002667        2667         1 setlocale
    0.04    0.002579         644         4 sigaction
    0.03    0.001869         467         4 close
    0.03    0.001825         912         2 open64
    0.03    0.001519         759         2 malloc
    0.02    0.001187         593         2 __sprintf\_chk
    0.02    0.001176         588         2 clock\_gettime
    0.02    0.001169         389         3 __errno_location
    0.02    0.001012         506         2 dcngettext
    0.01    0.000814         814         1 lseek64
    0.01    0.000757         757         1 getopt_long
    0.01    0.000744         744         1 textdomain
    0.01    0.000742         247         3 strchr
    0.01    0.000634         634         1 __strtoull\_internal
    0.01    0.000602         602         1 getpagesize
    0.01    0.000542         271         2 localeconv
    0.01    0.000340         340         1 fclose
    0.01    0.000300         300         1 memmove
    0.00    0.000228         114         2 sigismember
    0.00    0.000184         184         1 getenv
    0.00    0.000170          85         2 sigaddset
    0.00    0.000148          74         2 free
    0.00    0.000093          93         1 bindtextdomain
    0.00    0.000090          90         1 sigemptyset
    0.00    0.000090          90         1 __cxa_atexit
    0.00    0.000088          88         1 __ctype\_b\_loc
    0.00    0.000074          74         1 __fpending
    ------ ----------- ----------- --------- --------------------
    100.00    5.823501                  3057 total
 
注:
使用-c选项, ltrace输出由进程创建的库调用, 输出结果以调用过程的时间为准进行排序.
因为是从urandom设备上读, 这是一种产生随机数的设备, 完成后写入null设备, 所以读过程花费了较多的时间.
使用ltrace去捕获运行时函数, 就好像在进程上系上了一个调试工具, 它占据了ltrace大量的时间, 这里ltrace一共消耗了5.8秒.
 
我们再来看一下strace所花费的时间, 如下:
 
strace -c dd if=/dev/urandom of=/dev/null count=1000
1000+0 records in
1000+0 records out
512000 bytes (512 kB) copied, 0.894482 seconds, 572 kB/s
Process 3049 detached
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 82.85    0.159393         159      1005           read
 15.07    0.028995          29      1003           write
  0.78    0.001494        1494         1           execve
  0.42    0.000814         136         6           rt_sigaction
  0.23    0.000446          41        11         1 close
  0.23    0.000435          73         6           fstat64
  0.21    0.000412          32        13           mmap2
  0.21    0.000408          29        14         6 open
  0.00    0.000000           0         1         1 access
  0.00    0.000000           0         3           brk
  0.00    0.000000           0         2           munmap
  0.00    0.000000           0         1           uname
  0.00    0.000000           0         4           mprotect
  0.00    0.000000           0         1           _llseek
  0.00    0.000000           0         1           rt_sigprocmask
  0.00    0.000000           0         1           getrlimit
  0.00    0.000000           0         1           set_thread_area
  0.00    0.000000           0         1           set_tid_address
  0.00    0.000000           0         2           clock_gettime
  0.00    0.000000           0         1           set_robust_list
------ ----------- ----------- --------- --------- ----------------
100.00    0.192397                  2078         8 total
 
注: 
strace一共消耗了0.19秒, strace把性能提升了30倍, 这主要是strace在跟踪系统调用的时候不需要动态库, 而ltrace是根据动态库来分析程序运行的.
所以ltrace也只能跟踪动态库, 不能跟踪静态库.


3) ltrace与strace的相同点

事实上我们用ltrace和strace都可以发现程序在哪个系统调用时发生了性能瓶径.
ltrace用-T, 而strace也用-T.
 
ltrace与strace都可以指定PID, 即对运行中的程序进行跟踪.
ltrace -p PID与strace -p PID
