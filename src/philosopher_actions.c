/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_actions.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/14 17:04:43 by cpost         #+#    #+#                 */
/*   Updated: 2022/09/15 12:56:40 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdio.h>

static void	print_message(t_philo *philo, t_status status)
{
	long	time;

	time = get_current_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->write_lock);
	if (status == RIGHT_FORK)
		printf("%010ld - Philo %d picked up right fork\n", time, philo->id);
	else if (status == LEFT_FORK)
		printf("%010ld - Philo %d picked up left fork\n", time, philo->id);
	else if (status == SLEEPING)
		printf("%010ld - Philo %d is sleeping\n", time, philo->id);
	else if (status == EATING)
		printf("%010ld - Philo %d is eating\n", time, philo->id);
	else if (status == THINKING)
		printf("%010ld - Philo %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->write_lock);
}

static bool pick_up_forks(t_philo *philo)
{
	if (philo->id != 1)
	{
		pthread_mutex_lock(&philo->right_fork);
		print_message(philo, RIGHT_FORK);
		pthread_mutex_lock(&philo->left_fork);
		print_message(philo, LEFT_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork);
		print_message(philo, LEFT_FORK);
		pthread_mutex_lock(&philo->right_fork);
		print_message(philo, RIGHT_FORK);
	}
}

bool	eating(t_philo *philo)
{
	long	current_time;
	long	elapsed_time;

	if (terminate_thread(philo->data) == true || kill_philo(philo) == true)
		return (false);
	pick_up_forks(philo);
	philo->last_meal = get_current_time;
	philo->x_eaten += 1;
	print_message(philo, EATING);
	while (get_current_time() - philo->last_meal < philo->data->time_to_eat)
	{
		if (terminate_thread(philo->data) == true || kill_philo(philo) == true)
		{
			pthread_mutex_unlock(&philo->left_fork);
			pthread_mutex_unlock(&philo->right_fork);
			return (false);
	}
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	return (true);
}

bool	sleeping(t_philo *philo)
{
	long	current_time;
	long	elapsed_time;

	if (terminate_thread(philo->data) == true || kill_philo(philo) == true)
		return (false);
	current_time = get_current_time();
	elapsed_time = current_time - philo->data->start_time;
	print_message(philo, SLEEPING);
	while (get_current_time() - current_time < philo->data->time_to_sleep)
	{
		if (terminate_thread(philo->data) == true || kill_philo(philo) == true)
			return (false);
	}
	return (true);
}

bool	thinking(t_philo *philo)
{
	long	current_time;
	long	elapsed_time;

	if (terminate_thread(philo->data) == true || kill_philo(philo) == true)
		return ;
	current_time = get_current_time();
	elapsed_time = current_time - philo->data->start_time;
	print_message(philo, THINKING);
	while (get_current_time() - current_time < philo->data->time_to_think)
	{
		if (terminate_thread(philo->data) == true || kill_philo(philo) == true)
			return (false);
	}
}
