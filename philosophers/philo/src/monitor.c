/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 09:19:46 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/23 12:19:06 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_death(t_data *data, int id, time_t death_time)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %d died\n", death_time - data->start_time, id);
	pthread_mutex_unlock(&data->print_mutex);
}

static bool	check_death(t_data *data, int i)
{
	time_t	current_time;
	time_t	time_since_meal;
	bool	is_dead;

	current_time = get_time();
	pthread_mutex_lock(&data->meal_mutex);
	time_since_meal = current_time - data->philos[i].last_meal;
	is_dead = time_since_meal >= data->time_to_die;
	pthread_mutex_unlock(&data->meal_mutex);
	if (is_dead)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (!data->someone_died)
		{
			data->someone_died = true;
			print_death(data, data->philos[i].id, current_time);
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

static bool	check_philosopher_status(t_data *data)
{
	int		i;
	bool	someone_died;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->death_mutex);
		someone_died = data->someone_died;
		pthread_mutex_unlock(&data->death_mutex);
		if (someone_died)
			return (true);
		if (check_death(data, i))
			return (true);
		if (data->must_eat != -1 && check_meal(data))
		{
			pthread_mutex_lock(&data->death_mutex);
			data->someone_died = true;
			pthread_mutex_unlock(&data->death_mutex);
			return (true);
		}
		i++;
	}
	return (false);
}

void	monitoring(t_data *data)
{
	while (1)
	{
		if (check_philosopher_status(data))
			break ;
		usleep(1000);
	}
}
