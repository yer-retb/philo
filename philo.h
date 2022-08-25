/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-retb <yer-retb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:41:57 by yer-retb          #+#    #+#             */
/*   Updated: 2022/08/25 03:24:55 by yer-retb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>	
# include <sys/time.h>

typedef struct n_philo
{
	int				tem;
	int				id;
	long int		time_start;
	int				left_f;
	int				right_f;
	pthread_t		pt;
	struct n_data	*d;
} t_philo;

typedef struct n_data
{	
	long int		time;
	int				num_ph;
	int				die;
	int				eat;
	int				sleep;
	int 			sig;
	int				tour;
	t_philo			*philo;
	pthread_mutex_t *fork;
	pthread_mutex_t *print;
} t_data;

void	creat_philo(t_data *data);
void	*the_table(void *av);
void	check_error(int ac, char **av,t_data *data);
int		ft_atoi(char *str);
long int	get_time(void);
void	ft_usleep(int time);

#endif
