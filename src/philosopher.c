/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: casper <cpost@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 10:57:39 by casper        #+#    #+#                 */
/*   Updated: 2022/08/31 12:51:00 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdio.h>

static bool	not_all_threads_were_succesfully_initiated(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->thread_init_lock);
	if (philo->data->thread_init_failed == true)
	{
		pthread_mutex_unlock(&philo->data->thread_init_lock);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->thread_init_lock);
		return (false);
	}
}

void	*run_philosopher(void *philo_struct)
{
	t_philo	*philo;

	philo = philo_struct;
	if (not_all_threads_were_succesfully_initiated(philo) == true)
	{
		printf("Thread initiation failed\n");
		return (NULL);
	}
	while (thread_terminate_conditions_are_not_met(philo) == true)
	{
		eat(philo);
		sleep(philo);
		rave(philo);
		repeat();
	}
	return (NULL);
}
