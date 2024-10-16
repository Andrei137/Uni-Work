#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* strrev(void* arg)
{
    char* s = (char*) arg;
    int len = strlen(s);
    char* aux = (char*)malloc(len);
    for (int i = len - 1; i >= 0; --i)
    {
        aux[strlen(s) - 1 - i] = s[i];
    }
    return aux;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        perror("Numarul de argumente nu este corect");
        return errno;
    }

    void* result;
    pthread_t thr;

    // se creaza un thread nou, lansat de functia strrev cu argumentul argv[1]
    if (pthread_create(&thr, NULL, strrev, argv[1]))
    {
        perror("Eroare la crearea thread-ului");
        return errno;
    }

    // se asteapta terminarea thread-ului
    if (pthread_join(thr, &result))
    {
        perror("Eroare la asteptarea thread-ului");
        return errno;
    }

    // totul a mers bine, afisam rezultatul
    printf("%s\n", (char*)result);
    free(result);

    return 0;
}
