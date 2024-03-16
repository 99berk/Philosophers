/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smell_of_death.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakgun <bakgun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:55:36 by bakgun            #+#    #+#             */
/*   Updated: 2024/03/16 17:25:08 by bakgun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->vars->death) != 0)
		return (print_error("Error\nMutex can't be locked"), 1);
	if (philo->vars->is_dead == 1)
		return (pthread_mutex_unlock(&philo->vars->death), 1);
	return (pthread_mutex_unlock(&philo->vars->death), 0);
}

void	*die(t_vars *vars, int index, int print)
{
	size_t	die_time;

	if (check_dead(&vars->philos[0]))
		return (NULL);
	if (pthread_mutex_lock(&vars->death) != 0)
		return (print_error("Error\nMutex can't be locked"), NULL);
	vars->is_dead = 1;
	die_time = get_time();
	pthread_mutex_unlock(&vars->death);
	ft_usleep(10, &vars->philos[0]);
	if (print)
		print_time("\033[0;31mdied", index, vars, die_time);
	return (NULL);
}

int	ctrl_max_eat(t_vars *vars)
{
	int	i;
	int	counter;

	i = -1;
	counter = 0;
	if (pthread_mutex_lock(&vars->eat) != 0)
		return (print_error("Error\nMutex can't be locked"), 1);
	while (++i < vars->count)
		if (vars->philos[i].eat_count >= vars->max_eat)
			counter++;
	if (counter == vars->count)
	{
		vars->is_dead = 1;
		return (pthread_mutex_unlock(&vars->eat), 1);
	}
	return (pthread_mutex_unlock(&vars->eat), 0);
}

void	*smell_of_death(void *arg)
{
	t_vars	*vars;
	int		time;

	vars = (t_vars *)arg;
	while (1)
	{
		if (pthread_mutex_lock(&vars->death) != 0)
			return (print_error("Error\nMutex can't be locked"), NULL);
		if (vars->max_eat > -1)
			if (ctrl_max_eat(vars))
				return (pthread_mutex_unlock(&vars->death), die(vars, 0, 0), NULL);
		pthread_mutex_unlock(&vars->death);
		vars->death_i = -1;
		if (check_dead(&vars->philos[0]))
			return (NULL);
		while (++vars->death_i < vars->count)
		{
			if (pthread_mutex_lock(&vars->eat) != 0)
				return (print_error("Error\nMutex can't be locked"), die(vars, 0, 0), NULL);
			time = get_time() - vars->philos[vars->death_i].last_ate;
			pthread_mutex_unlock(&vars->eat);
			if (time > vars->time_to_die)
				return (die(vars, vars->death_i + 1, 1));
		}
	}
}
