/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 09:07:28 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/10 11:07:13 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_forks(t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_status(philo, "has taken a fork");
	}
}

static void	release_forks(t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	}
}

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		custom_sleep(5);
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_status(philo, "has taken a fork");
		custom_sleep(philo->data->time_to_die);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return ;
	}
	take_forks(philo);
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	custom_sleep(philo->data->time_to_eat);
	release_forks(philo);
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
	bool	should_continue;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		custom_sleep(philo->data->time_to_eat / 2);
	while (!philo->data->someone_died)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		should_continue = !philo->data->someone_died;
		pthread_mutex_unlock(&philo->data->death_mutex);
		if (!should_continue)
			break ;
		pthread_mutex_lock(&philo->data->meal_mutex);
		if (philo->data->must_eat != -1
			&& philo->meals_eaten >= philo->data->must_eat)
		{
			pthread_mutex_unlock(&philo->data->meal_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->meal_mutex);
		eat(philo);
		print_status(philo, "is sleeping");
		custom_sleep(philo->data->time_to_sleep);
		think(philo);
	}
	return (NULL);
}
