#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#define THREADS 5

void    *routine(void *td)
{
    printf("Thread %d, created by thread %d\n", (int) pthread_self(), (int) (pthread_t) td);
    pthread_exit(NULL);
}

int     main()
{
    pthread_t   ths[THREADS];
    pthread_t   td;
    int         i;

    td = pthread_self();
    for (i = 0;i < THREADS; i++)
    {
        printf("Thread %d, creating %d thread\n", (int) td, i+1);
        pthread_create(&ths[i], NULL, routine, (void*) td);
        pthread_join(ths[i], NULL);
    }
    pthread_exit(NULL);
    return (0);
}
