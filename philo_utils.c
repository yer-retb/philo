/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-retb <yer-retb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:16:52 by yer-retb          #+#    #+#             */
/*   Updated: 2022/09/04 01:17:12 by yer-retb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	struct timeval	timing;
	long int		time;

	if (gettimeofday(&timing, NULL) == -1)
		return (0);
	time = (timing.tv_sec * 1000) + (timing.tv_usec / 1000);
	return (time);
}

void	ft_usleep(int time)
{
	long long	t;

	t = get_time();
	while (get_time() - t < time)
		usleep(60);
}

int	ft_atoi(char *str)
{
	int				i;
	unsigned long	rsl;

	i = 0;
	rsl = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		rsl = rsl * 10 + str[i] - 48;
		i++;
	}
	return (rsl);
}

void	passing_args(t_data *data, char **av)
{
	if (av[5])
		data->tour = ft_atoi(av[5]);
	data->num_ph = ft_atoi(av[1]);
	data->die = ft_atoi(av[2]);
	data->eat = ft_atoi(av[3]);
	data->sleep = ft_atoi(av[4]);
}

int	check_error(int ac, char **av, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (ac < 5 || ac > 6)
	{
		printf("Error : Check your arguments\n");
		return (0);
	}
	while (++i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if ((av[i][j] >= 0 && av[i][j] < 48)
				|| (av[i][j] > 57) || (av[i][0] == '0'))
			{
				printf("Error : Check your arguments\n");
				return (0);
			}
			j++;
		}
	}
	passing_args(data, av);
	return (1);
}
