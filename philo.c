/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-retb <yer-retb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 15:27:35 by yer-retb          #+#    #+#             */
/*   Updated: 2022/09/01 04:06:36 by yer-retb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int i;
	unsigned long rsl;

	i = 0;
	rsl = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		rsl = rsl * 10 + str[i] - 48;
		i++;
	}
	return (rsl);
}

int	check_error(int ac, char **av, t_data *data)
{
	int	i;
	int	j;
	
	i = 1;
	if (ac < 5 || ac > 6)
	{
		printf("Error : Check your arguments\n");
		return 0;
	}
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if ((av[i][j] >= 0 && av[i][j] < 48) || (av[i][j] > 57) || (av[i][0] == '0'))
			{
				printf("Error : Check your arguments\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	if (av[5])
		data->tour = ft_atoi(av[5]);
	data->num_ph = ft_atoi(av[1]);
	data->die = ft_atoi(av[2]);
	data->eat = ft_atoi(av[3]);
	data->sleep = ft_atoi(av[4]);
	return 1;
}



void	*the_table(void *av)
{
	t_philo *philo = (t_philo*)av;

	if (philo->id % 2 == 0)
		usleep(60);
	while (1)
	{
		pthread_mutex_lock(&philo->d->fork[philo->left_f]);
		pthread_mutex_lock(philo->d->print);
		printf("\033[1;32m%ld ms philo %d has taken a fork\n",get_time() - philo->d->time, philo->id);
		pthread_mutex_unlock(philo->d->print);
		pthread_mutex_lock(&philo->d->fork[philo->right_f]);
		pthread_mutex_lock(philo->d->print);
		printf("\033[1;32m%ld ms philo %d has taken a fork\n",get_time() - philo->d->time, philo->id);
		pthread_mutex_unlock(philo->d->print);
		pthread_mutex_lock(philo->d->print);
		printf("\033[1;33m%ld ms philo %d is eating\n",get_time() - philo->d->time, philo->id);
		philo->temp = get_time() - philo->d->time;
		pthread_mutex_lock(philo->d->test);
		philo->d->sig += 1;
		pthread_mutex_unlock(philo->d->test);
		pthread_mutex_unlock(philo->d->print);
		ft_usleep(philo->d->eat);
		pthread_mutex_lock(philo->d->print);
		printf("\033[1;34m%ld ms philo %d is sleeping\n",get_time() - philo->d->time, philo->id);
		pthread_mutex_unlock(philo->d->print);
		pthread_mutex_unlock(&philo->d->fork[philo->left_f]);
		pthread_mutex_unlock(&philo->d->fork[philo->right_f]);
		ft_usleep(philo->d->sleep);
		pthread_mutex_lock(philo->d->print);
		printf("\033[1;30m%ld ms philo %d is thinking\n",get_time() - philo->d->time, philo->id);
		pthread_mutex_unlock(philo->d->print);
	}
	return (0);
}

int	deff(t_philo data)
{
	if ((get_time() - data.d->time) - (data.temp) >= data.d->die)
		return 0;
	return 1;
}

int timing(t_data *data)
{
	pthread_mutex_lock(data->test);
	if ((data->sig / data->tour ) == data->num_ph)
		return (0);
	pthread_mutex_unlock(data->test);
	return (1);
}

void creat_philo(t_data *data)
{
	int 	i;
	int 	j;

	i = 0;
	j = -1;
	data->philo = malloc(sizeof(t_philo) * data->num_ph);
	data->fork = malloc (sizeof(pthread_mutex_t) * data->num_ph);
	data->print = malloc (sizeof(pthread_mutex_t));
	data->test = malloc (sizeof(pthread_mutex_t));
	if (!data->philo || !data->fork || !data->print || !data->test)
		return ;
	pthread_mutex_init(data->print, NULL);
	while (++j < data->num_ph)
		pthread_mutex_init(&data->fork[j], NULL);
	data->time = get_time();
	while (i < data->num_ph)
	{
		data->philo[i].d = data;
		data->philo[i].time_start = get_time();
		data->philo[i].id = i + 1;
		data->philo[i].left_f = i;
		data->philo[i].right_f = (i + 1) % data->num_ph;
		pthread_create(&data->philo[i].pt, NULL, &the_table, &data->philo[i]);
		i++;
		usleep(60);
	}
	j = -1;
	i = 0;
	while (1)
	{
		
		if (!(timing(data)))
			return ;
		if (!deff(data->philo[i]))
		{
			pthread_mutex_lock(data->print);
			printf("\033[1;31m%ld ms philo %d die\n",((get_time() - data->time)), data->philo[i].id);
			return ;
		}
		i++;
		if (i == data->num_ph)
			i = 0;
	}
	while (++j < data->num_ph)
		pthread_mutex_destroy(&data->fork[j]);
	
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (check_error(ac, av, data))
 		creat_philo(data);
}
