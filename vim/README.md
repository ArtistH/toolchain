PART1: Using
------------

## 1. about exit
    :wq! --- 强制保存退出
    :wq  --- 保存退出
    :x   --- 作用和 :wq 一样
    ZZ   --- 作用和 :wq 一样(注意Z是大写的, 并且不是在命令模式)
    :q   --- 退出
    :q!  --- 强制退出

## 2. about mv
    h: 	 --- 在当前行向左移动一个字符
    j: 	 --- 移动到下一行
    k: 	 --- 移动到上一行
    l: 	 --- 在当前行向右移动一个字符
    Ctrl +f: --- 向前滚动一页
    Ctrl +b: --- 向后滚动一页
    :n 	 --- 将光标定位到第n行
    :$ 	 --- 将光标定位到最后一行
    0 	 --- 将光标定位到本行的行首
    $ 	 --- 将光标定位到本行的行尾
    G	 --- 将光标定位到本文章的最后一行(与 :$ 功能相同)
    H	 --- 将光标定位到屏幕的顶端
    M    	 --- 将光标定位到屏幕的中间
    L    	 --- 将光标定位到屏幕的底端

## 3. about search
    / --- 后面跟要查找的东西, 在文件中向前搜索
    ? --- 后面跟要查找的东西, 在文件中向后搜索
    n --- 向前重复搜索
    N --- 向后重复搜索

## 4. about cp
    yy  		--- 复制光标当前行
    nyy 		--- 复制光标当前行到当前行以下的n-1行
    :1,100 co 200   --- 将1~100的内容复制到第200行
    :100,102 co $   --- 将100~102行的内容复制到最后一行

## 5. about paste
    p --- 粘贴到当前行的下一行
    P --- 粘贴到当前行的上一行

## 6. about delete & cut
    dd  		--- 删除当前行
    ndd 		--- 删除光标当前行到当前行以下的n-1行
    dw  		--- 删除一个单词
    ndw 		--- 删除n个单词
    x   		--- 删除一个字符
    nx  		--- 删除n个字符
    dG  		--- 删除当前光标到文件末尾的所有内容
    d0  		--- 删除当前光标到本行行首的所有内容
    d$  		--- 删除当前光标到本行行尾的所有内容
    :1,100d 	--- 删除1~100行
    :100d   	--- 删除第100行
    :1,100 mo $ 	--- 将1~100行的内容移动到最后一行
    :g/^$/d		--- 删除文件中空行

## 7. about insert
    i --- 在当前位置的字符前面进入插入模式
    I --- 在当前行的开头进行插入
    a --- 在当前位置的字符后面进入插入模式
    A --- 在当前行的结尾进行插入
    o --- 在当前行下面打开一个新行进行插入
    O --- 在当前行上面打开一个新行进行插入

## 8. about undo
    u --- 撤销上一次的更改

## 9. about replace
    (regexp是要匹配的式样, replacement是要替换的字符串)
    :s/regexp/replacement  	 --- 替换当前行出现的第一个式样
    :s/regexp/replacement/g	 --- 替换当前行所有的匹配
    :%s/regexp/replacement/g --- 替换文件中所有匹配式样

## 10. about commit
    多行注释:
	1) 首先按esc进入命令行模式下, 按下Ctrl+v, 进入列(也叫区块)模式;
	2) 在行首使用上下键选择需要注释的多行;
	3) 按下键盘"I"键, 进入插入模式;
	4) 然后输入注释符("//", "#"等);
	5) 最后按下"Esc"键.
	注: 在按下esc键后, 会稍等一会才会出现注释.
 
    删除多行注释:
	1) 首先按esc进入命令行模式下, 按下Ctrl+v, 进入列模式;
	2) 选定要取消注释的多行;
	3) 按下"x"或者"d".
	注: 如果是"//"注释, 那需要执行两次该操作, 如果是"#"注释, 一次即可.



PART2: Plugin
-------------

## 1. grep
    1) cp grep/grep.vim ~/.vim/plugin/
    2) add the follow line to ~/.vimrc
	________________________________
	nnoremap <silent> <F3> :Grep<CR> 
	________________________________

    F3 --- 开启grep

## 2. ctags
    0) INSTALL ctags
    1) cd src 					--- 进入源码目录
    2) ctags -R --fields=+ls	--- 生成tags文件, --fields=+ls用于echofunc
    3) :set tags=src/tags		--- 设置tags
    4) ctrl-]					--- 跳转到函数定义处
    5) ctrl-t					--- 跳回

## 3. Manage with Vundle(See .vimrc)
    0) 下载安装vundle
    git clone https://github.com/gmarik/vundle.git ~/.vim/bundle/vundle
    然后进入vim执行	:BundleInstall

    1) taglist(需要先安装ctags)
    let Tlist_Show_One_File = 1     "不同时显示多个文件的tag, 只显示当前文件的
    let Tlist_Exit_OnlyWindow = 1   "如果taglist窗口是最后一个窗口, 则退出vim
    let Tlist_Use_Right_Window = 1  "在右侧窗口中显示taglist窗口 
    nmap tl :Tlist<cr>              "设置快捷键 

    :Tlist  --- 开启taglist(快捷键 tl)
    o       --- 在一个新打开的窗口中显示光标下tag
    <Space> --- 显示光标下tag的原型定义
    u       --- 更新taglist窗口中的tag
    s		--- 更改排序方式, 在按名字排序和按出现顺序排序间切换
    x		--- taglist窗口放大和缩小, 方便查看较长的tag
    +		--- 打开一个折叠
    -		--- 将tag折叠起来
    *		--- 打开所有的折叠
    =		--- 将所有tag折叠起来
    q		--- 关闭taglist窗口

## 4. cscope(待用)
    0) INSTALL cscope
    1) cp cscope/cscope_maps.vim ~/.vim/plugin/
    2) add the follow line to ~/.vimrc to use the quickfix to show the cscope result
	    _____________________________________
	    set cscopequickfix=s-,c-,d-,i-,t-,e- 
	    _____________________________________
    3) cd src
    4) cscope -Rbkq
        -R : 在生成索引文件时, 搜索子目录树中的代码
        -b : 只生成索引文件, 不进入cscope的界面
        -k : 在生成索引文件时, 不搜索/usr/include目录
        -q : 生成cscope.in.out和cscope.po.out文件, 加快cscope的索引速度
    5) :cs add src/cscope.out src --- 将生成的cscope文件导入到vim(因在cscope_maps.vim中有设置, 可以不执行)
    6) cscope find用法:
    :cs find s|g|d|c|t|e|f|i name 
	_________________________________________________
	说明									|快捷键
	-------------------------------------------------
	0 或 s |查找符号                        |ctrl-\ s	
	-------------------------------------------------
	1 或 g |查找全局的定义                  |ctrl-\ g
	-------------------------------------------------
	2 或 d |查看指定函数调用了哪些函数      |ctrl-\ d
	-------------------------------------------------
	3 或 c |查看指定函数被哪些函数所调用	|ctrl-\ c
	-------------------------------------------------
	4 或 t |查找字符串 						|ctrl-\ t
	-------------------------------------------------
	6 或 e |查找正则表达式 					|ctrl-\ e
	-------------------------------------------------
	7 或 f |查找文件 						|ctrl-\ f
	-------------------------------------------------
	8 或 i |查看指定的文件被哪些文件include	|ctrl-\ i 
	_________________________________________________
