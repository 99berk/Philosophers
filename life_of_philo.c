/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakgun <bakgun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:55:25 by bakgun            #+#    #+#             */
/*   Updated: 2024/03/22 11:47:08 by bakgun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	take_fork(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->l_fork) != 0)
		return (print_error("Error\nFork can't be locked"), 1);
	if (check_dead(philo))
		return (pthread_mutex_unlock(&philo->l_fork), 1);
	print_time("has take a fork", philo->index, philo->vars, get_time());
	if (philo->vars->count == 1)
	{
		while (!check_dead(philo))
			usleep(100);
		return (pthread_mutex_unlock(&philo->l_fork), 1);
	}
	if (pthread_mutex_lock(philo->r_fork) != 0)
		return (print_error("Error\nFork can't be locked"), 1);
	if (check_dead(philo))
		return (pthread_mutex_unlock(&philo->l_fork),
			pthread_mutex_unlock(philo->r_fork), 1);
	return (print_time("has take a fork", philo->index,
			philo->vars, get_time()), 0);
}

int	eat(t_philo *philo)
{
	if (check_dead(philo))
		return (pthread_mutex_unlock(&philo->l_fork),
			pthread_mutex_unlock(philo->r_fork), 1);
	print_time("\033[0;32mis eating", philo->index,
		philo->vars, get_time());
	if (ft_usleep(philo->vars->time_to_eat, philo))
		return (pthread_mutex_unlock(&philo->l_fork),
			pthread_mutex_unlock(philo->r_fork), 1);
	if (pthread_mutex_lock(&philo->vars->eat) != 0)
		return (print_error("Error\nFork can't be locked"),
			pthread_mutex_unlock(&philo->l_fork),
			pthread_mutex_unlock(philo->r_fork), 1);
	philo->last_ate = get_time();
	pthread_mutex_unlock(&philo->vars->eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (philo->eat_count++, 0);
}

int	sleep_and_think(t_philo *philo)
{
	if (check_dead(philo))
		return (1);
	print_time("is sleeping", philo->index, philo->vars, get_time());
	if (ft_usleep(philo->vars->time_to_sleep, philo))
		return (1);
	if (check_dead(philo))
		return (1);
	print_time("is thinking", philo->index, philo->vars, get_time());
	return (0);
}

void	*life_of_philo(void *arg)
{
	t_philo	*philo;
	t_vars	*vars;

	philo = (t_philo *)arg;
	vars = philo->vars;
	if (philo->index % 2 == 0)
		ft_usleep(10, philo);
	while (1)
	{
		if (check_dead(philo) || take_fork(philo))
			return (die(vars, 0, 0));
		if (check_dead(philo) || eat(philo))
			return (die(vars, 0, 0));
		if (check_dead(philo) || sleep_and_think(philo))
			return (die(vars, 0, 0));
	}
	return (NULL);
}
