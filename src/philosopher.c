/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: casper <cpost@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 10:57:39 by casper        #+#    #+#                 */
/*   Updated: 2022/08/14 20:46:19 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdio.h>

static bool	all_threads_were_succesfully_initiated(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->thread_init_failed_lock);
	if (philo->data->thread_init_failed == true)
	{
		pthread_mutex_unlock(&philo->data->thread_init_failed_lock);
		return (false);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->thread_init_failed_lock);
		return (true);
	}
}

void	*run_philosopher(void *philo_struct)
{
	t_philo	*philo;

	philo = philo_struct;
	if (all_threads_were_succesfully_initiated(philo) == false)
	{
		printf("Thread initiation failed\n");
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(250);
	while (terminate_thread_conditions(philo) == false)
	{
		eat(philo);
		sleep(philo);
		rave(philo);
		repeat();
	}
	return (NULL);
}