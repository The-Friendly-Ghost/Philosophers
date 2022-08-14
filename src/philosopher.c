/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: casper <cpost@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 10:57:39 by casper        #+#    #+#                 */
/*   Updated: 2022/08/14 20:56:34 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdio.h>

static bool	not_all_threads_were_succesfully_initiated(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->thread_init_failed_lock);
	if (philo->data->thread_init_failed == true)
	{
		pthread_mutex_unlock(&philo->data->thread_init_failed_lock);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->thread_init_failed_lock);
		return (false);
	}
}

void	*run_philosopher(void *philo_struct)
{
	t_philo	*philo;

	philo = philo_struct;
	if (not_all_threads_were_succesfully_initiated(philo))
	{
		printf("Thread initiation failed\n");
		return (NULL);
	}
	if (philo_id_is_an_odd_number)
		usleep(250);
	while (thread_terminate_conditions_are_not_met(philo))
	{
		eat(philo);
		sleep(philo);
		rave(philo);
		repeat();
	}
	return (NULL);
}