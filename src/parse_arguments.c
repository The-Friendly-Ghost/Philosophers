/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_arguments.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/12 12:20:19 by cpost         #+#    #+#                 */
/*   Updated: 2022/07/29 14:55:36 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>

/**
 * Converts arguments to unsigned integers. If an input is invalid, an error
 * message will show and then the program will exit.
 * @param argument The argument to be converted
 * @return unsigned int 
 */
static unsigned int	check_valid_input(t_data *data)
{
	if (data->amount_philosophers == 0 || data->time_to_die == 0
		|| data->time_to_eat == 0 || data->time_to_sleep == 0
		|| data->x_times_to_eat == 0)
		return (INPUT_NOT_VALID);
	else
		return (INPUT_VALID);
}

/**
 * Converts arguments to unsigned integers. If an input is invalid, an error
 * message will show and then the program will exit.
 * @param argument The argument to be converted
 * @return unsigned int 
 */
static unsigned int	ft_atoi(const char *argument, t_data *data)
{
	int			i;
	long		number;

	i = 0;
	number = 0;
	while (argument[i])
	{
		if (argument[i] >= '0' && argument[i] <= '9')
			number = (argument[i] - 48) + (number * 10);
		if (argument[i] < '0' || argument[i] > '9'
			|| number > INT_MAX)
		{
			if (data)
				free(data);
			printf("Input not valid\n");
			exit (INPUT_NOT_VALID);
		}
		i++;
	}
	return ((unsigned int)number);
}

/**
 * Parses the arguments from the command line and (if valid) stores them
 * inside of a struct (t_data).
 * @param argument_count Amount of arguments
 * @param argument Arguments inputted on the command line
 * @return t_data struct if arguments are valid. NULL if arguments are 
 * not valid. 
 */
t_data	*parse_arguments(int argument_count, char **argument)
{
	t_data	*data;

	if (argument_count != 5 && argument_count != 6)
	{
		printf("Input five or six arguments\n");
		return (NULL);
	}
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->amount_philosophers = ft_atoi(argument[1], data);
	data->time_to_die = ft_atoi(argument[2], data);
	data->time_to_eat = ft_atoi(argument[3], data);
	data->time_to_sleep = ft_atoi(argument[4], data);
	if (argument_count == 6)
		data->x_times_to_eat = ft_atoi(argument[5], data);
	else
		data->x_times_to_eat = -1;
	if (check_valid_input(data) == INPUT_NOT_VALID)
	{
		free(data);
		printf("Input not valid\n");
		return (NULL);
	}
	return (data);
}
