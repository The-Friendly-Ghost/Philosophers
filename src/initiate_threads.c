/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initiate_threads.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: casper <cpost@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 10:06:34 by casper        #+#    #+#                 */
/*   Updated: 2022/09/19 15:48:22 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Initiates a thread (philo) for every philosopher
 * @param philo A pointer to an array of philo structs
 * @param data A pointer to the data struct
 * @return true if all threads where successfully created. false
 * if thread creation failed. 
 * @note
 */
pthread_t	*initiate_threads(t_philo *philo, t_data *data)
{
	unsigned int	i;
	pthread_t		*thread;

	i = 0;
	thread = malloc(sizeof(pthread_t) * data->amount_philosophers);
	pthread_mutex_lock(&data->thread_init_lock);
	while (i < data->amount_philosophers)
	{
		if (pthread_create(&thread[i], NULL, run_philosopher,
				&philo[i]) != 0)
		{
			data->thread_init_failed = true;
			pthread_mutex_unlock(&data->thread_init_lock);
			return (NULL);
		}
		i++;
	}
	// if (pthread_create(&data->thread[i], NULL, run_printer, &data) != 0)
	// {
	// 	data->thread_init_failed = true;
	// 	pthread_mutex_unlock(&data->thread_init_lock);
	// 	return (false);
	// }
	pthread_mutex_unlock(&data->thread_init_lock);
	return (thread);
}
