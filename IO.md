## ftrace

## blktrace
	shell> Install blktrace
	shell> blktrace -d /dev/sdaX -o - | blkparse -i - > X.trace
	shell> dd 

	启动dd, 使用blktrace抓取dd过程.

## blkcat
	shell> Install sleuthkit
	shell> blkcat /dev/sdaX blockNO.
