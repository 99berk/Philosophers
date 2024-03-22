/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakgun <bakgun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:55:37 by bakgun            #+#    #+#             */
/*   Updated: 2024/03/22 10:42:26 by bakgun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdlib.h>

int	set_max_eat(t_vars *vars, int argv)
{
	if (argv <= 0)
		return (-1);
	vars->max_eat = argv;
	return (1);
}

int	set_philo(int argc, char **argv, t_vars *vars)
{
	vars->philos = NULL;
	vars->num = 0;
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0
		|| ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
		return (print_error("Invalid argument\nArgs must be positive int"), 0);
	vars->count = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	vars->start_time = get_time();
	vars->is_dead = 0;
	if (argc == 6)
	{
		if (set_max_eat(vars, ft_atoi(argv[5])) != 1)
			return (print_error(ERR_MSG_POSITIVE), 0);
	}
	else
		vars->max_eat = -1;
	return (1);
}

int	philo_mutex_init(t_vars *vars, int i)
{
	vars->philos = malloc(sizeof(t_philo) * vars->count);
	if (!vars->philos)
		return (print_error("Malloc error"), 0);
	if ((pthread_mutex_init(&vars->eat, NULL) != 0 || !++vars->num)
		|| (pthread_mutex_init(&vars->death, NULL) != 0 || !++vars->num))
		return (print_error("Mutex init error"), 0);
	while (++i < vars->count)
	{
		if (pthread_mutex_init(&vars->philos[i].l_fork, NULL) != 0)
			return (print_error("Mutex init error"), 0);
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

void	destroy_and_free(t_vars *vars, pthread_t **threads_id)
{
	int	i;

	if (*threads_id != NULL)
		free(*threads_id);
	i = -1;
	if (++i < vars->num)
		pthread_mutex_destroy(&vars->eat);
	if (++i < vars->num)
		pthread_mutex_destroy(&vars->death);
	i = -1;
	while (++i < vars->count && i + 2 < vars->num)
		pthread_mutex_destroy(&vars->philos[i].l_fork);
	if (vars->philos != NULL)
		free(vars->philos);
}

int	main(int argc, char **argv)
{
	t_vars		vars;
	pthread_t	*threads_id;
	pthread_t	killer;
	int			i;

	if (argc < 5 || argc > 6)
		return (print_error(ARG_MSG), 1);
	threads_id = NULL;
	if (!set_philo(argc, argv, &vars))
		return (1);
	if (!philo_mutex_init(&vars, -1))
		return (destroy_and_free(&vars, &threads_id), 1);
	threads_id = malloc(sizeof(pthread_t) * vars.count);
	if (!threads_id)
		return (print_error("Malloc error"),
			destroy_and_free(&vars, &threads_id), 1);
	i = -1;
	while (++i < vars.count)
		pthread_create(&threads_id[i], NULL, life_of_philo, &vars.philos[i]);
	pthread_create(&killer, NULL, smell_of_death, &vars);
	i = -1;
	while (++i < vars.count)
		pthread_join(threads_id[i], NULL);
	pthread_join(killer, NULL);
	return (destroy_and_free(&vars, &threads_id), 0);
}
