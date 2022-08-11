/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/11 13:47:53 by cpost         #+#    #+#                 */
/*   Updated: 2022/08/11 17:39:42 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h> 

void	leaks_func(void)
{
	system("leaks -q philo");
}

/**
 * Main
 * @param argument_count Amount of arguments
 * @param arguments Arguments inputted on the command line
 * @return SUCCESS if program succesfully ends. FAILURE if there's an
 * error somewhere. 
 * @note Functions location :
 * 'initiate_data_struct' > initiate_data_struct.c
 * 'initiate_philo_struct' > initiate_philo_struct.c
 * 'initiate_philo_threads' > initiate_philo_threads.c
 */
int	main(int argument_count, char **arguments)
{
	t_data	*data;
	t_philo	*philo;

	//atexit(leaks_func);
	philo = NULL;
	data = initiate_data_struct(argument_count, arguments);
	if (data == NULL)
		return (FAILURE);
	philo = initiate_philo_struct(data);
	if (philo == NULL)
		return (FAILURE); //todo: destroy data and mutexes in it
	if (initiate_philo_threads(philo, data) == false)
		return (FAILURE); //todo: destroy data, philo and mutexes
	free(data);
	return (SUCCES);
}
