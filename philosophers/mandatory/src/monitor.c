/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 09:19:46 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/10 14:52:40 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	check_death(t_data *data, int i)
{
	time_t	current_time;
	time_t	last_meal_time;

	pthread_mutex_lock(&data->meal_mutex);
	current_time = get_time();
	last_meal_time = data->philos[i].last_meal;
	pthread_mutex_unlock(&data->meal_mutex);
	if (current_time - last_meal_time > data->time_to_die)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (!data->someone_died)
		{
			printf("%ld %d died\n", current_time - data->start_time, i + 1);
			data->someone_died = true;
		}
		pthread_mutex_unlock(&data->death_mutex);
		return (true);
	}
	return (false);
}

static bool	check_meal(t_data *data)
{
	int	i;
	int	finished;

	if (data->must_eat == -1)
		return (false);
	finished = 0;
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (data->philos[i].meals_eaten >= data->must_eat)
			finished++;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	return (finished == data->num_philos);
}

void	monitoring(t_data *data)
{
	int	i;

	while (!data->someone_died)
	{
		i = 0;
		while (i < data->num_philos && !data->someone_died)
		{
			if (check_death(data, i))
				break ;
			if (check_meal(data))
			{
				pthread_mutex_lock(&data->print_mutex);
				data->someone_died = true;
				pthread_mutex_unlock(&data->print_mutex);
				break ;
			}
			i++;
		}
		if (data->someone_died)
			break ;
		usleep(1000);
	}
}
