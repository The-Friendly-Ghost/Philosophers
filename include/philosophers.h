/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/11 13:48:17 by cpost         #+#    #+#                 */
/*   Updated: 2022/07/29 15:01:02 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>

typedef enum e_exit {
	SUCCES,
	FAILURE,
	INPUT_VALID,
	INPUT_NOT_VALID,
	MALLOC_FAIL
}	t_exit;

typedef struct s_data {
	unsigned int	amount_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	x_times_to_eat;
}	t_data;

typedef struct s_philo {
	unsigned int	id;
	unsigned int	x_eaten;
	unsigned int	last_meal;
	pthread_mutex_t	
	t_data			*data;
}	t_philo;

//parse_arguments.c

t_data	*parse_arguments(int argument_count, char **argument);

//main.c

void	print_values(t_data	*data);

#endif