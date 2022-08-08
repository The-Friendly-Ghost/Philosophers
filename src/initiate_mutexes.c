/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initiate_mutexes.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: casper <casper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/07 17:19:35 by casper        #+#    #+#                 */
/*   Updated: 2022/08/07 17:19:36 by casper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Initiate mutexes in the data struct
 * @param data Struct with the program data in it
 * @return nothing 
 */
void	*initiate_data_struct(int argument_count, char **argument)
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
	if (parse_arguments(data, argument_count, argument) == false)
	{
		free(data);
		return (NULL);
	}
	return (data);
}
