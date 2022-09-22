/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/11 13:47:53 by cpost         #+#    #+#                 */
/*   Updated: 2022/09/22 11:28:44 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * The first function that a philo thread starts. Basically, this
 * is the main function of a philo thread.
 * @param philo_struct A (void) pointer to the philo struct for this
 * philosopher.
 * @return Nothing
 */
bool	join_threads(pthread_t *threads, t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->amount_philosophers)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (false);
		i++;
	}
	return (true);
}

/**
 * Main
 * @param argument_count Amount of arguments
 * @param arguments Arguments inputted on the command line
 * @return SUCCESS if program succesfully ends. FAILURE if there's an
 * error somewhere. 
 * @note Functions location :
 * 'initiate_data_struct' > initiate_data_struct.c
 * 'initiate_philo_struct' > initiate_philo_struct.c
 * 'initiate_threads' > initiate_threads.c
 */
int	main(int argument_count, char **arguments)
{
	t_data		*data;
	t_philo		*philo;
	pthread_t	*threads;

	philo = NULL;
	threads = NULL;
	data = initiate_data_struct(argument_count, arguments);
	if (data == NULL)
		return (FAILURE);
	philo = initiate_philo_struct(data);
	if (philo == NULL)
		return (destroy_all(data, philo), FAILURE);
	threads = initiate_threads(philo, data);
	if (threads == NULL)
		return (destroy_all(data, philo), FAILURE);
	monitor_shit(data, philo, 0, 0);
	if (join_threads(threads, data) == false)
		return (destroy_all(data, philo), FAILURE);
	return (free(threads), destroy_all(data, philo), SUCCES);
}
