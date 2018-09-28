# Intro
    gcc是gnu的c编译器，gcc在执行编译工作的时候，总共需要4步：
    1. Pre-Processing   [预处理器cpp] 预处理，生成.i的文件。	
	2. Compiling		[编译器ccl] 将预处理后的文件转换成汇编语言，生成.s文件。		
	3. Assembling 		[汇编器as] 由汇编变为目标代码(机器代码)生成.o文件。			
	4. Linking 		    [链接器ld] 连接目标代码，生成可执行程序。					

# gcc [options] [filenames] (80%)
<table>
	<tr>
		<th>选项名</th>
		<th>作用</th>
	</tr>
	<tr>
		<td>-o FILE</td>
		<td>
        生成指定的输出文件<br>
	    $ gcc a.c -o a.out<br>
        $ gcc -E a.c -o a.i<br>
		</td>
	</tr>
	<tr>
		<td>-E</td>
		<td>
        只激活预处理(即只运行预编译器). 不生成文件, 会打印到标准输出.<br>
        如果需要保存, 可以用重定向方法或-o选项:<br>
        $ gcc -E a.c > a.i<br>
        $ gcc -E a.c -o a.i<br>
        </td>
	</tr>
    <tr>
		<td>-S</td>
		<td>
        只激活预处理和编译. 即指把文件编译成为汇编代码.<br>
        $ gcc -S a.c // 将生成a.s的汇编代码
        </td>
	</tr>
    <tr>
		<td>-c</td>
		<td>
        只激活预处理, 编译和汇编. 也就是只把程序做成obj文件.<br>
        $ gcc -c a.c // 将生成a.o的obj文件
        </td>
	</tr>
	<tr>
		<td>-g</td>
		<td>指示编译器在编译的时候产生调试信息</td>
	</tr>
	<tr>
		<td>-Wall</td>
		<td>生成所有警告信息</td>
	</tr>
	<tr>
		<td>-Idir</td>
		<td>
        将dir目录加入搜索头文件的目录路径<br>
        可以通过设置以下环境变量来指定搜索路径:<br>
        C_INCLUDE_PATH<br>
        CPP_INCLUDE_PATH<br>
        </td>
	</tr>
	<tr>
		<td>-Ldir</td>
		<td>
        将dir目录加入搜索库的目录路径<br>
        可以通过设置以下环境变量来指定搜索路径:<br>
        LD_LIBRARY_PATH<br>
        </td>
	</tr>
	<tr>
		<td>-llib</td>
		<td>链接lib库</td>
	</tr>
</table>

# 多文件编译
	如果有多个源文件, 基本上有两种编译方法:
	(假设有两个源文件为test.c和testfun.c)

	1. 一次性编译(多个文件一起编译)
	$ gcc testfun.c test.c -o test
	将testfun.c和test.c分别编译后链接成test可执行文件.

	2. 独立编译(分别编译各个源文件, 之后对编译后输出的目标文件进行链接.)
	$ gcc -c testfun.c // 将testfun.c编译成testfun.o
	$ gcc -c test.c    // 将test.c编译成test.o
	$ gcc testfun.o test.o -o test // 将testfun.o和test.o链接成test 

	以上两种方法相比较, 第一中方法编译时需要所有文件重新编译,
	而第二种方法可以只重新编译修改的文件, 未修改的文件不用重新编译.

# 头文件与库文件
## 缺省位置
    头文件:
    /usr/include
    /usr/local/include
    库文件:
    /usr/lib
    /usr/local/lib

# 链接库文件
## -llib
    $ gcc -Wall calc.c -o calc -lm // -lm表示要链接libm.so或者libm.a库文件
## 静态库(.a)
    程序在编译链接的时候把库的代码链接到可执行文件中.
    程序运行的时候将不再需要静态库.
## 动态库(共享库)(.so或.sa)
    程序在运行的时候才去链接动态库的代码, 多个程序共享使用共享库的代码.
    一个与共享库链接的可执行文件仅仅包含它用到的函数入口地址的一个表, 而不是外部函数所在目标文件的整个机器码.
    在可执行文件开始运行以前, 外部函数的机器码由操作系统从磁片上的该共享库中复制到内存中, 这个过程成为动态链接(dynamic linking).
    共享库可以在多个程序间共享, 所以动态链接使得可执行文件更小, 节省了磁盘空间.
## 生成静态库
    $ gcc -c func.c
    $ ar rcs libfunc.a func.o   // ar是gnu归档工具
                                // rcs(replace and create)
                                // 如果.a文件已经存在则替换, 不存在则创建.
                                // s表示保存.o文件的一些索引信息到库文件中.
    $ gcc main.c libfunc.a -o main
    或
    $ gcc -L. main.c -o main -lfunc // 默认情况不会在当前目录下查找库文件, 所以需要添加-L.选项.
    注: 库实际上是一个归档文件, 可以简单认为是.o文件的一个归档.
## 生成动态库
    $ gcc -shared -fPIC func.c -o libfunc.so 
    // shared: 生成共享库格式
    // -fPIC: 产生位置无关码(position independent code)
              表示运行加载与内存地址无关, 可以在任何地址加载运行.
    $ gcc -L. main.c -o main -lfunc
## 运行动态库
    1. 拷贝.so文件到系统共享库路径下(一般指/usr/lib)
    2. 更改LD_LIBRARY_PATH
    3. ldconfig
        配置ld.so.conf, ldconfig更新ld.so.cache.

# 优化级别
    -O0
    -O1
    -O2
    -O3
    编译器的优化选项的4个级别, -O0表示没有优化, -O1为缺省值, -O3优化级别最高.

# 查看gcc编译优化的具体选项开关
    $ gcc -c -Q -O1 --help=optimizers > /tmp/O1-opts
    $ gcc -c -Q -O2 --help=optimizers > /tmp/O2-opts
    $ diff /tmp/O1-opts /tmp/O2-opts | grep enabled

# gcc [options] [filenames] (20%)
## -C 
    在预处理的时候, 不删除注释信息, 一般和-E使用, 有时候分析程序用这个很方便.

## -ansi 
    关闭gnu c中与ansi c不兼容的特性, 激活ansi c的专有特性. 
    (包括禁止一些asm inline typeof关键字, 以及UNIX, vax等预处理宏.) 

## -include file 
    功能就相当于在代码中使用#include.
    $ gcc a.c -include a.h 

## -Dmacro 
    相当于C语言中的#define macro 

## -Dmacro=defn 
    相当于C语言中的#define macro=defn 

## -Umacro 
    相当于C语言中的#undef macro 

## -I- 
    就是取消前一个参数的功能, 所以一般在-Idir之后使用.

## -nostdinc 
    使编译器不在系统缺省的头文件目录里面找头文件, 一般和-I联合使用, 明确限定头文件的位置.

## -M 
    生成文件关联的信息, 包含目标文件所依赖的所有源代码.

## -MD 
    和-M相同, 但是输出将导入到.d的文件里面.

## -MM 
    和-M相同, 但是它将忽略由#include <file>造成的依赖关系.

## -MMD 
    和-MM相同, 但是输出将导入到.d的文件里面.

## -ggdb 
    此选项将尽可能的生成gdb的可以使用的调试信息. 

## -w 
    不生成任何警告信息.
