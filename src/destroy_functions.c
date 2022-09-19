/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   destroy_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 13:29:26 by cpost         #+#    #+#                 */
/*   Updated: 2022/09/19 14:51:41 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

/**
 * Destroys all the created meal mutexes.
 * @param philo Struct with all the philo's in it
 * @param created Amount of philo's created
 * @return Nothing
 */
void	destroy_meal_lock(t_philo *philo, unsigned int created)
{
	unsigned int	i;

	i = 0;
	while (i < created)
	{
		pthread_mutex_destroy(&philo[i].meal_lock);
		i++;
	}
}

/**
 * Destroys all the created fork mutexes.
 * @param fork_array The array with all the fork mutexes in it
 * @param created_forks The amount of forks in the fork_array.
 * @return Nothing
 */
void	destroy_forks(pthread_mutex_t *fork_array, unsigned int created_forks)
{
	unsigned int	i;

	i = 0;
	while (i < created_forks)
	{
		pthread_mutex_destroy(&fork_array[i]);
		i++;
	}
}

/**
 * Destroys all the created mutexes
 * @param data Struct with all the created mutexes in it.
 * @param mutexes_created Amount of mutexes created
 * @return Nothing
 */
void	destroy_mutexes(t_data *data, unsigned int mutexes_created)
{
	if (mutexes_created > 0)
		pthread_mutex_destroy(&data->philo_dead_lock);
	if (mutexes_created > 1)
		pthread_mutex_destroy(&data->write_lock);
	if (mutexes_created > 2)
		pthread_mutex_destroy(&data->thread_init_lock);
	// if (mutexes_created > 3)
	// 	pthread_mutex_destroy(&data->queue_lock);
	destroy_forks(data->forks, data->amount_philosophers);
}

/**
 * Destroys all the program data
 * @param data Struct with all the created mutexes in it.
 * @param philo Struct with all the philo's in it
 * @return Nothing
 */
void	destroy_all(t_data *data, t_philo *philo)
{
	if (data != NULL)
		destroy_mutexes(data, 99);
	if (philo != NULL)
		destroy_meal_lock(philo, data->amount_philosophers);
	if (data != NULL)
		free(data);
	if (philo != NULL)
		free(philo);
}
