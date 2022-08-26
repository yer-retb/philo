/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-retb <yer-retb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 15:27:35 by yer-retb          #+#    #+#             */
/*   Updated: 2022/08/26 22:51:16 by yer-retb         ###   ########.fr       */
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

int	should_die(t_philo *philo)
{

	// printf("time should die %ld \n", get_time() - philo->tem);
	if (philo->temp - get_time() > philo->d->die)
		return 1;
	return 0;
}

void	*the_table(void *av)
{
	t_philo *philo = (t_philo*)av;
	int i = 0;

	while (1)
	{
		pthread_mutex_lock(&philo->d->fork[philo->left_f]);
		pthread_mutex_lock(philo->d->print);
		printf("\033[1;32m%ld ms philo %d has taken a fork\n",get_time() - philo[i].time_start, philo[i].id);
		pthread_mutex_unlock(philo->d->print);
		pthread_mutex_lock(&philo->d->fork[philo->right_f]);
		pthread_mutex_lock(philo->d->print);
		printf("\033[1;32m%ld ms philo %d has taken a fork\n",get_time() - philo[i].time_start, philo[i].id);
		pthread_mutex_unlock(philo->d->print);
		pthread_mutex_lock(philo->d->print);
		printf("\033[1;33m%ld ms philo %d is eating\n",get_time() - philo[i].d->time, philo[i].id);
		philo[i].temp = get_time() - philo[i].d->time;
		pthread_mutex_unlock(philo->d->print);
		ft_usleep(philo[i].d->eat);
		pthread_mutex_lock(philo->d->print);
		printf("\033[1;34m%ld ms philo %d is sleeping\n",get_time() - philo[i].d->time, philo[i].id);
		pthread_mutex_unlock(philo->d->print);
		pthread_mutex_unlock(&philo->d->fork[philo->left_f]);
		pthread_mutex_unlock(&philo->d->fork[philo->right_f]);
		ft_usleep(philo[i].d->sleep);
		pthread_mutex_lock(philo->d->print);
		printf("\033[1;30m%ld ms philo %d is thinking\n",get_time() - philo[i].d->time, philo[i].id);
		pthread_mutex_unlock(philo->d->print);
		// if (should_die(&philo[i]))
		// 	exit(1);
	}
	return (0);
}


void creat_philo(t_data *data)
{
	int 	i;
	int 	j;

	i = -1;
	j = -1;
	data->fork = malloc (sizeof(pthread_mutex_t) * data->num_ph);
	data->print = malloc (sizeof(pthread_mutex_t));
	pthread_mutex_init(data->print, NULL);
	while (++j < data->num_ph)
		pthread_mutex_init(&data->fork[j], NULL);
	data->time = get_time();
	while (++i < data->num_ph)
	{
		pthread_create(&data->philo[i].pt, NULL, &the_table, &data->philo[i]);
		// ft_usleep(200);
		usleep(60);
	}
	j = -1;
	i = 1;
	while (1)
	{
		//printf("\033[1;31mphilo %d die in %ld\n", data->philo->id, (data->time - data->philo[i].tem));
		if ((get_time() - data->time) - (data->philo[i].temp) >= data->die)
		{
			printf("\033[1;31m%ld ms philo %d die\n",((get_time() - data->time) - (data->philo[i].temp)), data->philo[i].id);
			return ;
		}
		i++;
		if (i == data->num_ph)
			i = 1;
	}
	while (++j < data->num_ph)
		pthread_mutex_destroy(&data->fork[j]);
	
}

int	init_philo(t_data *data)
{
	int	i;


	data->philo = malloc(sizeof(t_philo) * data->num_ph);
	if (!data->philo)
		return (0);
	i = 0;
	while (i < data->num_ph)
	{
		data->philo[i].d = data;
		data->philo[i].time_start = get_time();
		data->philo[i].id = i + 1;
		data->philo[i].left_f = i;
		data->philo[i].right_f = (i + 1) % data->num_ph;
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	check_error(ac, av, data);
	init_philo(data);
 	creat_philo(data);
}
