/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:22:21 by aaltinto          #+#    #+#             */
/*   Updated: 2024/02/08 16:23:46 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->vars->death) != 0)
		return (err_msg("Error\nMutex can't be locked"), 1);
	if (philo->vars->is_dead == 1)
		return (pthread_mutex_unlock(&philo->vars->death), 1);
	return (pthread_mutex_unlock(&philo->vars->death), 0);
}

static void	die(t_vars *vars, int index)
{
	size_t	die_time;

	if (pthread_mutex_lock(&vars->death) != 0)
		err_msg("Error\nMutex can't be locked");
	vars->is_dead = 1;
	die_time = get_time();
	pthread_mutex_unlock(&vars->death);
	ft_usleep(10);
	print_time("\033[0;31mdied", index, vars, die_time);
}

static int	check_all(t_vars *vars)
{
	int	i;
	int	counter;

	i = -1;
	counter = 0;
	pthread_mutex_lock(&vars->eat);
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

void	*death_note(void *arg)
{
	t_vars	*vars;
	int		i;
	int		time;

	vars = (t_vars *)arg;
	while (1)
	{
		if (pthread_mutex_lock(&vars->death) != 0)
			return (err_msg("Error\nMutex can't be locked"), NULL);
		if (vars->max_eat > -1)
			if (check_all(vars))
				return (pthread_mutex_unlock(&vars->death), NULL);
		pthread_mutex_unlock(&vars->death);
		i = -1;
		while (++i < vars->count)
		{
			if (pthread_mutex_lock(&vars->eat) != 0)
				return (err_msg("Error\nMutex can't be locked"), NULL);
			time = get_time() - vars->philos[i].last_ate;
			pthread_mutex_unlock(&vars->eat);
			if (time > vars->time_to_die)
				return (die(vars, i + 1), NULL);
		}
	}
}
