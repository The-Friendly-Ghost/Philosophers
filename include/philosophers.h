/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/11 13:48:17 by cpost         #+#    #+#                 */
/*   Updated: 2022/08/01 13:55:44 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
# include <pthread.h>
# include <stdbool.h>

typedef enum e_validation {
	SUCCES,
	FAILURE
}	exit_code;

typedef struct s_data {
	unsigned int	amount_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	eat_limit;
	bool			eat_limit_enabled;
	unsigned long	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	philo_dead_lock;
	bool			philo_dead;
	pthread_mutex_t	write_lock;
}	t_data;

typedef struct s_philo {
	unsigned int	id;
	unsigned int	x_eaten;
	unsigned int	last_meal;
	t_data			*data;
}	t_philo;

//utils.c

bool	an_argument_is_zero(t_data *data);

//initiate_data_struct.c

t_data	*initiate_data_struct(int argument_count, char **argument);

//main.c

void	print_values(t_data	*data);

#endif