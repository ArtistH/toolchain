# Intro
    gcc是gnu的c编译器, gcc在执行编译工作的时候, 总共需要4步:
    1. Pre-Processing   预处理, 生成.i的文件.                       [预处理器cpp]
	2. Compiling		将预处理后的文件转换成汇编语言, 生成文件.s. [编译器egcs]
	3. Assembling 		由汇编变为目标代码(机器代码)生成.o文件.	    [汇编器as]
	4. Linking 		    连接目标代码, 生成可执行程序.               [链接器ld]


# 查看gcc编译优化的具体选项开关
    gcc -c -Q -O1 --help=optimizers > /tmp/O1-opts
    gcc -c -Q -O2 --help=optimizers > /tmp/O2-opts
    diff /tmp/O1-opts /tmp/O2-opts | grep enabled


# gcc [options] [filenames] 
## -o FILE
    生成指定的输出文件
	shell) gcc test.c -o test
    shell) gcc -S hello.c -o hello.asm

## -E
    只激活预处理(即只运行预编译器). 不生成文件, 会打印到标准输出.
    如果需要保存, 可以用重定向方法或-o选项:
    shell) gcc -E test.c > test.i
    shell) gcc -E test.c -o test.i

## -S
    只激活预处理和编译. 即指把文件编译成为汇编代码.
    shell) gcc -S test.c // 将生成.s的汇编代码.

## -c 
    只激活预处理, 编译和汇编. 也就是只把程序做成obj文件.
    shell) gcc -c test.c // 他将生成.o的obj文件

## -C 
    在预处理的时候, 不删除注释信息, 一般和-E使用, 有时候分析程序用这个很方便.

## -ansi 
    关闭gnu c中与ansi c不兼容的特性, 激活ansi c的专有特性. 
    (包括禁止一些asm inline typeof关键字, 以及UNIX, vax等预处理宏.) 

## -include file 
    功能就相当于在代码中使用#include.
    shell) gcc hello.c -include /root/pianopan.h 

## -Dmacro 
    相当于C语言中的#define macro 

## -Dmacro=defn 
    相当于C语言中的#define macro=defn 

## -Umacro 
    相当于C语言中的#undef macro 

## -Idir 
    对于#include <file>, gcc会到-I制定的目录查找, 查找不到, 然后将到系统的缺省的头文件目录查找.

## -I- 
    就是取消前一个参数的功能, 所以一般在-Idir之后使用.

## -nostdinc 
    使编译器不在系统缺省的头文件目录里面找头文件, 一般和-I联合使用, 明确限定头文件的位置.

## -M 
    生成文件关联的信息, 包含目标文件所依赖的所有源代码.
    shell) gcc -M hello.c 

## -MD 
    和-M相同, 但是输出将导入到.d的文件里面.

## -MM 
    和-M相同, 但是它将忽略由#include <file>造成的依赖关系.

## -MMD 
    和-MM相同, 但是输出将导入到.d的文件里面.

## -llibrary 
    指定编译的时候使用的库 
    shell) gcc -lncurses hello.c 
    使用ncurses库编译程序 

## -Ldir 
    指定编译的时候搜索库的路径.
    比如你自己的库, 可以用它制定目录, 不然编译器将只在标准库的目录找. 这个dir就是目录的名称.

## 优化级别
    -O0
    -O1
    -O2
    -O3
    编译器的优化选项的4个级别, -O0表示没有优化, -O1为缺省值, -O3优化级别最高.

## -g 
    指示编译器在编译的时候产生调试信息.

## -ggdb 
    此选项将尽可能的生成gdb的可以使用的调试信息. 

## -static 
    此选项将禁止使用动态库, 所以编译出来的东西一般都很大, 也不需要什么动态连接库就可以运行.

## -shared
    此选项将尽量使用动态库, 所以生成文件比较小. 
    shell) gcc -fPIC -shared xxx.c -o xxx.so (注: 动态库中不能有main()函数, 否则连接时会出错.)

## -w 
    不生成任何警告信息.

## -Wall 
    生成所有警告信息.


# 多文件编译
	如果有多个源文件, 基本上有两种编译方法:
	(假设有两个源文件为test.c和testfun.c)

	1. 多个文件一起编译
	用法: shell) gcc testfun.c test.c -o test
	作用: 将testfun.c和test.c分别编译后链接成test可执行文件.

	2. 分别编译各个源文件, 之后对编译后输出的目标文件进行链接.
	用法:
	shell) gcc -c testfun.c 将testfun.c编译成testfun.o
	shell) gcc -c test.c    将test.c编译成test.o
	shell) gcc -o testfun.o test.o -o test  将testfun.o和test.o链接成test 

	以上两种方法相比较, 第一中方法编译时需要所有文件重新编译,
	而第二种方法可以只重新编译修改的文件, 未修改的文件不用重新编译.
