/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/10 11:22:07 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/21 13:38:33 by spyun         ########   odam.nl         */
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
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_status(philo, "has taken a fork");
		custom_sleep(philo->data->time_to_die);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return ;
	}
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	take_forks(philo);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal = get_time();
	print_status(philo, "is eating");
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	custom_sleep(philo->data->time_to_eat);
	release_forks(philo);
}

void	think(t_philo *philo)
{
	time_t	time_to_next_meal;
	time_t	think_time;

	print_status(philo, "is thinking");
	pthread_mutex_lock(&philo->data->meal_mutex);
	time_to_next_meal = (philo->last_meal + philo->data->time_to_die)
		- get_time();
	pthread_mutex_unlock(&philo->data->meal_mutex);
	if (time_to_next_meal > philo->data->time_to_eat + 20)
	{
		if (philo->id % 2 == 0)
			think_time = 15;
		else
			think_time = philo->data->time_to_eat / 2;
		custom_sleep(think_time);
	}
}
