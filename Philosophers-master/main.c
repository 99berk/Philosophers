/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakgun <bakgun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:26:00 by aaltinto          #+#    #+#             */
/*   Updated: 2024/02/15 17:58:47 by bakgun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	abort_mission(t_vars *vars, pthread_t **threads_id)
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
	pthread_t	azrael;
	int			i;

	if (argc < 5 || argc > 6)
		return (err_msg(ARG_MSG), 1);
	threads_id = NULL;
	if (!philo_fill(argc, argv, &vars))
		return (1);
	if (!philo_mutex_init(&vars, -1))
		return (abort_mission(&vars, &threads_id), 1);
	threads_id = malloc(sizeof(pthread_t) * (vars.count));
	if (!threads_id)
		return (err_msg("Error\nMalloc error"),
			abort_mission(&vars, &threads_id), 1);
	i = -1;
	while (++i < vars.count)
		pthread_create(&threads_id[i], NULL, eat_sleep_repeat, &vars.philos[i]);
	pthread_create(&azrael, NULL, death_note, &vars);
	i = -1;
	while (++i < vars.count)
		pthread_join(threads_id[i], NULL);
	pthread_join(azrael, NULL);
	return (abort_mission(&vars, &threads_id), 0);
}
