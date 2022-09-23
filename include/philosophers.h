/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/11 13:48:17 by cpost         #+#    #+#                 */
/*   Updated: 2022/09/23 13:14:09 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

#define ALL_MUTEXES 99

typedef enum e_status {
	SUCCES,
	FAILURE,
	FORK,
	SLEEPING,
	EATING,
	THINKING,
	DIED
}	t_status;

typedef struct s_data {
	unsigned int	amount_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	time_to_think;
	unsigned long	start_time;
	unsigned int	eat_limit;
	bool			eat_limit_enabled;
	bool			philo_dead;
	bool			thread_init_failed;
	pthread_mutex_t	thread_init_lock;
	pthread_mutex_t	philo_dead_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
}	t_data;

typedef struct s_philo {
	unsigned int	id;
	unsigned int	x_eaten;
	long			last_meal;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

//utils.c

bool			an_argument_is_zero(t_data *data);
unsigned long	get_current_time(void);
void			*ft_calloc(size_t nmemb, size_t size);
void			set_time_to_think(t_data *data);

//initiate_data_struct.c

t_data			*initiate_data_struct(int argument_count, char **argument);

//initiate_philo_struct.c

t_philo			*initiate_philo_struct(t_data *data);

//initiate_threads.c

pthread_t		*initiate_threads(t_philo *philo, t_data *data);

//philosopher.c

void			*run_philosopher(void *philo_struct);

//monitor.c

bool			thread_init_success(t_data *data);
void			monitor_shit(t_data *data, t_philo *philo,
					unsigned int finished, unsigned int i);
bool			terminate_thread(t_data *data);
bool			kill_philo(t_philo *philo);
bool			philo_ate_enough(t_data *data, t_philo *philo);

//philosopher_actions.c

bool			eating(t_philo *philo);
bool			sleeping(t_philo *philo);
bool			thinking(t_philo *philo);
void			print_message(t_philo *philo, t_status status);

//destroy_mutexes.c

void			destroy_mutexes(t_data *data, unsigned int mutexes_created);
void			destroy_forks(t_data *data, unsigned int created_forks);
void			destroy_all(t_data *data, t_philo *philo);
void			destroy_meal_lock(t_philo *philo, unsigned int created);

#endif