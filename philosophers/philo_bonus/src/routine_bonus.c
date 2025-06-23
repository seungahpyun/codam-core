/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_bonus.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 14:42:26 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/23 11:27:37 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_bonus.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 14:42:26 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/03 09:14:38 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	*death_checker(void *arg)
{
	t_philo	*philo;
	time_t	last_meal_copy;

	philo = (t_philo *)arg;
	while (!philo->data->someone_died)
	{
		sem_wait(philo->data->meal_sem);
		last_meal_copy = philo->last_meal;
		sem_post(philo->data->meal_sem);
		if (get_time() - last_meal_copy >= philo->data->time_to_die)
		{
			sem_wait(philo->data->print_sem);
			printf("%ld %d died\n", get_time() - philo->data->start_time,
				philo->id);
			exit(EXIT_FAILURE);
		}
		usleep(1000);
	}
	return (NULL);
}

static void	eat(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	sem_wait(philo->data->meal_sem);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	sem_post(philo->data->meal_sem);
	custom_sleep(philo->data->time_to_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

static bool	should_continue(t_philo *philo)
{
	bool	should_continue;

	sem_wait(philo->data->meal_sem);
	should_continue = (philo->data->must_eat == -1
			|| philo->meals_eaten < philo->data->must_eat);
	sem_post(philo->data->meal_sem);
	return (should_continue);
}

void	philo_routine(t_philo *philo)
{
	pthread_t	death_checker_thread;

	if (philo->data->num_philos == 1)
		handle_single_philo(philo);
	if (pthread_create(&death_checker_thread, NULL, death_checker, philo) != 0)
		exit(EXIT_FAILURE);
	if (pthread_detach(death_checker_thread) != 0)
		exit(EXIT_FAILURE);
	if (philo->id % 2 == 0)
		custom_sleep(philo->data->time_to_eat / 2);
	while (!philo->data->someone_died && should_continue(philo))
	{
		eat(philo);
		print_status(philo, "is sleeping");
		custom_sleep(philo->data->time_to_sleep);
		print_status(philo, "is thinking");
		usleep(1000);
	}
}
