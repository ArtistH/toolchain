# 常用操作
    (gdb) ctrl+x, a 开启gdbtui
    (gdb) ctrl+x, 2 打开汇编指令级窗口

    (gdb) b(break)  设置断点
    (gdb) r(run)

    (gdb) s(step)   单步跟踪进入(执行一行源程序代码, 如果此行代码中有函数调用, 则进入该函数)
    (gdb) n(next)   单步跟踪(执行一行源程序代码, 此行代码中的函数调用也一并执行)
    (gdb) si        命令类似于s命令
    (gdb) ni        命令类似于n命令
                    所不同的是, 这两个命令(si/ni)所针对的是汇编指令, 而s/n针对的是源代码.

    (gdb) bt(backtrace)     栈回溯

    (gdb) i(info) b         查看断点
          i(info) thread    查看线程
    (gdb) d(delete)         后接断点号, 删除断点.

    (gdb) watch 只要watch的变量被修改, 就会自动设置断点停住.

    (gdb) c(continue)


# with LD_PRELOAD
    e.g.
    (gdb) set environment LD_PRELOAD ./lsan-helper.so
    (gdb) file a.out


# 用gdb查看内存
    格式: x /nfu <addr>

    说明:
    x是examine的缩写

    n表示要显示的内存单元的个数

    f表示显示方式, 可取如下值:
        x 按十六进制格式显示变量
        d 按十进制格式显示变量
        u 按十进制格式显示无符号整型
        o 按八进制格式显示变量
        t 按二进制格式显示变量
        a 按十六进制格式显示变量
        i 指令地址格式
        c 按字符格式显示变量
        f 按浮点数格式显示变量

    u表示一个地址单元的长度:
        b表示单字节
        h表示双字节
        w表示四字节
        g表示八字节

    Format letters are o(octal), x(hex), d(decimal), u(unsigned decimal),
    t(binary), f(float), a(address), i(instruction), c(char) and s(string).
    Size letters are b(byte), h(halfword), w(word), g(giant, 8 bytes).

    举例:
    x/3uh buf
    表示从内存地址buf读取内容, h表示以双字节为一个单位, 3表示三个单位, u表示按十六进制显示.


# 修改内存
    命令形式: set * 有类型的指针=value
    使用示例: 对于void *p = malloc(128)这样分配的地址, 可以使用先强制指定类型, 后再写入值, 如:
    set *((char *)p) = 0x61
    set *((char *)p) = 'a'
    set *((char *)(p+110)) = 'b'
    set *(int *)p = 0xff


# attach pid
    shell) sudo gdb attach pid
    执行后进程会停止, 跳到gdb执行.


# gdb call functions 
    gdb带call func能力
    (gdb) call printf("hello world\n")


# core-dump
    training/debug/core-dump
    (1) 可以用下面的语句设置一下, 然后再运行程序便成生成core文件.
    shell) ulimit -c unlimited

    (2) set core pattern:
    shell) sudo sh -c 'echo "core" > /proc/sys/kernel/core_pattern'

    (3) shell) gcc -g exam.c
        shell) gdb ./a.out --core=core

# gdb debug multithreads
    training/thread/thread_life.c
    shell) gcc -g thread_life.c -pthread
    shell) gdb ./a.out
    (gdb) info thread   查看线程数
    (gdb) thread 2      切换到线程2
    (gdb) set set scheduler-locking on  锁住调度器, off放开
    (gdb) c(continue)   另一个线程会停住
