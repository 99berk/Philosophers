/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakgun <bakgun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:47:15 by aaltinto          #+#    #+#             */
/*   Updated: 2024/02/15 18:01:05 by bakgun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static int	max_eat_fill(t_vars *vars, int argv)
{
	if (argv <= 0)
		return (-1);
	vars->max_eat = argv;
	return (1);
}

int	philo_mutex_init(t_vars *vars, int i)
{
	vars->philos = malloc(sizeof(t_philo) * vars->count);
	if (!vars->philos)
		return (err_msg("malloc error"), 0);
	if ((pthread_mutex_init(&vars->eat, NULL) != 0 || !++vars->num)
		|| (pthread_mutex_init(&vars->death, NULL) != 0 || !++vars->num))
		return (err_msg("mutex init error"), 0);
	while (++i < vars->count)
	{
		if (pthread_mutex_init(&vars->philos[i].l_fork, NULL) != 0)
			return (err_msg("mutex init error"), 0);
		vars->num++;
		if (i == vars->count -1)
			vars->philos[i].r_fork = &vars->philos[0].l_fork;
		else
			vars->philos[i].r_fork = &vars->philos[i + 1].l_fork;
		vars->philos[i].eat_count = 0;
		vars->philos[i].index = i + 1;
		vars->philos[i].last_ate = vars->start_time;
		vars->philos[i].vars = vars;
	}
	return (1);
}

int	philo_fill(int argc, char **argv, t_vars *vars)
{
	int	i;

	vars->philos = NULL;
	vars->num = 0;
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0
		|| ft_atoi(argv[4]) <= 0)
		return (err_msg(ERR_MSG_POSITIVE), 0);
	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		vars->count = ft_atoi(argv[1]);
		vars->time_to_die = ft_atoi(argv[2]);
		vars->time_to_eat = ft_atoi(argv[3]);
		vars->time_to_sleep = ft_atoi(argv[4]);
		vars->start_time = get_time();
		vars->is_dead = 0;
		if (argc == 6)
		{
			if (max_eat_fill(vars, ft_atoi(argv[5])) != 1)
				return (err_msg(ERR_MSG_POSITIVE), 0);
		}
		else
			vars->max_eat = -1;
	}
	return (1);
}
