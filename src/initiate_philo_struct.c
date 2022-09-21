/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initiate_philo_struct.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: casper <cpost@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/07 17:19:35 by casper        #+#    #+#                 */
/*   Updated: 2022/09/21 17:18:45 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Initiate mutexes in the data struct
 * @param data Struct with the program data in it
 * @return nothing 
 */
t_philo	*initiate_philo_struct(t_data *data)
{
	t_philo			*philo;
	unsigned int	i;

	philo = ft_calloc(data->amount_philosophers, sizeof(t_philo));
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
		if (pthread_mutex_init(&philo[i].meal_lock, NULL) != 0)
			return (destroy_meal_lock(philo, i + 1), free(philo), NULL);
		i++;
	}
	return (philo);
}
