/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initiate_philo_threads.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: casper <cpost@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 10:06:34 by casper        #+#    #+#                 */
/*   Updated: 2022/08/29 12:24:43 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Initiates a thread (philo) for every philosopher
 * @param philo A pointer to an array of philo structs
 * @param data A pointer to the data struct
 * @return SUCCESS if program succesfully ends. FAILURE if there's an
 * error somewhere. 
 * @note Functions location :
 * 'initiate_data_struct' > initiate_data_struct.c
 * 'initiate_philo_struct' > initiate_philo_struct.c
 * 'initiate_philo_threads' > initiate_philo_threads.c
 */
bool	initiate_philo_threads(t_philo *philo, t_data *data)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_lock(&data->thread_init_lock);
	while (i < data->amount_philosophers)
	{
		if (pthread_create(&data->thread[i], NULL, run_philosopher, 
			&philo[i]) != 0)
			{
				data->thread_init_failed = true;
				pthread_mutex_unlock(&data->thread_init_lock);
				return (false); // DELETE ALL DATA IF FALSE
			}
		i++;
	}
	pthread_mutex_unlock(&data->thread_init_lock);
	return (true);
}