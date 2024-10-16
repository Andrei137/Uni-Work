#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/* TODO List
- Good error checking
- Vector buffer
- Bonus: Overwrite folder yes/no option
*/

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        write(2, "Usage: ./mycp <source> <destination>\n", 38);
        return 1;
    }

    const char* src_name = argv[1];
    const char* dst_name = argv[2];

    int src_fd;
    if ((src_fd = open(src_name, O_RDONLY), src_fd) < 0)
    {
        char* message = "Sorry, could not open source file\n";
        write(2, message, strlen(message));
        return errno;
    }

    struct stat sb;
    char response;
    if (stat(dst_name, &sb) == 0)
    {
        char* message = "The file already exists, overwrite? (y/n) -> ";
        write(1, message, strlen(message));
        if (read(0, &response, 1) < 0)
        {
            message = "Sorry, something went wrong\n";
            write(2, message, strlen(message));
            close(src_fd);
            return errno;
        }
        else if (response != 'y')
        {
            message = "Stopped by user\n";
            write(1, message, strlen(message));
            close(src_fd);
            return 0;
        }
    }

    int dst_fd;
    if (dst_fd = open(dst_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR), dst_fd < 0)
    {
        char* message = "Sorry, something went wrong\n";
        write(2, message, strlen(message));
        close(src_fd);
        return errno;
    }

    ssize_t r_bytes;
    char buffer[4096];
    while ((r_bytes = read(src_fd, buffer, sizeof(buffer))) > 0)
    {
        ssize_t w_bytes = write(dst_fd, buffer, r_bytes);
        if (w_bytes != r_bytes)
        {
            char* message = "Sorry, something went wrong\n";
            write(2, message, strlen(message));
            close(src_fd);
            close(dst_fd);
            return errno;
        }
    }

    close(src_fd);
    close(dst_fd);
    char* message = "The copy was successful\n";
    write(1, message, strlen(message));

    return 0;
}