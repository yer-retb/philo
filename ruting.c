/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ruting.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-retb <yer-retb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 01:30:06 by yer-retb          #+#    #+#             */
/*   Updated: 2022/09/04 01:30:53 by yer-retb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	taking_and_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->d->fork[philo->left_f]);
	pthread_mutex_lock(philo->d->print);
	printf("\033[1;32m%ld ms philo %d has taken a fork\n",
		get_time() - philo->d->time, philo->id);
	pthread_mutex_unlock(philo->d->print);
	pthread_mutex_lock(&philo->d->fork[philo->right_f]);
	pthread_mutex_lock(philo->d->print);
	printf("\033[1;32m%ld ms philo %d has taken a fork\n",
		get_time() - philo->d->time, philo->id);
	pthread_mutex_unlock(philo->d->print);
	pthread_mutex_lock(philo->d->print);
	printf("\033[1;33m%ld ms philo %d is eating\n",
		get_time() - philo->d->time, philo->id);
	philo->temp = get_time() - philo->d->time;
	pthread_mutex_lock(philo->d->test);
	philo->d->sig += 1;
	pthread_mutex_unlock(philo->d->test);
	pthread_mutex_unlock(philo->d->print);
	ft_usleep(philo->d->eat);
}

void	*the_table(void *av)
{
	t_philo	*philo;

	philo = (t_philo *)av;
	if (philo->id % 2 == 0)
		usleep(60);
	while (1)
	{
		taking_and_eating(philo);
		pthread_mutex_lock(philo->d->print);
		printf("\033[1;34m%ld ms philo %d is sleeping\n",
			get_time() - philo->d->time, philo->id);
		pthread_mutex_unlock(philo->d->print);
		pthread_mutex_unlock(&philo->d->fork[philo->left_f]);
		pthread_mutex_unlock(&philo->d->fork[philo->right_f]);
		ft_usleep(philo->d->sleep);
		pthread_mutex_lock(philo->d->print);
		printf("\033[1;30m%ld ms philo %d is thinking\n",
			get_time() - philo->d->time, philo->id);
		pthread_mutex_unlock(philo->d->print);
	}
	return (0);
}

int	deff(t_philo data)
{
	if ((get_time() - data.d->time) - (data.temp) >= data.d->die)
		return (0);
	return (1);
}

int	timing(t_data *data)
{
	pthread_mutex_lock(data->test);
	if ((data->sig / data->tour) == data->num_ph)
		return (0);
	pthread_mutex_unlock(data->test);
	return (1);
}

void	ruting(t_data *data)
{
	int	i;

	i = 0;
	make_philos(data);
	while (1)
	{
		if (!(timing(data)))
			return ;
		if (!deff(data->philo[i]))
		{
			pthread_mutex_lock(data->print);
			printf("\033[1;31m%ld ms philo %d die\n",
				((get_time() - data->time)), data->philo[i].id);
			return ;
		}
		i++;
		if (i == data->num_ph)
			i = 0;
	}
}
