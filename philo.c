/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-retb <yer-retb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 15:27:35 by yer-retb          #+#    #+#             */
/*   Updated: 2022/08/20 18:01:35 by yer-retb         ###   ########.fr       */
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
		return (0);
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

int	main(int ac, char **av)
{
	t_philo *src;
	t_data	*data;
	int tour;

	tour = 0;
	src = malloc(sizeof(t_philo));
	data = malloc(sizeof(t_data));	
	check_error(ac, av, src, data);
	creat_philo(src, data);
}
