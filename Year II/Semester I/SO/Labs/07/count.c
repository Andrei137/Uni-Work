#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>

#define MAX_RESOURCES 5
#define NR_THREADS 7

int available_resources = MAX_RESOURCES;
pthread_mutex_t mtx;

int decrease_count(int count)
{
    pthread_mutex_lock(&mtx);
    if (available_resources < count)
    {
        printf("!!!     Nu sunt destule resurse    !!!\n");
        printf("Tried %d resources but only %d remaining\n", count, available_resources);
        pthread_mutex_unlock(&mtx);
        return -1;
    }
    else
    {
        available_resources -= count;
        printf("Got      %d resources %d remaining\n", count, available_resources);
    }
    pthread_mutex_unlock(&mtx);
    return 0;
}

int increase_count(int count)
{
    pthread_mutex_lock(&mtx);
    available_resources += count;
    printf("Released %d resources %d remaining\n", count, available_resources);
    pthread_mutex_unlock(&mtx);
    return 0;
}

void* thread_resources(void* arg)
{
    int* count = (int*)arg;
    if (decrease_count(*count) == 0)
    {
        // sleep(1 + rand() % 3);
        increase_count(*count);
    }
    return NULL;
}

int main()
{
    srand(time(0));

    printf("MAX_RESOURCES=%d\n", MAX_RESOURCES);

    // se initializeaza mutex-ul
    if (pthread_mutex_init(&mtx, NULL)) 
    {
        perror(NULL);
        return errno;
    }

    pthread_t thrs[NR_THREADS];

    for (int i = 0; i < NR_THREADS; ++i)
    {
        int* count = (int*)malloc(sizeof(int));
        *count = 1 + rand() % MAX_RESOURCES;
        if (pthread_create(&thrs[i], NULL, thread_resources, count))
        {
            perror("Eroare la crearea thread-ului");
            return errno;
        }
    }

    // asteptarea terminarii thread-urilor
    for (int i = 0; i < NR_THREADS; ++i)
    {
        if (pthread_join(thrs[i], NULL))
        {
            perror("Eroare la asteptarea thread-ului");
            return errno;
        }
    }

    // totul a mers bine, distrugem mutex-ul
    pthread_mutex_destroy (&mtx);

    return 0;
}