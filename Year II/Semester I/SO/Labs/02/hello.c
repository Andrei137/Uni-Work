#include <unistd.h>

int main(int argc, char* argv[])
{
    if (write(1, "Hello, World!\n", 14) < 0)
    {
        write(2, "Sorry, could not write to stdout\n", 33);
        return 1;
    }
    return 0;
}