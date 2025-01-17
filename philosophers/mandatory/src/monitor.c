/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 09:19:46 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/17 17:46:33 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	check_death(t_data *data, int i)
{
	time_t	current_time;
	time_t	last_meal_time;
	bool	is_dead;

	is_dead = false;
	pthread_mutex_lock(&data->meal_mutex);
	current_time = get_time();
	last_meal_time = data->philos[i].last_meal;
	pthread_mutex_unlock(&data->meal_mutex);
	if (current_time - last_meal_time > data->time_to_die)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (!data->someone_died)
		{
			data->someone_died = true;
			is_dead = true;
			pthread_mutex_lock(&data->print_mutex);
			printf("%ld %d died\n", current_time - data->start_time, i + 1);
			pthread_mutex_unlock(&data->print_mutex);
		}
		pthread_mutex_unlock(&data->death_mutex);
	}
	return (is_dead);
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
	int		i;
	bool	someone_died;

	someone_died = false;
	while (!someone_died)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_lock(&data->death_mutex);
			someone_died = data->someone_died;
			pthread_mutex_unlock(&data->death_mutex);
			if (someone_died || check_death(data, i))
			{
				someone_died = true;
				break ;
			}
			if (check_meal(data))
			{
				pthread_mutex_lock(&data->death_mutex);
				data->someone_died = true;
				pthread_mutex_unlock(&data->death_mutex);
				someone_died = true;
				break ;
			}
			i++;
		}
		usleep(100);
	}
}
