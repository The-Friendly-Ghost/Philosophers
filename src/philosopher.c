/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: casper <cpost@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 10:57:39 by casper        #+#    #+#                 */
/*   Updated: 2022/09/15 12:34:46 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdio.h>

/**
 * The first function that a philo thread starts. Basically, this
 * is the main function of a philo thread.
 * @param philo_struct A (void) pointer to the philo struct for this
 * philosopher.
 * @return Nothing
 */
void	*run_philosopher(void *philo_struct)
{
	t_philo	*philo;

	philo = philo_struct;
	if (thread_init_success(philo->data) == false)
	{
		printf("Thread initiation failed\n");
		return (NULL);
	}
	pthread_mutex_lock(&philo->data->write_lock);
	printf("%010ld - Philo %d is thinking\n", 0, philo->id);
	pthread_mutex_unlock(&philo->data->write_lock);
	while (terminate_thread(philo->data) == false)
	{
		if (eating(philo) == false)
			break ;
		if (sleeping(philo) == false)
			break ;
		if (thinking(philo) == false)
			break ;
	}
	return (NULL);
}
