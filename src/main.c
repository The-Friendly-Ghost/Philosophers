/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/11 13:47:53 by cpost         #+#    #+#                 */
/*   Updated: 2022/08/09 18:39:27 by casper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h> 

void	leaks_func(void)
{
	system("leaks philo");
}

/**
 * Main
 * @param argument_count Amount of arguments
 * @param arguments Arguments inputted on the command line
 * @return SUCCESS if program succesfully ends. FAILURE if there's an
 * error somewhere. 
 * @note Functions location :
 * 'initiate_data_struct' > initiate_data_struct.c
 */
int	main(int argument_count, char **arguments)
{
	t_data	*data;
	t_philo	*philos;

	//atexit(leaks_func);
	philos = NULL;
	data = initiate_data_struct(argument_count, arguments);
	if (data == NULL)
		return (FAILURE);
	philos = initiate_philo_struct(data);
	if (philos == NULL)
		return (FAILURE); //todo: destroy data and mutexes in it
	free(data);
	return (SUCCES);
}
