/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 10:36:58 by cpost         #+#    #+#                 */
/*   Updated: 2022/09/23 17:03:44 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Checker function that checks if all threads were successfully
 * initiated. 
 * @param data A pointer to the data struct.
 * @return true if thread init failed. False if all threads were
 * succesfully created.
 */
bool	thread_init_success(t_data *data)
{
	pthread_mutex_lock(&data->thread_init_lock);
	if (data->thread_init_failed == true)
	{
		pthread_mutex_unlock(&data->thread_init_lock);
		return (false);
	}
	pthread_mutex_unlock(&data->thread_init_lock);
	return (true);
}

/**
 * Checker function that checks if the progam should stop running. 
 * @param data A pointer to the data struct.
 * @return true if program has to stop. Else false.
 */
bool	terminate_thread(t_data *data)
{
	pthread_mutex_lock(&data->philo_dead_lock);
	if (data->philo_dead == true)
	{
		pthread_mutex_unlock(&data->philo_dead_lock);
		return (true);
	}
	pthread_mutex_unlock(&data->philo_dead_lock);
	return (false);
}

/**
 * Checker function that checks if the current philo should be dying. 
 * @param philo A pointer to the philo struct.
 * @return true if philo should die. Else false.
 */
bool	kill_philo(t_philo *philo)
{
	unsigned long	elapsed_time;

	pthread_mutex_lock(&philo->meal_lock);
	pthread_mutex_lock(&philo->data->philo_dead_lock);
	if (get_current_time() - philo->last_meal >= philo->data->time_to_die
		&& philo->data->philo_dead == false)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		philo->data->philo_dead = true;
		pthread_mutex_unlock(&philo->data->philo_dead_lock);
		elapsed_time = get_current_time() - philo->data->start_time;
		usleep(200);
		printf("%ld %d died\n", elapsed_time, philo->id);
		return (true);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_unlock(&philo->data->philo_dead_lock);
	return (false);
}

/**
 * Checks if a specific philosopher ate 
 * @param philo A pointer to the philo struct.
 * @return True if philo ate enough. Else false.
 */
bool	philo_ate_enough(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (philo->x_eaten >= data->eat_limit)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&philo->meal_lock);
		return (false);
	}
}

/**
 * Function that keeps on looping while the threads are running. If a
 * philosopher dies or all philosophers have eaten, the while loop ends.
 * @param data A pointer to the data struct.
 * @param philo A pointer to the philo struct.
 * @return Nothing
 */
void	monitor_shit(t_data *data, t_philo *philo, unsigned int finished,
	unsigned int i)
{
	while (terminate_thread(data) == false)
	{
		i = 0;
		finished = 0;
		while (i < data->amount_philosophers)
		{
			if (data->eat_limit_enabled == true
				&& philo_ate_enough(data, &philo[i]) == true)
				finished++;
			if (kill_philo(&philo[i]) == true)
				return ;
			i++;
		}
		if (finished == data->amount_philosophers)
		{
			pthread_mutex_lock(&philo->data->philo_dead_lock);
			data->philo_dead = true;
			pthread_mutex_unlock(&philo->data->philo_dead_lock);
			return ;
		}
	}
	usleep(200);
}
