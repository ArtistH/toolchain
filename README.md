# toolchain

## useful cmd
    1) apropos timer   # 列出所有timer相关函数

    2) ulimit
        ulimit -a 用来显示当前的各种用户进程限制

        我们在用这个命令的时候主要是为了产生core文件, 就是程序运行发行段错误时的文件:
        ulimit -c unlimited

    3) chrt 修改进程的调度策略和优先级
        chrt -f -a -p 50 pid
        -f      fifo
        -a      代表所有线程
        -p 50   修改优先级为50(用户空间数字越大,优先级越高. 内核空间相反, 在bitmap上对应是99-50.)
        pid     进程id

    4) renice/nice
        renice -n -5 -g pid 可以修改线程运行的nice值
        nice -n 5 ./a.out   直接在进程启动时设置nice值
        
    5) taskset
