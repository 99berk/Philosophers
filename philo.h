/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bakgun <bakgun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:58:19 by bakgun            #+#    #+#             */
/*   Updated: 2024/03/22 11:46:55 by bakgun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define ARG_MSG "Args must be like:\n\x1b[33m<number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]"
# define ERR_MSG_POSITIVE "Invalid argument\nArgs must be positive int"
# define ERR_MSG "Error\nMutex can't be locked"

# include <pthread.h>

typedef struct s_philo
{
	int				eat_count;
	size_t			last_ate;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	struct s_vars	*vars;
	int				index;			
}	t_philo;

typedef struct s_vars
{
	int				count;
	int				is_dead;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				max_eat;
	int				num;
	int				death_i;
	pthread_mutex_t	death;
	pthread_mutex_t	eat;
	size_t			start_time;
	t_philo			*philos;
}	t_vars;

void	print_error(char *str);
int		ft_atoi(char *num);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	get_time(void);
void	*life_of_philo(void *arg);
int		ft_usleep(size_t miliseconds, t_philo *philo);
int		check_dead(t_philo *philo);
void	print_time(char *str, int i, t_vars *vars, size_t current);
void	*die(t_vars *vars, int index, int print);
void	*smell_of_death(void *arg);

#endif