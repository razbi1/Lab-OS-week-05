#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int             g_buff;
pthread_mutex_t g_lock;
pthread_cond_t  g_cond_p;
pthread_cond_t  g_cond_c;

void    *prod(void *argc)
{
    int     i;

    i = 0;
	while (1){
  		pthread_mutex_lock(&g_lock);
  		while(g_buff != 0)
  			pthread_cond_wait(&g_cond_p, &g_lock);
  		g_buff = i;
  		pthread_cond_signal(&g_cond_c);
  		pthread_mutex_unlock(&g_lock);
  		i++;
 	}
 	pthread_exit(0);
}

void    *cons(void *argc)
{
	while(1)
    {
  		pthread_mutex_lock(&g_lock);
  		while(g_buff == 0)
  			pthread_cond_wait(&g_cond_c,&g_lock);
        printf("%d\n", g_buff);
  		g_buff = 0;
  		pthread_cond_signal(&g_cond_p);
  		pthread_mutex_unlock(&g_lock);
 	}
 	pthread_exit(0);
}

int     main()
{
    pthread_t pro_con[2];

    g_buff = 0;
    pthread_mutex_init(&g_lock, NULL);
    pthread_cond_init(&g_cond_p, NULL);
    pthread_cond_init(&g_cond_c, NULL);
    pthread_create(&pro_con[0], NULL, prod, NULL);
    pthread_create(&pro_con[1], NULL, cons, NULL);
    pthread_join(pro_con[0], NULL);
    pthread_join(pro_con[1], NULL);
    pthread_cond_destroy(&g_cond_p);
    pthread_cond_destroy(&g_cond_c);
    pthread_mutex_destroy(&g_lock);
    return (0);
}
