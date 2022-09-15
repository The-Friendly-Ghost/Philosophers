/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initiate_data_struct.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/12 12:20:19 by cpost         #+#    #+#                 */
/*   Updated: 2022/09/15 10:36:26 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>

/**
 * Initiates array of mutexes (each mutex is a fork). For every philosopher,
 * one fork mutex is initiated.
 * @param data Struct with the program data in it
 * @return True if initiation without error. False if there
 * is an error somewhere.
 */
static bool	initiate_forks(unsigned int amount_philos,
		pthread_mutex_t *fork_array)
{
	unsigned int	fork_id;

	fork_array = ft_calloc(amount_philos, sizeof(pthread_mutex_t));
	if (fork_array == NULL)
		return (false);
	fork_id = 0;
	while (fork_id < amount_philos)
	{
		if (pthread_mutex_init(&fork_array[fork_id], NULL) != 0)
			return (destroy_forks(fork_array, fork_id), false);
		fork_id++;
	}
	return (true);
}

/**
 * Initiate mutexes in the data struct
 * @param data Struct with the program data in it
 * @return True if initiation without error. False if there
 * is an error somewhere.
 *  @note Functions location :
 * 'initiate_forks' > same file
 */
static bool	initiate_mutexes_in_data_struct(t_data *data)
{
	if (initiate_forks(data->amount_philosophers, data->forks) == false)
		return (false);
	if (pthread_mutex_init(&data->philo_dead_lock, NULL) != 0)
		return (destroy_mutexes(data, 0), false);
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (destroy_mutexes(data, 1), false);
	if (pthread_mutex_init(&data->thread_init_lock, NULL) != 0)
		return (destroy_mutexes(data, 2), false);
	if (pthread_mutex_init(&data->queue_lock, NULL) != 0)
		return (destroy_mutexes(data, 3), false);
	return (true);
}

/**
 * Converts arguments to unsigned integers. If an input is invalid, an error
 * message will show and then the program will exit.
 * @param argument The argument to be converted
 * @param data Struct with the program data in it
 * @return unsigned int 
 */
static bool	convert_str_to_int(const char *argument, unsigned int *data)
{
	int			i;
	long		number;
	static int	argument_number;

	i = 0;
	number = 0;
	argument_number++;
	while (argument[i])
	{
		if (argument[i] >= '0' && argument[i] <= '9')
			number = (argument[i] - 48) + (number * 10);
		if (argument[i] < '0' || argument[i] > '9'
			|| number > INT_MAX)
		{
			printf("Error: argument %i not valid\n", argument_number);
			return (false);
		}
		i++;
	}
	*data = (unsigned int)number;
	return (true);
}

/**
 * Initialize arguments into the data struct. 
 * @param data Struct with the program data in it
 * @param argument_count Amount of arguments
 * @param argument Arguments inputted on the command line
 * @return t_data struct if arguments are valid. NULL if arguments are 
 * not valid. 
 * @note Functions location :
 * 'an_argument_is_zero' > utils.c
 * 'set_time_to_think' > utils.c;
 * 'convert_str_to_int' > same file
 */
static bool	parse_arguments(t_data *data, int argument_count, char **argument)
{
	if (convert_str_to_int(argument[1], &data->amount_philosophers) == false)
		return (false);
	if (convert_str_to_int(argument[2], &data->time_to_die) == false)
		return (false);
	if (convert_str_to_int(argument[3], &data->time_to_eat) == false)
		return (false);
	if (convert_str_to_int(argument[4], &data->time_to_sleep) == false)
		return (false);
	set_time_to_think(data);
	if (argument_count == 6)
	{
		if (convert_str_to_int(argument[5], &data->eat_limit) == false)
			return (false);
		data->eat_limit_enabled = true;
	}
	if (argument_count != 6)
		data->eat_limit_enabled = false;
	if (an_argument_is_zero(data))
		return (false);
	return (true);
}

/**
 * Initiate data struct
 * @param argument_count Amount of arguments
 * @param argument Arguments inputted on the command line
 * @return t_data struct if arguments are valid. NULL if arguments are 
 * not valid. 
 * @note Functions location :
 * 'parse_arguments' > same file
 * 'initiate_mutexes_in_data_struct' > same file
 */
t_data	*initiate_data_struct(int argument_count, char **argument)
{
	t_data	*data;

	if (argument_count != 5 && argument_count != 6)
		return (printer("Invalid amount of arguments\n", data));
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	if (parse_arguments(data, argument_count, argument) == false)
		return (free(data), NULL);
	if (initiate_mutexes_in_data_struct(data) == false)
		return (free(data), NULL);
	data->philo_dead = false;
	data->exit_program = false;
	data->thread_init_failed = false;
	data->start_time = get_current_time();
	data->print_queue = ft_calloc(data->amount_philosophers * 10, sizeof(char *));
	return (data);
}
