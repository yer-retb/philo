#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int j = 0;
pthread_mutex_t mutex;

void *test(void *s)
{
	(void)s;
	int i = -1;
	while (++i < 1000000)
	{
		pthread_mutex_lock(&mutex);
		printf("hello word\n");
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int main(int ac, char **av)
{
	(void)ac;
	pthread_t tab[atoi(av[1])];
	int i;

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < atoi(av[1]))
	{
		pthread_create(tab + i, NULL, &test, NULL);
		i++;
		printf("Thread %d has started\n", i);
	}
	i = 0;
	while (i < atoi(av[1]))
	{
		pthread_join(tab[i], NULL);
		i++;
		printf("Thread %d has finished execution\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("%d\n", j);

}