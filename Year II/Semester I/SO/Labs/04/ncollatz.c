#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    pid_t pid;
    for (int i = 1; i < argc; ++i)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("Error at fork!");
            return errno;
        }
        else if (pid == 0)
        {
            printf("Starting Parent %d Me %d\n", getppid(), getpid());
            char* argv1[] = {"collatz", argv[i], NULL};
            execve("/home/blackspell13/collatz", argv1, NULL);
            perror(NULL);
        }
    }
    while (wait(NULL) > 0);
    return 0;
}