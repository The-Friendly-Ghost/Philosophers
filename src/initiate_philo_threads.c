/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initiate_philo_threads.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: casper <cpost@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 10:06:34 by casper        #+#    #+#                 */
/*   Updated: 2022/08/11 17:33:55 by casper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	initiate_philo_threads(t_philo *philo, t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->amount_philosophers)
	{
		if (pthread_create(&data->thread[i], NULL, run_philosopher, 
			&philo[i]) != 0)
			return (false); // DELETE ALL DATA IF FALSE
		i++;
	}
	return (true);
}