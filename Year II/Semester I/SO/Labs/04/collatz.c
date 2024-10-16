#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

void collatz(int a_n)
{
    printf("%d ", a_n);
    do
    {
        if (a_n % 2 == 0)
        {
            a_n /= 2;
        }
        else
        {
            a_n = a_n * 3 + 1;
        }
        printf("%d ", a_n);
    } while (a_n != 1);
    printf(".\n");
}

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
        collatz(atoi(argv[1]));
    }
    else
    {
        wait(NULL);
        printf("Child %d finished\n", pid);
    }
}