/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initiate_philos.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: casper <casper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/07 17:19:35 by casper        #+#    #+#                 */
/*   Updated: 2022/08/09 19:00:09 by casper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Initiate mutexes in the data struct
 * @param data Struct with the program data in it
 * @return nothing 
 */
t_philo	*initiate_philo_struct(t_data *data)
{
	t_philo			*philo;
	unsigned int	i;

	philo = calloc(data->amount_philosophers, sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	i = 0;
	while (i < data->amount_philosophers)
	{
		philo[i].id = i + 1;
		philo[i].x_eaten = 0;
		philo[i].data = data;
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->amount_philosophers];
		philo[i].last_meal = get_current_time();
		i++;
	}
	return (philo);
}
