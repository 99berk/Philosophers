/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaltinto <aaltinto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:57:56 by aaltinto          #+#    #+#             */
/*   Updated: 2024/02/12 12:06:34 by aaltinto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include "philo.h"

int	ft_atoi(char *num)
{
	long	ret;
	size_t	i;

	ret = 0;
	i = -1;
	while (num[++i])
	{
		if (num[i] > '9' && num[i] > '0')
			return (0);
		ret = (ret * 10) + (num[i] - 48);
	}
	if (ret < -2147483648 || ret > 2147483647)
		return (-1);
	return (ret);
}

void	err_msg(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
		i++;
	write(2, msg, i);
	write(2, "\n", 1);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		err_msg("gettimeofday() error");
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_time(char *msg, int i, t_vars *vars, size_t current)
{
	size_t	p_time;

	p_time = current - vars->start_time;
	printf("%ld %d %s\033[0;37m\n", p_time, i, msg);
}

int	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
	{
		usleep(100);
		if (philo->vars->is_dead == 1)
			return (1);
	}
	return (0);
}
