/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakgun <bakgun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:38:25 by bakgun            #+#    #+#             */
/*   Updated: 2024/01/03 18:06:42 by bakgun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <sys/time.h>

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_sec / 1000));
}

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
}

int	philo_atoi(char *str, int check)
{
	int				i;
	int				sign;
	unsigned long	num;

	i = 0;
	sign = 1;
	num = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			return (ft_putstr("Arguments can not be a negative number.\n"), 0);
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		num = (num * 10) + (str[i++] - '0');
	}
	if ((num > 2147483648 && sign == -1) || (num > 2147483647 && sign == 1))
		return (ft_putstr("Argument is out of integer limits.\n"), 0);
	if (check == 1)
		return (1);
	return (num * sign);
}

int	check_args(char **argv)
{
	int i;

	i = 0;
	while (argv[++i])
		if (argv[i])
			if (philo_atoi(argv[i], 1) == 0)
				return (0);
	return (1);
}

int	set_and_ready(t_var *args, char **argv)
{
	args->number_of_philosophers = philo_atoi(argv[1], 0);
	args->time_to_die = philo_atoi(argv[2], 0);
	args->time_to_eat = philo_atoi(argv[3], 0);
	args->time_to_sleep = philo_atoi(argv[4], 0);
	if (argv[5])
		args->number_of_times_each_philosopher_must_eat = philo_atoi(argv[5], 0);
	else
		args->number_of_times_each_philosopher_must_eat = -1;
	args->philosopher_dead = 0;
	return (1);
}

int	main(int argc, char **argv)
{
	t_var	args;
	
	if (argc == 5 || argc == 6)
	{
		if (check_args(argv))
		{
			if (set_and_ready(&args, argv))
			{
				
			}
		}
	}
	else
		ft_putstr("Wrong number of argument.\nCorrect usage: ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
}
