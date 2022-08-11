/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/11 13:48:17 by cpost         #+#    #+#                 */
/*   Updated: 2022/08/11 17:37:53 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
# include <pthread.h>
# include <stdbool.h>

# define mutex pthread_mutex_t

typedef enum e_validation {
	SUCCES,
	FAILURE
}	exit_code;

typedef struct s_data {
	unsigned int	amount_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned long	start_time;
	unsigned int	eat_limit;
	bool			eat_limit_enabled;
	bool			philo_dead;
	mutex			philo_dead_lock;
	mutex			write_lock;
	mutex			*forks;
	pthread_t		*thread;
}	t_data;

typedef struct s_philo {
	unsigned int	id;
	unsigned int	x_eaten;
	unsigned int	last_meal;
	mutex			*left_fork;
	mutex			*right_fork;
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


#endif