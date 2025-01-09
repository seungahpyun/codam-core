/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 09:07:28 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/09 11:27:57 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		custom_sleep(5);
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_status(philo, "has taken a fork");
	if (philo->data->num_philos == 1)
	{
		custom_sleep(philo->data->time_to_die);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return ;
	}
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->print_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->print_mutex);
	custom_sleep(philo->data->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	think(t_philo *philo)
{
	long long	time_since_meal;
	long long	think_time;
	long long	next_meal_gap;

	print_status(philo, "is thinking");
	time_since_meal = get_time() - philo->last_meal;
	next_meal_gap = philo->data->time_to_die - time_since_meal;
	if (next_meal_gap >= philo->data->time_to_eat * 2)
	{
		think_time = philo->data->time_to_eat / 2;
		if (philo->id % 2)
			think_time = think_time * 0.8;
		custom_sleep(think_time);
	}
	else if (next_meal_gap > 50)
	{
		think_time = 30;
		custom_sleep(think_time);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		custom_sleep(philo->data->time_to_eat / 2);
	while (!philo->data->someone_died)
	{
		if (philo->data->must_eat != -1
			&& philo->meals_eaten >= philo->data->must_eat)
			break ;
		eat(philo);
		print_status(philo, "is sleeping");
		custom_sleep(philo->data->time_to_sleep);
		think(philo);
	}
	return (NULL);
}
