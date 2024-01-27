#ifndef PHILO2_H
# define PHILO2_H

#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	pthread_t		philo_thread_id;
	int				philo_id;
	int				last_ate;
	int				eat_count;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_var	*var;
}	t_philo;

typedef struct s_var
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				philosopher_dead;
	suseconds_t		s_time;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	mutex;
	t_philo			*philosophers;
} t_var;

#endif