/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 10:36:58 by cpost         #+#    #+#                 */
/*   Updated: 2022/09/15 11:59:50 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Checker function that checks if all threads were successfully
 * initiated. 
 * @param data A (void) pointer to the data struct.
 * @return true if thread init failed. False if all threads were
 * succesfully created.
 */
bool	thread_init_success(t_data *data)
{
	pthread_mutex_lock(&data->thread_init_lock);
	if (data->thread_init_failed == true)
	{
		pthread_mutex_unlock(&data->thread_init_lock);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&data->thread_init_lock);
		return (false);
	}
}

/**
 * Checker function that checks if the progam should stop running. 
 * @param data A (void) pointer to the data struct.
 * @return true if program has to stop. Else false.
 */
bool	terminate_thread(t_data *data)
{
	phthread_mutex_lock(&data->philo_dead_lock);
	if (data->philo_dead == true || data->exit_program == true)
	{
		phthread_mutex_unlock(&data->philo_dead_lock);
		return (true);
	}
	else
	{
		phthread_mutex_unlock(&data->philo_dead_lock);
		return (false);
	}
}

/**
 * Checker function that checks if the current philo should be dying. 
 * @param philo A (void) pointer to the philo struct.
 * @return true if philo should die. Else false.
 */
bool	kill_philo(t_philo *philo)
{
	long	current_time;
	long	elapsed_time;

	current_time = get_current_time();
	pthread_mutex_lock(&data->philo_dead_lock);
	if (philo->last_meal - current_time > data->time_to_die
		&& philo->data->philo_dead == false)
	{
		philo->data->philo_dead = true;
		pthread_mutex_unlock(&data->philo_dead_lock);
		elapsed_time = current_time - philo->data->start_time;
		pthread_mutex_lock(&data->write_lock);
		printf("%010ld - Philo %d has died\n", elapsed_time, philo->id);
		pthread_mutex_unlock(&data->write_lock);
		return (true);
	}
	pthread_mutex_unlock(&data->philo_dead_lock);
	return (false);
}
