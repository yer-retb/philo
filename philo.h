/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-retb <yer-retb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:41:57 by yer-retb          #+#    #+#             */
/*   Updated: 2022/08/22 12:48:32 by yer-retb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>	

typedef struct n_philo
{
	int				phi;
	int				die;
	int				eat;
	int				sleep;
	int				index;
	pthread_t		philos;
	pthread_mutex_t *fork;
	
} t_philo;

typedef struct n_data
{	
	int 			sig;
	int				tour;
} t_data;

void	creat_philo(t_philo *src, t_data *data);
void	*the_table(void *av);
void	check_error(int ac, char **av, t_philo *src, t_data *data);
int		ft_atoi(char *str);

#endif
