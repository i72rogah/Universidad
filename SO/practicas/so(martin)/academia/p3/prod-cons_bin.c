#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N 5
#define MAX_ITEMS 20
void *fprod();
void *fcons();
int cont=0;
int buffer[N];

pthread_mutex_t mutex= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t lleno= PTHREAD_COND_INITIALIZER;
pthread_cond_t vacio= PTHREAD_COND_INITIALIZER;

main()
{
	srand(time(NULL));
	pthread_t prod, cons;

	pthread_create(&prod, NULL, (void *) fprod, NULL);
	pthread_create(&cons, NULL, (void *) fcons, NULL);

	pthread_join(prod, NULL);
	pthread_join(cons, NULL);

}

void *fprod()
{
	
	usleep(rand()%100000);
	int num_items=0, pos_buffer=0;
	while(num_items <=MAX_ITEMS)
	{
		pthread_mutex_lock(&mutex);
		if(cont==N)
			pthread_cond_wait(&lleno, &mutex);
		buffer[pos_buffer]=rand()%20;
		printf("P: Colocando en la pos %d el productor %d\n", pos_buffer, buffer[pos_buffer]);
		sleep(1);
		pos_buffer=(pos_buffer+1)%N;
		cont++;
		num_items++;
		pthread_cond_signal(&vacio);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}

void *fcons()
{
	usleep(rand()%100000);
	int item, num_items=0, pos_buffer=0;
	while(num_items<=MAX_ITEMS)
	{
		pthread_mutex_lock(&mutex);
		if(cont==0)
			pthread_cond_wait(&vacio, &mutex);
		item=buffer[pos_buffer];
		printf("C: Leo de %d el valor %d\n", pos_buffer, item);
		sleep(1);
		pos_buffer=(pos_buffer+1)%N;
		cont--;
		num_items++;
		pthread_cond_signal(&lleno);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}