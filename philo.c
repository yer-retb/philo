/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-retb <yer-retb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 15:27:35 by yer-retb          #+#    #+#             */
/*   Updated: 2022/08/22 10:33:40 by yer-retb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int i;
	int sg;
	unsigned long rsl;

	i = 0;
	sg = 1;
	rsl = 0;
	if (str[i] == '-')
	{
		sg *= -1;
		i++;
	}
	while (str[i])
	{
		if ((str[i] >= 0 && str[i] < 48) || (str[i] > 57))
			printf("Error\n");
		i++;
	}
	i = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		rsl = rsl * 10 + str[i] - 48;
		i++;
	}
	return (rsl * sg);
}

void	check_error(int ac, char **av, t_philo *src, t_data *data)
{
	
	if (ac < 5 || ac > 6)
	{
		printf("Error : Check your arguments\n");
		return ;
	}
	if (ac == 6)
	{
		data->tour = ft_atoi(av[5]);
		data->sig = 5;
	}
	if (av[1])
		src->phi = ft_atoi(av[1]);
	if (av[2])
		src->die = ft_atoi(av[2]);
	if (av[3])
		src->eat = ft_atoi(av[3]);
	if (av[4])
		src->sleep = ft_atoi(av[4]);
	else
		printf("Error : Check your arguments\n");
}
int sala = 0;
void	*the_table(void *av)
{
	t_philo *src = (t_philo *)av;
	int i;

	i = 0;
	if (i % 2 != 0)
		usleep(1000);
	while (i <= 5)
	{

			pthread_mutex_lock(&src->fork[i]);
			pthread_mutex_lock(&src->fork[i + 1 % (src->phi + 1)]);
			printf("philo %d take fork => %d and fork => %d\n",i, i, ((i + 1) % (src->phi + 1)));
			// printf("ok \n");
			// printf("========>  %d\n", src->philos[i]);
			sleep(1);
			sala++;
			pthread_mutex_unlock(&src->fork[i]);
			pthread_mutex_unlock(&src->fork[i + 1 % src->phi]);
		// else
		// {
		// 	pthread_mutex_lock(&src->fork[i]);
		// 	pthread_mutex_lock(&src->fork[i + 1 % (src->phi + 1)]);
		// 	printf("i => %d next => %d\n", i, ((i + 1) % (src->phi + 1)));
		// 	sleep(1);
		// 	printf("okay\n");
		// 	pthread_mutex_unlock(&src->fork[i]);
		// 	pthread_mutex_unlock(&src->fork[i + 1 % src->phi]);
		// }
		i++;
	}
	return (NULL);
}

void creat_philo(t_philo *src, t_data *data)
{
	int 	i;
	int 	j;
	char	*tab;

	i = -1;
	j = -1;
	src->fork = malloc (sizeof(pthread_mutex_t) * src->phi);
	src->philos = malloc (sizeof(pthread_t) * src->phi);
	tab = malloc (sizeof(int) * (src->phi + 1));
	// give_id(tab, src);
	while (++j < src->phi)
		pthread_mutex_init(src->fork + i, NULL);
	while (++i < src->phi)
		pthread_create(src->philos + i, NULL, the_table, src);
	
	i = -1;
	j = -1;
	while (1)
	{
		usleep(300);
		if (sala == src->phi * src->eat)
		{
			break;
		}
	}
	// while (++i < src->phi)
	// 	pthread_join(src->philos[i], NULL);
	while (++j < src->phi)
		pthread_mutex_destroy(&src->fork[j]);
	
}

int	main(int ac, char **av)
{
	t_philo *src;
	t_data	*data;
	int tour;

	tour = 0;
	src = malloc(sizeof(t_philo) * 5);
	tab[0] = sr
	data = malloc(sizeof(t_data));	
	check_error(ac, av, src, data);
	creat_philo(src, data);
}
