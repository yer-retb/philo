/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-retb <yer-retb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:41:57 by yer-retb          #+#    #+#             */
/*   Updated: 2022/09/04 05:50:12 by yer-retb         ###   ########.fr       */
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
	int				flag;	
	int				id;
	int				left_f;
	int				right_f;
	long int		time_start;
	long int		temp;
	pthread_t		pt;
	struct n_data	*d;

}t_philo;

typedef struct n_data
{
	int				sig;
	int				num_ph;
	int				die;
	int				eat;
	int				sleep;
	int				tour;
	long int		time;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*test;
}t_data;

void		creat_philo(t_data *data);
void		*the_table(void *av);
int			check_error(int ac, char **av, t_data *data);
int			ft_atoi(char *str);
long int	get_time(void);
void		ft_usleep(int time);
void		taking_and_eating(t_philo *philo);
void		make_philos(t_data *data);
int			deff(t_philo data);
int			timing(t_data *data);
void		ruting(t_data *data);

#endif
