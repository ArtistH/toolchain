# 1. strace && ltrace简介
    / strace	跟踪程序的每个系统调用
    \ ltrace	跟踪程序的库函数调用

    eg. 
	strace ./a.out
	ltrace ./a.out
	 
    ltrace也可以把系统调用都打印出来, 使用-S参数
	ltrace -S ./a.out
  
 
# 2. ltrace/strace的耗时
    ltrace -c dd if=/dev/urandom of=/dev/null count=1000   
    1000+0 records in   
    1000+0 records out  
    512000 bytes (512 kB) copied, 2.31346 seconds, 221 kB/s 
    % time     seconds  usecs/call     calls    function
    ------ ----------- ----------- --------- --------------------
    37.03     0.293652         293      1000    read
    34.89     0.276706         276      1000    write
    22.45     0.178077         178      1000    memcpy
    1.61      0.012749        6374         2    __fprintf_chk
    0.90      0.007102        7102         1    __overflow
    0.65      0.005148        2574         2    dcgettext
    0.38      0.002978        1489         2    clock_gettime
    0.34      0.002720         272        10    strlen
    0.26      0.002076        2076         1    setlocale
    0.22      0.001731         577         3    sigaction
    0.15      0.001167         291         4    close
    0.10      0.000807         269         3    localeconv
    0.08      0.000674         337         2    sigaddset
    0.08      0.000648         324         2    sigismember
    0.07      0.000591         295         2    __sprintf_chk
    0.07      0.000523         261         2    __freading
    0.06      0.000500         125         4    __errno_location
    0.06      0.000440         440         1    fclose
    0.06      0.000439         439         1    strrchr
    0.05      0.000374         187         2    open64
    0.04      0.000353         353         1    getenv
    0.04      0.000352         176         2    dup2
    0.04      0.000334         334         1    sigemptyset
    0.04      0.000333         333         1    __fpending
    0.04      0.000321         107         3    strchr
    0.04      0.000310         155         2    malloc
    0.04      0.000310         310         1    fileno
    0.04      0.000293         293         1    memmove
    0.03      0.000263         263         1    fflush
    0.03      0.000203         203         1    lseek64
    0.02      0.000164         164         1    __cxa_atexit
    0.02      0.000162         162         1    __strtoull_internal
    0.02      0.000126         126         1    getpagesize
    0.02      0.000125         125         1    __ctype_b_loc
    0.02      0.000122         122         1    bindtextdomain
    0.01      0.000115         115         1    getopt_long
    0.01      0.000111         111         1    textdomain
    ------ ----------- ----------- --------- --------------------
    100.00    0.793099                  3065 total

    注:
    使用-c选项, ltrace输出由进程创建的库调用, 输出结果以调用过程的时间为准进行排序. 
    因为是从urandom设备上读, 这是一种产生随机数的设备, 完成后写入null设备, 所以读过程花费了较多的时间.  
    使用ltrace去捕获运行时函数, 就好像在进程上系上了一个调试工具, 它占据了ltrace大量的时间, 这里ltrace一共消耗了0.79秒.  

    我们再来看一下strace所花费的时间, 如下: 
    strace -c dd if=/dev/urandom of=/dev/null count=1000    
    1000+0 records in   
    1000+0 records out  
    512000 bytes (512 kB, 500 KiB) copied, 0.324057 s, 1.6 MB/s 
    % time     seconds  usecs/call     calls    errors syscall
    ------ ----------- ----------- --------- --------- ----------------
     65.77    0.001775           2      1003           read
     29.71    0.000802           1      1003           write
      4.52    0.000122          61         2           dup2
      0.00    0.000000           0        19        11 open
      0.00    0.000000           0        11           close
      0.00    0.000000           0         1           execve
      0.00    0.000000           0         3         3 access
      0.00    0.000000           0         3           brk
      0.00    0.000000           0         1           munmap
      0.00    0.000000           0         3           mprotect
      0.00    0.000000           0         1           _llseek
      0.00    0.000000           0         3           rt_sigaction
      0.00    0.000000           0        11           mmap2
      0.00    0.000000           0         6           fstat64
      0.00    0.000000           0         1           set_thread_area
    ------ ----------- ----------- --------- --------- ----------------
    100.00    0.002699                  2071        14 total

    注: 
    strace一共消耗了0.002秒, strace把性能提升了很多倍, 这主要是strace在跟踪系统调用的时候不需要动态库, 而ltrace是根据动态库来分析程序运行的.    
    所以ltrace也只能跟踪动态库, 不能跟踪静态库.


# 3. ltrace与strace的相同点
    事实上我们用ltrace和strace都可以发现程序在哪个系统调用时发生了性能瓶径.
    ltrace用-T, 而strace也用-T.
    ltrace与strace都可以指定PID, 即对运行中的程序进行跟踪.
    ltrace -p PID VS strace -p PID

# 4. Example
    shell) gcc main.c
    shell) ltrace ./a.out
    观察可见_libc_start_main才是程序入口, main函数中的printf被编译器优化为puts().
