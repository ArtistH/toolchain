# toolchain

## useful cmd
    1) $ apropos timer    列出所有timer相关函数

    2) ulimit
        $ ulimit -a 用来显示当前的各种用户进程限制

        我们在用这个命令的时候主要是为了产生core文件, 就是程序运行发行段错误时的文件:
        $ ulimit -c unlimited

## process scheduling
    1) chrt 修改进程的调度策略和优先级
        # chrt -f -a -p 50 pid
        -f      fifo
        -a      代表所有线程
        -p 50   修改优先级为50(用户空间数字越大,优先级越高. 内核空间相反, 在bitmap上对应是99-50.)
        pid     进程id

    2) renice/nice
        # renice -n -5 -g pid 可以修改线程运行的nice值
        # nice -n 5 ./a.out   直接在进程启动时设置nice值
        
    3) taskset
        # taskset -a -p 01 pid  让pid进程内的所有线程都在cpu0上跑
        # taskset -a -p 02 pid  让pid进程内的所有线程都在cpu1上跑
        # taskset -a -p 03 pid  让pid进程内的所有线程都在cpu0,cpu1上跑

        # taskset -a -cp 0,1 pid    让pid进程内的所有线程在cpu0,cpu1上跑
                                    -c, --cpu-list

## memory mangement
    1) smem
        # smem --pie=command    生成饼状图
        # smem --bar=command    生成柱状图
