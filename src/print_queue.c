/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_queue.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:03:35 by cpost         #+#    #+#                 */
/*   Updated: 2022/08/31 15:15:37 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Initiates array of mutexes (each mutex is a fork). For every philosopher,
 * one fork mutex is initiated.
 * @param data Struct with the program data in it
 * @return True if initiation without error. False if there
 * is an error somewhere.
 */
void	add_to_print_queue(char *new_str)
{
	static unsigned int	i;

	i = 0;
}
