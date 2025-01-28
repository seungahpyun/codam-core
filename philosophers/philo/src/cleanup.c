/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 09:28:15 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/10 11:04:18 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup(t_data *data)
{
	int	i;

	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	if (data->forks)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->death_mutex);
}

int	error_msg(char *msg)
{
	printf("%s\n", msg);
	return (EXIT_FAILURE);
}

int	error_cleanup(char *msg, t_data *data)
{
	printf("%s\n", msg);
	cleanup(data);
	return (EXIT_FAILURE);
}
