/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/11 13:48:17 by cpost         #+#    #+#                 */
/*   Updated: 2022/08/31 15:00:12 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
# include <pthread.h>
# include <stdbool.h>

typedef enum e_status {
	SUCCES,
	FAILURE
}	t_status;

typedef struct s_data {
	char			**print_queue;
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
	pthread_t		*thread;
}	t_data;

typedef struct s_philo {
	unsigned int	id;
	unsigned int	x_eaten;
	unsigned int	last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

//main.c

void	print_values(t_data	*data);

//utils.c

bool	an_argument_is_zero(t_data *data);
long	get_current_time(void);

//initiate_data_struct.c

t_data	*initiate_data_struct(int argument_count, char **argument);

//initiate_philo_struct.c

t_philo	*initiate_philo_struct(t_data *data);

//initiate_threads.c

bool	initiate_philo_threads(t_philo *philo, t_data *data);

//philosopher.c

void	*run_philosopher(void *philo_struct);

//philosopher_actions.c

void	eat(t_philo *philo);
void	sleep(t_philo *philo);
void	think(t_philo *philo);
void	repeat(void);

//destroy_mutexes.c

void	destroy_mutexes(t_data *data, unsigned int mutexes_created);
void	destroy_forks(pthread_mutex_t *fork_array, unsigned int created_forks);

#endif