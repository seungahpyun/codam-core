/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_bonus.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 14:42:26 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/10 15:25:36 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	check_death(t_philo *philo)
{
	if (get_time() - philo->last_meal > philo->data->time_to_die)
	{
		sem_wait(philo->data->print_sem);
		printf("%ld %d died\n", get_time() - philo->data->start_time,
			philo->id);
		exit(EXIT_FAILURE);
	}
}

static void	eat(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	philo->last_meal = get_time();
	philo->meals_eaten++;
	custom_sleep(philo->data->time_to_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	philo_routine(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		print_status(philo, "has taken a fork");
		custom_sleep(philo->data->time_to_die);
		print_status(philo, "died");
		exit(EXIT_FAILURE);
	}
	if (philo->id % 2 == 0)
		custom_sleep(philo->data->time_to_eat / 2);
	while (!philo->data->someone_died)
	{
		check_death(philo);
		if (philo->data->must_eat != -1
			&& philo->meals_eaten >= philo->data->must_eat)
			exit(EXIT_SUCCESS);
		eat(philo);
		print_status(philo, "is sleeping");
		custom_sleep(philo->data->time_to_sleep);
		print_status(philo, "is thinking");
		usleep(100);
	}
}
