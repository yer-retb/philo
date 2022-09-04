/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-retb <yer-retb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 15:27:35 by yer-retb          #+#    #+#             */
/*   Updated: 2022/09/04 18:39:24 by yer-retb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	make_philos(t_data *data)
{
	int	i;

	i = 0;
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
}

void	creat_philo(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	data->philo = malloc(sizeof(t_data) * data->num_ph);
	data->fork = malloc (sizeof(pthread_mutex_t) * data->num_ph);
	data->print = malloc (sizeof(pthread_mutex_t));
	data->test = malloc (sizeof(pthread_mutex_t));
	if (!data->philo || !data->fork || !data->print || !data->test)
		return ;
	pthread_mutex_init(data->print, NULL);
	pthread_mutex_init(data->test, NULL);
	while (++j < data->num_ph)
		pthread_mutex_init(&data->fork[j], NULL);
	ruting(data);
	j = -1;
	while (++j < data->num_ph)
		pthread_mutex_destroy(&data->fork[j]);
	pthread_mutex_destroy(data->test);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (check_error(ac, av, data))
		creat_philo(data);
}
