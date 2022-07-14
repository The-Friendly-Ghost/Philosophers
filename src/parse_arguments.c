/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_arguments.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/12 12:20:19 by cpost         #+#    #+#                 */
/*   Updated: 2022/07/14 12:29:47 by cpost         ########   odam.nl         */
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
static unsigned int	ft_atoi(const char *argument, t_start *start)
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
			if (start)
				free(start);
			printf("Input not valid\n");
			exit (1);
		}
		i++;
	}
	return ((unsigned int)number);
}

/**
 * Parses the arguments from the command line and (if valid) stores them
 * inside of a struct (t_start).
 * @param argument_count Amount of arguments
 * @param argument Arguments inputted on the command line
 * @return t_start struct if arguments are valid. NULL if arguments are 
 * not valid. 
 */
t_start	*parse_arguments(int argument_count, char **argument)
{
	t_start	*start;

	if (argument_count != 5 && argument_count != 6)
		return (NULL);
	start = malloc(sizeof(t_start));
	if (start == NULL)
		return (NULL);
	start->amount_philosophers = ft_atoi(argument[1], start);
	start->time_to_die = ft_atoi(argument[2], start);
	start->time_to_eat = ft_atoi(argument[3], start);
	start->time_to_sleep = ft_atoi(argument[4], start);
	if (argument_count == 6)
		start->x_times_to_eat = ft_atoi(argument[5], start);
	else
		start->x_times_to_eat = -1;
	return (start);
}
