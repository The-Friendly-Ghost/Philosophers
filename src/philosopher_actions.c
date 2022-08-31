/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_actions.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/14 17:04:43 by cpost         #+#    #+#                 */
/*   Updated: 2022/08/31 15:15:22 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdio.h>

void	eat(t_philo *philo)
{

}

void	sleep(t_philo *philo)
{
	long	sleep_start_time;
	long	program_time_elapsed;

	if (terminate_thread_conditions(philo) == true)
		return ;
	sleep_start_time = get_current_time();
	program_time_elapsed = sleep_start_time - philo->data->start_time;
	pthread_mutex_lock(&philo->data->write_lock);
	printf("%010ld - Philo %d is sleeping\n", program_time_elapsed, philo->id);
	pthread_mutex_unlock(&philo->data->write_lock);
	while (get_current_time() - sleep_start_time < philo->data->time_to_sleep)
	{
		if (terminate_thread_conditions(philo) == true)
			return ;
	}
}

void	rave(t_philo *philo)
{
	long	time;

	if (terminate_thread_conditions(philo) == true)
		return ;
	time = get_current_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->write_lock);
	printf("%010ld - Philo %d is raving\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->write_lock);
}

/**
 * Just for the pun.
 */
void	repeat(void)
{
	return ;
}
