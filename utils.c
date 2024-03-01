/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakgun <bakgun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:14:51 by bakgun            #+#    #+#             */
/*   Updated: 2024/03/01 17:35:58 by bakgun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include "philo.h"
#include <stdio.h>

void	print_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(2, str, i);
	write(2, "\n", 1);
}

int	ft_atoi(char *num)
{
	long	number;
	size_t	i;

	number = 0;
	i = -1;
	while (num[++i])
	{
		if (!(num[i] <= '9' && num[i] >= '0'))
			return (0);
		number = (number * 10) + (num[i] - 48);
	}
	if (number < -2147483648 || number > 2147483647)
		return (-1);
	return (number);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		print_error("gettimeofday() error");
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(size_t miliseconds, t_philo *philo)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < miliseconds)
	{
		usleep(100);
		if (philo->vars->is_dead == 1)
			return (1);
	}
	return (0);
}

void	print_time(char *str, int i, t_vars *vars, size_t current)
{
	size_t	p_time;

	p_time = current - vars->start_time;
	printf("%ld %d %s\033[0;37m\n", p_time, i, str);
}
