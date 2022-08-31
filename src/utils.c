/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: casper <cpost@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/07 17:19:19 by casper        #+#    #+#                 */
/*   Updated: 2022/08/31 15:10:53 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>
#include <stdio.h>

/**
 * If the amount of philosophers is odd, then the time to eat must fit
 * at least 2 times in to time_to_sleep + time_to_think. This is to
 * prevent a philosopher from getting to eat two times in a row while 
 * the philosopher next to him hasn't eaten yet.
 * @param data Struct with the program data in it
 * @return nothing
 */
void	set_time_to_think(t_data *data)
{
	if (data->amount_philosophers % 2 == 1 && (data->time_to_eat * 2)
		> data->time_to_sleep)
		data->time_to_think = (data->time_to_eat * 2) - data->time_to_sleep;
	else
		data->time_to_think = 0;
}

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
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*x;

	x = s;
	while (n > 0)
	{
		*x = 0;
		x++;
		n--;
	}
	return (s);
}

/**
 * @brief Create a new array and fill the entire array with 0 (using ft_bzero)
 * @param nmemb The amount of elements to be created
 * @param size The size of each element
 * @return void * - Address to array filled with 0's
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (ptr)
		ft_bzero(ptr, (nmemb * size));
	return (ptr);
}
