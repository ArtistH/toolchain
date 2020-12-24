#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define ERR_EXIT(m) \
    do { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while (0)


int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stdout, "Usage: %s command1 command2\n", argv[0]);
        return -1;
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) 
		ERR_EXIT("pipe error");

	pid_t pid;
	pid = fork();
	if (pid == -1) 
		ERR_EXIT("fork error");
    if (pid == 0) {
		dup2(pipefd[1], STDOUT_FILENO); /* 将标准输出复制到子进程对管道的写端 */
        close(pipefd[0]);
        close(pipefd[1]); /* 因为标准输出已经指向了管道的写端, 即管道的写端已经成为了子进程的标准输出，所以此时关闭管道写端也没有关系. */
	    execlp(argv[1], argv[1], NULL);	/* execlp替换子进程映像 */
        fprintf(stderr, "error execute %s\n", argv[1]);
        exit(EXIT_FAILURE);
	} else if (pid > 0) {
        dup2(pipefd[0], STDIN_FILENO); /* 管道的读端成为文件句柄0 */
        close(pipefd[0]);
        close(pipefd[1]);
	    execlp(argv[2], argv[2], NULL);	
        fprintf(stderr, "error execute %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    return 0;
}
