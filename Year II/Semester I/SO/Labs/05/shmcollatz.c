#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    printf("Starting parent %d\n", getpid());
    char shm_name[] = "myshm";
    int shm_fd = shm_open(shm_name, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
    if (shm_fd < 0)
    {
        perror(NULL);
        return errno;
    }
    size_t shm_size = getpagesize();
    if (ftruncate(shm_fd, shm_size * (argc - 1)) == -1)
    {
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }
    pid_t pid;
    int offset = 0;
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
            void* shm_ptr = mmap(0, shm_size, PROT_WRITE, MAP_SHARED, shm_fd, offset);
            if (shm_ptr == MAP_FAILED)
            {
                perror(NULL);
                shm_unlink(shm_name);
                return errno;
            }
            int* shm_int = (int*) shm_ptr;
            int value = atoi(argv[i]);
            while (value != 1)
            {
                *shm_int = value;
                if (value % 2 == 0)
                {
                    value /= 2;
                }
                else
                {
                    value = 3 * value + 1;
                }
                ++shm_int;
                if (shm_int == shm_ptr + shm_size)
                {
                    printf("Error, too many values");
                    munmap(shm_ptr, shm_size);
                    shm_unlink(shm_name);
                    return errno;
                }
            }
            *shm_int = value;
            munmap(shm_ptr, shm_size);
            printf("Done Parent %d Me %d\n", getppid(), getpid());
            return 0;
        }
        offset += shm_size;
    }
    while (wait(NULL) > 0);
    void* shm_ptr = mmap(0, shm_size * (argc - 1), PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED)
    {
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }
    int* shm_int = (int*) shm_ptr;
    for (int j = 0; j < argc - 1; ++j)
    {
        printf("%d: ", *shm_int);
        while (*shm_int != 1)
        {
            printf("%d ", *shm_int);
            ++shm_int;
        }
        printf("%d\n", *shm_int);
        shm_int = shm_ptr + (j + 1) * shm_size;
    }
    munmap(shm_ptr, shm_size * (argc - 1));
    shm_unlink(shm_name);
    return 0;
}