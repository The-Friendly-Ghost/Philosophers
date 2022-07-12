/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/11 13:47:53 by cpost         #+#    #+#                 */
/*   Updated: 2022/07/12 16:06:15 by cpost         ########   odam.nl         */
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
	t_start	*start;

	//atexit(leaks_func);
	start = parse_arguments(argument_count, argument);
	if (start == NULL)
		return (1);
	free(start);
	return (0);
}
