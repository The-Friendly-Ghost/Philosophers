/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_actions.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/14 17:04:43 by cpost         #+#    #+#                 */
/*   Updated: 2022/09/21 12:07:55 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdio.h>

void	print_message(t_philo *philo, t_status status)
{
	unsigned long	time;

	time = get_current_time() - philo->data->start_time;
	if (terminate_thread(philo->data) == false && kill_philo(philo) == false)
	{
		pthread_mutex_lock(&philo->data->write_lock);
		if (status == THINKING)
			printf("%ld %d is thinking\n", time, philo->id);
		else if (status == FORK)
			printf("%ld %d has taken a fork\n", time, philo->id);
		else if (status == SLEEPING)
			printf("%ld %d is sleeping\n", time, philo->id);
		else if (status == EATING)
			printf("%ld %d is eating\n", time, philo->id);
		pthread_mutex_unlock(&philo->data->write_lock);
	}
}

static void	pick_up_forks(t_philo *philo)
{
	if (philo->id != 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, FORK);
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, FORK);
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, FORK);
	}
}

bool	eating(t_philo *philo)
{
	if (terminate_thread(philo->data) == true || kill_philo(philo) == true)
		return (false);
	pick_up_forks(philo);
	print_message(philo, EATING);
	pthread_mutex_lock(&philo->meal_lock);
	philo->x_eaten += 1;
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->meal_lock);
	while (get_current_time() - philo->last_meal < philo->data->time_to_eat)
		usleep(250);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (true);
}

bool	sleeping(t_philo *philo)
{
	long	current_time;

	if (terminate_thread(philo->data) == true || kill_philo(philo) == true)
			return (false);
	print_message(philo, SLEEPING);
	current_time = get_current_time();
	while (get_current_time() - current_time < philo->data->time_to_sleep)
		usleep(250);
	return (true);
}

bool	thinking(t_philo *philo)
{
	long	current_time;

	if (terminate_thread(philo->data) == true || kill_philo(philo) == true)
		return (false);
	print_message(philo, THINKING);
	current_time = get_current_time();
	while (get_current_time() - current_time < philo->data->time_to_think)
		usleep(250);
	return (true);
}
