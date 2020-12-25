侦听unix domain socket, 类似tcpdump.

mv /tmp/UNIX.domain /tmp/UNIX.domain.original # 改名后, server对应.original文件.
socat -t100 -x -v UNIX-LISTEN:/tmp/UNIX.domain,mode=777,reuseaddr,fork UNIX-CONNECT:/tmp/UNIX.domain.original

相当于建立了一个双向通道, socat在/tmp/UNIX.domain上监听通信, 并将其转发到/tmp/UNIX.domain.original上.
