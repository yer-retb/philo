/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-retb <yer-retb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 15:27:35 by yer-retb          #+#    #+#             */
/*   Updated: 2022/08/23 02:51:02 by yer-retb         ###   ########.fr       */
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

void	check_error(int ac, char **av, t_data *data)
{
	
	if (ac < 5 || ac > 6)
	{
		printf("Error : Check your arguments\n");
		return ;
	}
	if (av[5])
		data->tour = ft_atoi(av[5]);
	data->num_ph = ft_atoi(av[1]);
	data->die = ft_atoi(av[2]);
	data->eat = ft_atoi(av[3]);
	data->sleep = ft_atoi(av[4]);
}

void	*the_table(void *av)
{
	t_data *data = (t_data *)av;
	int i;

	i = 0;
	if (i % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&data->fork[i]);
		pthread_mutex_lock(&data->fork[(i + 1) % data->num_ph]);
		printf("philo %d has taken a fork\n", data->philo[i].id);
		i++;
		sleep(1);
		pthread_mutex_unlock(&data->fork[i]);
		pthread_mutex_unlock(&data->fork[(i + 1) % data->num_ph]);
	}
	return (NULL);
}


void creat_philo(t_data *data)
{
	int 	i;
	int 	j;

	i = -1;
	j = -1;
	data->fork = malloc (sizeof(pthread_mutex_t) * data->num_ph);
	data->philo->pt = malloc (sizeof(pthread_t) * data->num_ph);
	while (++j < data->num_ph)
		pthread_mutex_init(data->fork + i, NULL);
	while (++i < data->num_ph)
		pthread_create(&data->philo[i].pt, NULL, &the_table, data);
		
	i = -1;
	j = -1;
	while (++i < data->num_ph)
		pthread_join(data->philo[i].pt, NULL);
	while (++j < data->num_ph)
		pthread_mutex_destroy(&data->fork[j]);
	
}

int	init_philo(t_data *data)
{
	int	i;
	t_philo *philo;

	data->philo = malloc(sizeof(t_philo) * data->num_ph);
	i = 0;
	while (i < data->num_ph)
	{
		data->philo[i].id = i + 1;
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	check_error(ac, av, data);
	init_philo(data);
 	creat_philo(data);
}
