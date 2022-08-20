/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-retb <yer-retb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:41:57 by yer-retb          #+#    #+#             */
/*   Updated: 2022/08/14 16:43:51 by yer-retb         ###   ########.fr       */
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
	struct n_philo *next;
	int				phi;
	int				die;
	int				eat;
	int				sleep;
	
	
} t_philo;

typedef struct n_data
{	
	pthread_mutex_t	mutex;
	int 			sig;
	int				tour;

} t_data;


#endif
