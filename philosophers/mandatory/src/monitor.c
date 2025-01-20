/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 09:19:46 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/20 09:12:18 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool    check_death(t_data *data, int i)
{
    time_t  current_time;
    time_t  time_since_meal;

    pthread_mutex_lock(&data->meal_mutex);
    current_time = get_time();
    time_since_meal = current_time - data->philos[i].last_meal;
    pthread_mutex_unlock(&data->meal_mutex);

    if (time_since_meal > data->time_to_die)
        return (true);
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
		usleep(50);
	}
}
