#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define n 4
#define m 3
#define p 2

struct position
{
    int i;
    int j;
};

int first_matrix[m][p] = 
{
    {1, 2},
    {3, 4},
    {5, 6}
};

int second_matrix[p][n] = 
{
    {8, 7, 6, 5},
    {4, 3, 2, 1}
};

int result_matrix[m][n];

void* multiply(void* position)
{
    struct position* index = (struct position*) position;
    int i = index->i;
    int j = index->j;
    free(position);
    result_matrix[i][j] = 0;
    for (int k = 0; k < p; ++k)
    {
        result_matrix[i][j] += first_matrix[i][k] * second_matrix[k][j];
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    if (argc != 1)
    {
        perror("Numarul de argumente nu este corect");
        return errno;
    }

    pthread_t thrs[m * n];
    int thread_index = 0;

    // se creaza un thread nou, lansat de functia multiply cu argumentul index, care are i si j curent
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            struct position* index = (struct position*)malloc(sizeof(struct position));
            index->i = i;
            index->j = j;
            if (pthread_create(&thrs[thread_index++], NULL, multiply, index))
            {
                perror("Eroare la crearea thread-ului");
                return errno;
            }
        }
    }

    // asteptarea terminarii thread-urilor
    for (int i = 0; i < thread_index; ++i)
    {
        if (pthread_join(thrs[i], NULL))
        {
            perror("Eroare la asteptarea thread-ului");
            return errno;
        }
    }

    // totul a mers bine, afisam rezultatul
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", result_matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}