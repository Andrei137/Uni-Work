#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("Error at fork!");
        return errno;
    }
    else if (pid == 0)
    {
        char* argv[] = {"ls", NULL};
        execve("/bin/ls", argv, NULL);
        perror(NULL);
    }
    else
    {
        printf("My PID=%d, Child PID=%d\n", getpid(), pid);
        wait(NULL);
        printf("Child %d finished\n", getpid());
    }
    return 0;
}