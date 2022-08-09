/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: casper <casper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/07 17:19:19 by casper        #+#    #+#                 */
/*   Updated: 2022/08/09 18:50:58 by casper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <sys/time.h>
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

/**
 * Gets the current time (in microseconds)
 * @return The time
 */
long	get_current_time(void)
{
	struct timeval	time;
	
	if (gettimeofday(&time, NULL) != 0)
		return (0); // Change this. If gettimeofday doesn't return 0, delete
					// structs and exit program
	return(time.tv_sec * 1000 + time.tv_usec / 1000);
}
