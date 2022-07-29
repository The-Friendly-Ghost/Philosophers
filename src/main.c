/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/11 13:47:53 by cpost         #+#    #+#                 */
/*   Updated: 2022/07/29 14:57:24 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h> 

void	leaks_func(void)
{
	system("leaks Philosophers");
}

int	main(int argument_count, char **argument)
{
	t_data	*data;
	t_philo	*philos;

	//atexit(leaks_func);
	data = parse_arguments(argument_count, argument);
	if (data == NULL)
		return (FAILURE);
	philos = init_philos(data);
	if (philos = NULL)
		return (FAILURE);
	free(data);
	return (SUCCES);
}
