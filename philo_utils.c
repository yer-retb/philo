/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-retb <yer-retb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:16:52 by yer-retb          #+#    #+#             */
/*   Updated: 2022/08/25 02:47:01 by yer-retb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	struct timeval timing;
	long int time;
	
	if (gettimeofday(&timing, NULL) == -1)
		return (0);
	time = (timing.tv_sec * 1000) + (timing.tv_usec / 1000);
	return(time);
}

void	ft_usleep(int time)
{
	long long t = get_time();

	while (get_time() - t < time)
		usleep(60);
}
