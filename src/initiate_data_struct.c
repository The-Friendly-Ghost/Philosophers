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
 * Checks if any of the arguments is 0
 * @param data Struct with the program data in it
 * @return unsigned int 
 */
static bool	an_argument_is_zero(t_data *data)
{
	if (data->amount_philosophers == 0 || data->time_to_die == 0
		|| data->time_to_eat == 0 || data->time_to_sleep == 0
		|| (data->eat_limit == 0 && data->eat_limit_enabled == true))
		{
			printf("Error: arguments can not be 0 or less\n");
			return (true);
		}
	else
		return (false);
}

/**
 * Converts arguments to unsigned integers. If an input is invalid, an error
 * message will show and then the program will exit.
 * @param argument The argument to be converted
 * @param data Struct with the program data in it
 * @return unsigned int 
 */
static bool	str_to_int(const char *argument, unsigned int *data)
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
			return(false);
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
 */
static bool	parse_arguments(t_data *data, int argument_count, char **argument)
{
	if (str_to_int(argument[1], &data->amount_philosophers) == false)
		return (false);
	if (str_to_int(argument[2], &data->time_to_die) == false)
		return (false);
	if (str_to_int(argument[3], &data->time_to_eat) == false)
		return (false);
	if (str_to_int(argument[4], &data->time_to_sleep) == false)
		return (false);
	if (argument_count == 6)
	{
		if (str_to_int(argument[5], &data->eat_limit) == false)
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
 */
t_data	*initiate_data_struct(int argument_count, char **argument)
{
	t_data	*data;

	if (argument_count != 5 && argument_count != 6)
	{
		printf("Invalid amount of arguments\n");
		return (NULL);
	}
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	if (parse_arguments(data, argument_count, argument) == FAILURE)
	{
		free(data);
		return (NULL);
	}
	return (data);
}
