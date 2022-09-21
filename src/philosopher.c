/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: casper <cpost@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 10:57:39 by casper        #+#    #+#                 */
/*   Updated: 2022/09/21 12:03:30 by cpost         ########   odam.nl         */
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
static void	run_one_philo(t_philo *philo)
{
	long	time;

	printf("%ld %d has taken a fork\n", (long)0, philo->id);
	usleep(philo->data->time_to_die * 1000);
	time = get_current_time() - philo->data->start_time;
	printf("%ld %d died\n", time, philo->id);
	pthread_mutex_lock(&philo->data->philo_dead_lock);
	philo->data->philo_dead = true;
	pthread_mutex_unlock(&philo->data->philo_dead_lock);
}

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
	if (philo->data->amount_philosophers == 1)
		return (run_one_philo(philo), NULL);
	print_message(philo, THINKING);
	if (philo->id % 2 == 0)
		usleep(300);
	while (1)
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
