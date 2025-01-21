/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/10 11:22:07 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/21 11:38:36 by spyun         ########   odam.nl         */
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
		custom_sleep(philo->data->time_to_eat * 0.1);
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_status(philo, "has taken a fork");
		custom_sleep(philo->data->time_to_die);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return ;
	}
	take_forks(philo);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	print_status(philo, "is eating");
	custom_sleep(philo->data->time_to_eat);
	release_forks(philo);
}

void	think(t_philo *philo)
{
	time_t	time_since_meal;
	time_t	think_time;
	time_t	next_meal_gap;

	print_status(philo, "is thinking");
	if (philo->id % 2 == 0)
		custom_sleep(philo->data->time_to_eat / 2);
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
