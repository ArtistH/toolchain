PART1: Using
------------

## 1. about save && exit
    :wq!    --- 强制保存退出
    :wq     --- 保存退出(:x 与此功能相同)
    :q      --- 退出
    :q!     --- 强制退出

## 2. about move
    h   --- 在当前行向左移动一个字符
    j 	--- 移动到下一行
    k 	--- 移动到上一行
    l 	--- 在当前行向右移动一个字符

    w   --- 移至下一个单词的词首
    b   --- 跳至当前或前一个单词的词首
    e   --- 跳至当前或下一个单词的词尾

    :n  --- 将光标定位到第n行
    0   --- 将光标定位到本行的行首
    $   --- 将光标定位到本行的行尾
    gg  --- 将光标定位到文件第一行
    G   --- 将光标定位到文件最后一行

    H	--- 将光标定位到屏幕的顶端
    M   --- 将光标定位到屏幕的中间
    L   --- 将光标定位到屏幕的底端

    Ctrl+f  --- 向下翻一屏
    Ctrl+b  --- 向上翻一屏
    Ctrl+d  --- 向下翻半屏
    Ctrl+u  --- 向上翻半屏

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
    dd  --- 删除当前行
    ndd --- 删除光标当前行到当前行以下的n-1行

    dw  --- 删除一个单词
    ndw --- 删除n个单词

    x   --- 删除一个字符
    nx  --- 删除n个字符

    dG  --- 删除当前光标到文件末尾的所有内容

    d0  --- 删除当前光标到本行行首的所有内容
    d$  --- 删除当前光标到本行行尾的所有内容

    :1,100d 	    --- 删除1~100行
    :100d   	    --- 删除第100行

    :1,100 mo $ 	--- 将1~100行的内容移动到最后一行

    :g/^$/d		    --- 删除文件中空行

## 7. about insert
    i --- 在当前位置的字符前面进入插入模式
    I --- 在当前行的开头进行插入
    a --- 在当前位置的字符后面进入插入模式
    A --- 在当前行的结尾进行插入
    o --- 在当前行下面打开一个新行进行插入
    O --- 在当前行上面打开一个新行进行插入

## 8. about undo
    u       --- 撤销上一次的更改
    Ctrl+r  --- 撤消最近一次撤消操作

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
	注: 在按下esc键后, 需稍等一会才会出现注释.
 
    删除多行注释:
	1) 首先按esc进入命令行模式下, 按下Ctrl+v, 进入列模式;
	2) 选定要取消注释的多行;
	3) 按下"x"或者"d".
	注: 如果是"//"注释, 那需要执行两次该操作, 如果是"#"注释, 一次即可.

## 11. about split screen
    Ctrl+w, s   --- 水平分割窗口(:split)
    Ctrl+w, v   --- 垂直分割窗口(:vsplit)
    :qa         --- 关闭所有窗口



PART2: Plugin
-------------

## 1. ctags
    0) INSTALL ctags
    1) cd src; ctags -R --fields=+ls    生成tags文件, --fields=+ls用于echofunc(采用cscope的索引, 所以一般不执行)
    2) :set tags=src/tags               设置tags(vundle安装了taglist.vim, 可以不执行)
    4) ctrl-]   跳转到函数定义处
    5) ctrl-t   跳回

## 2. cscope
    0) INSTALL cscope
    1) cd src; cscope-indexer -r
    2) :cs add src/cscope.out src   将生成的cscope文件导入到vim(因在vimrc中有设置, 可以不执行)
    4) cscope find用法:
    :cs f(ind) s|g|d|c|t|e|f|i name 
<table>
	<tr>
		<th>command</th>
		<th>说明</th>
		<th>快捷键</th>
	</tr>
	<tr>
		<th>0 或 s</th>
		<th>查找符号</th>
		<th>ctrl-\ s</th>
	</tr>
	<tr>
		<th>1 或 g</th>
		<th>查找全局的定义</th>
		<th>ctrl-\ g</th>
	</tr>
	<tr>
		<th>2 或 d</th>
		<th>查看指定函数调用了哪些函数</th>
		<th>ctrl-\ d</th>
	</tr>
	<tr>
		<th>3 或 c</th>
		<th>查看指定函数被哪些函数所调用</th>
		<th>ctrl-\ c</th>
	</tr>
	<tr>
		<th>4 或 t</th>
		<th>查找字符串</th>
		<th>ctrl-\ t</th>
	</tr>
	<tr>
		<th>6 或 e</th>
		<th>查找正则表达式</th>
		<th>ctrl-\ e</th>
	</tr>
	<tr>
		<th>7 或 f</th>
		<th>查找文件</th>
		<th>ctrl-\ f</th>
	</tr>
	<tr>
		<th>8 或 i</th>
		<th>查看指定的文件被哪些文件include</th>
		<th>ctrl-\ i</th>
	</tr>
</table>

    5) ctrl+o  回到上次位置
    6) ctrl+i  前进

## 3. Manage with Vundle(See .vimrc)
    git clone https://github.com/gmarik/vundle.git ~/.vim/bundle/vundle
    然后进入vim执行	:BundleInstall
