#include "philo2.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

suseconds_t	get_time(void)
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

int	mutex_create(t_var *args)
{
	int	i;

	i = -1;
	args->fork_mutex = malloc(sizeof(pthread_mutex_t) * args->number_of_philosophers);
	if (!args->fork_mutex)
		return (0);
	while (++i < args->number_of_philosophers)
		pthread_mutex_init(&args->fork_mutex[i], NULL);
	pthread_mutex_init(&args->mutex, NULL);
	return (1);
}

int	philo_create(t_var *args)
{
	int	i;

	i = -1;
	args->philosophers = malloc(sizeof(t_philo) * args->number_of_philosophers);
	if (!args->philosophers)
		return (0);
	while (++i < args->number_of_philosophers)
	{
		args->philosophers[i].philo_id = i + 1;
		args->philosophers[i].l_fork = &args->fork_mutex[i];
		args->philosophers[i].r_fork = &args->fork_mutex[(i + 1) % args->number_of_philosophers];
		args->philosophers[i].var = args;
		args->philosophers[i].last_ate = 0;
		args->philosophers[i].eat_count = 0;
	}
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
	if (mutex_create(args) == 0)
		return (0);
	if (philo_create(args) == 0)
		return (0);
	return (1);
}

void	print_philo(t_philo *philos, char *str)
{
	printf("%ld philo[%d] %s\n", get_time() - philos->var->s_time, philos->philo_id, str);
}

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->var->mutex);
    if ((philo->var->time_to_die < (get_time() - philo->var->s_time - philo->last_ate)))
    {
        philo->var->philosopher_dead = 1;
		printf("die:%d, last_eat:%d, now-eat:%d ... ->", philo->var->time_to_die, philo->last_ate, (get_time() - philo->var->s_time - philo->last_ate));
		print_philo(philo, "is dead");
        pthread_mutex_unlock(&philo->var->mutex);
        return 1;
    }
    pthread_mutex_unlock(&philo->var->mutex);
    return 0;
}

int	philo_takes_forks(t_philo *philos)
{
	if (philos->philo_id % 2 == 0)
		pthread_mutex_lock(philos->r_fork);
	else
		pthread_mutex_lock(philos->l_fork);
	if (!check_dead(philos))
		print_philo(philos, "has taken a fork");
	if (philos->philo_id % 2 == 0)
	{
		if (pthread_mutex_lock(philos->l_fork) != 0)
			return (pthread_mutex_unlock(philos->r_fork), 1);
		if (!check_dead(philos))
			print_philo(philos, "has taken a fork");
	}
	else
	{
		if (pthread_mutex_lock(philos->r_fork) != 0)
			return(pthread_mutex_unlock(philos->l_fork), 1);
		if (!check_dead(philos))
			print_philo(philos, "has taken a fork");
	}
	return (0);
}

void	philo_is_eating(t_philo *philos)
{
	print_philo(philos, "is eating");
	pthread_mutex_lock(&philos->var->mutex);
	philos->last_ate = get_time() - philos->var->s_time;
	pthread_mutex_unlock(&philos->var->mutex);
	usleep(philos->var->time_to_eat * 1000);
	pthread_mutex_lock(&philos->var->mutex);
	if (philos->eat_count != -1)
		philos->eat_count++;
	pthread_mutex_unlock(&philos->var->mutex);
	pthread_mutex_unlock(philos->l_fork);
	pthread_mutex_unlock(philos->r_fork);
}

void	philo_is_sleeping(t_philo *philos)
{
	print_philo(philos, "is sleeping");
	usleep(philos->var->time_to_sleep * 1000);
}

void	philo_is_thinking(t_philo *philos)
{
	print_philo(philos, "is thinking");
}

void	*philo_life(void *args)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = (t_philo *)args;
	while (philos->var->philosopher_dead == 0)
	{
		if (check_dead(philos))
			return (0);
		philo_takes_forks(philos);
		if (check_dead(philos))
		{
			pthread_mutex_unlock(philos->l_fork);
			pthread_mutex_unlock(philos->r_fork);
			return (0);
		}
		philo_is_eating(philos);
		if (check_dead(philos))
			return (0);
		philo_is_sleeping(philos);
		if (check_dead(philos))
			return (0);
		philo_is_thinking(philos);
	}
	return (0);
}

void	start_philos(t_var *args)
{
	int	i;

	i = -1;
	args->s_time = get_time();
	while (++i < args->number_of_philosophers)
		pthread_create(&args->philosophers[i].philo_thread_id, NULL, philo_life, (void *)&args->philosophers[i]);
	i = -1;
	while (++i < args->number_of_philosophers)
		pthread_join(args->philosophers[i].philo_thread_id, NULL);
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
				start_philos(&args);
			}
		}
	}
	else
		ft_putstr("Wrong number of argument.\nCorrect usage: ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
}