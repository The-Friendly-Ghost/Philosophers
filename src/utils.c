/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: casper <casper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/07 17:19:19 by casper        #+#    #+#                 */
/*   Updated: 2022/08/07 17:19:20 by casper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

/**
 * Checks if any of the arguments in the data struct is 0
 * @param data Struct with the program data in it
 * @return True if one of the arguments is 0. False if no 0 is found.
 */
bool	an_argument_is_zero(t_data *data)
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