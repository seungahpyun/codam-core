/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 09:19:46 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/09 10:35:10 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool check_death(t_data *data, int i)
{
	if (get_time() - data->philos[i].last_meal > data->time_to_die)
	{
		pthread_mutex_lock(&data->print_mutex);
		if (!data->someone_died)
		{
			printf("%lld %d died\n", get_time() - data->start_time, i + 1);
			data->someone_died = true;
		}
		pthread_mutex_unlock(&data->print_mutex);
		return (true);
	}
	return (false);
}

bool	check_meal(t_data *data)
{
	int	i;
	int	finished;

	if (data->must_eat == -1)
		return (false);
	finished = 0;
	i = 0;
	while (i < data->num_philos)
	{
		if (data->philos[i].meals_eaten >= data->must_eat)
			finished++;
		i++;
	}
	return (finished == data->num_philos);
}

void	monitoring (t_data *data)
{
	int i;

	while (!data->someone_died)
	{
		i = 0;
		while (i < data->num_philos && !data->someone_died)
		{
			if (check_death(data, i))
				break ;
			if (check_meal(data))
			{
				data->someone_died = true;
				break ;
			}
			i++;
		}
		if (data->someone_died)
			break ;
		usleep(1000);
	}
}
