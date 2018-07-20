## chrt 修改进程的调度策略和优先级
        shell> chrt -f -a -p 50 pid
        -f      fifo
        -a      代表所有线程
        -p 50   修改优先级为50(用户空间数字越大,优先级越高. 内核空间相反, 在bitmap上对应是99-50.)
        pid     进程pid

## renice/nice
        shell> renice -n -5 -g pid 可以修改线程运行的nice值
        shell> nice -n 5 ./a.out   直接在进程启动时设置nice值
        
## taskset
        shell> taskset -a -p 01 pid	让pid进程内的所有线程都在cpu0上跑
        shell> taskset -a -p 02 pid	让pid进程内的所有线程都在cpu1上跑
        shell> taskset -a -p 03 pid	让pid进程内的所有线程都在cpu0,cpu1上跑

        shell> taskset -a -cp 0,1 pid 让pid进程内的所有线程在cpu0,cpu1上跑 (-c, --cpu-list)
