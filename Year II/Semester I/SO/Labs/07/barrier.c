#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHRS 5

sem_t sem;
pthread_mutex_t mtx;
int count = 0;

void barrier_point()
{
    pthread_mutex_lock(&mtx);
    ++count;
    if (count == NTHRS)
    {
        pthread_mutex_unlock(&mtx);
        if (sem_post(&sem))
        {
            perror("Error!! Something went wrong");
            return;
        }
        return;
    }
    pthread_mutex_unlock(&mtx);
    if (sem_wait(&sem))
    {
        perror("Error!! Something went wrong");
        return;
    }
    if (sem_post(&sem))
    {
        perror("Error!! Something went wrong");
        return;
    }
}

void* tfun(void* arg)
{
    int* tid = (int*)arg;
    printf("%d reached the barrier \n",*tid);
    barrier_point();
    printf("%d passed the barrier \n", *tid);
    free(tid);
    return NULL;
}

int main()
{
    printf("NTHRS=%d\n", NTHRS);

    pthread_t thrs[NTHRS];

    // se initializeaza semaforul
    if(sem_init(&sem, 0, 0))
    {
        perror("Eroare la initializarea semaforului\n");
        return errno;
    }

    // se initializeaza mutex-ul
    if(pthread_mutex_init(&mtx, NULL))
    {
          perror("Eroare la crearea mutex-ului\n");
          return errno ;
    }

    for(int i = 0; i < NTHRS; ++i)
    {
        int* k = (int*)malloc(sizeof(int));
        *k = i;
        if(pthread_create(&thrs[i], NULL, tfun, k))
        {
            perror(NULL); 
            return errno;
        }
    }

    // asteptarea terminarii thread-urilor
    for(int i = 0; i < NTHRS; ++i)
    {
        if(pthread_join(thrs[i], NULL))
        {
            perror("Eroare la asteptarea thread-ului");
            return errno;
        }
    }

    // se distruge semaforul
    if(sem_destroy(&sem))
    {
        perror("Eroare la distrugerea semaforului \n");
        return errno;
    }

    // se distruge mutex-ul
    if (pthread_mutex_destroy(&mtx))
    {
        perror("Eroare la distrugerea mutexului \n");
        return errno;
    }

    return 0;
}
