#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int i = 0;

typedef struct n_data{
	char buffer[5];
	pthread_mutex_t m[1];
} t_data;

void	*fun(void *args)
{
	t_data *data = (t_data *)args;
	pthread_mutex_lock(&data->m[1]);
	printf("%d\n", i++);
	pthread_mutex_unlock(&data->m[1]);
	return (NULL);
}

int main()
{
	pthread_t	t[3];
	t_data data;
	bzero(data.buffer, 5);
	for(int i = 0; i < 3; i++)
		pthread_mutex_init(data.m + i, NULL);
	for(int i = 0; i < 3; i++)
		pthread_create(t + i, NULL, fun, &data);
	for(int i = 0; i < 3; i++)
		pthread_join(t[i], NULL);
	for(int i = 0; i < 3; i++)
		pthread_mutex_destroy(data.m + 1);
}