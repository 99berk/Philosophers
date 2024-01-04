/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakgun <bakgun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:11:30 by bakgun            #+#    #+#             */
/*   Updated: 2024/01/04 14:09:07 by bakgun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>

typedef struct s_philo
{
	pthread_t		philo_thread_id;
	int				last_ate;
	int				eat_time;
	pthread_mutex_t	*fork;
}	t_pihlo;

typedef struct s_var
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				philosopher_dead;
	int				s_time;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	mutex;
	t_pihlo			*philosophers;
} t_var;

#endif