/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 09:07:28 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/17 17:47:52 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	should_continue_routine(t_philo *philo)
{
	bool	continue_flag;

	pthread_mutex_lock(&philo->data->death_mutex);
	continue_flag = !philo->data->someone_died;
	pthread_mutex_unlock(&philo->data->death_mutex);
	if (!continue_flag)
		return (false);
	pthread_mutex_lock(&philo->data->meal_mutex);
	if (philo->data->must_eat != -1
		&& philo->meals_eaten >= philo->data->must_eat)
	{
		pthread_mutex_unlock(&philo->data->meal_mutex);
		return (false);
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (true);
}

static void	perform_routine(t_philo *philo)
{
	eat(philo);
	print_status(philo, "is sleeping");
	custom_sleep(philo->data->time_to_sleep);
	think(philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		custom_sleep(philo->data->time_to_eat / 2);
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->someone_died)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		if (!should_continue_routine(philo))
			break ;
		perform_routine(philo);
	}
	return (NULL);
}
