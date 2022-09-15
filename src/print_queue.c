/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_queue.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpost <cpost@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:03:35 by cpost         #+#    #+#                 */
/*   Updated: 2022/09/15 11:05:23 by cpost         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * The strdup() function returns a pointer to a new string which is 
 * a duplicate of the string s.  Memory for the new string is 
 * obtained with malloc(3), and can be freed with free(3).
 * @param s The string that has to be copied
 * @return On success, the strdup() function returns a pointer to the 
 * duplicated string.  It returns NULL if insufficient memory was 
 * available.
 */
static char	*ft_strdup(const char *s)
{
	char	*x;
	int		i;

	i = 0;
	x = malloc(ft_strlen((char *)s) + 1);
	if (!x)
		return (NULL);
	while (s[i])
	{
		x[i] = s[i];
		i++;
	}
	x[i] = 0;
	return (x);
}

/**
 * Initiates array of mutexes (each mutex is a fork). For every philosopher,
 * one fork mutex is initiated.
 * @param data Struct with the program data in it
 * @return True if initiation without error. False if there
 * is an error somewhere.
 */
void	add_to_print_queue(char *new_str, t_data *data)
{
	static unsigned int	i;
	unsigned int		size;
	char				*print_str;

	size = data->amount_philosophers * 10;
	print_str = ft_strdup(new_str);
	pthread_mutex_lock(&data->queue_lock);
	if (i >= size)
		i = 0;
	data->print_queue[i] = print_str;
	i++;
	pthread_mutex_unlock(&data->queue_lock);
}

/**
 * Prints a string and returns NULL
 * @param str The string to print
 * @return NULL
 */
char	*printer(char *str, t_data *data)
{
	pthread_mutex_lock(&data->write_lock);
	printf("%s\n", str);
	pthread_mutex_unlock(&data->write_lock);
	return (NULL);
}

/**
 * Checks if there's a new message to be printed. If so, runs the printer
 * function. If there are no more messages and a philo has died or philo's are
 * done eating, end the function.
 * @param data Struct with the program data in it
 * @return True if initiation without error. False if there
 * is an error somewhere.
 */
void	*run_printer(t_data *data)
{
	static unsigned int	i;
	unsigned int		size;

	if (thread_init_success(data) == false)
	{
		printf("Thread initiation failed\n");
		return (NULL);
	}
	size = data->amount_philosophers * 10;
	while (1)
	{
		if (i >= size)
			i = 0;
		while (!data->print_queue[i])
		{
			if (terminate_thread(data) == true)
				break ;
			usleep(100);
		}
		printer(data->print_queue[i], data);
		free(data->print_queue[i]);
		data->print_queue[i] = NULL;
		i++;
	}
	free(data->print_queue);
	return (NULL);
}
