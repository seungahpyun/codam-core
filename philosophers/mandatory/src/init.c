/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 09:07:23 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/10 14:55:03 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	init_mutex(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (false);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (false);
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (false);
	if (pthread_mutex_init(&data->meal_mutex, NULL))
		return (false);
	if (pthread_mutex_init(&data->death_mutex, NULL))
		return (false);
	return (true);
}

bool	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (false);
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->num_philos;
		data->philos[i].last_meal = get_time();
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		i++;
	}
	return (true);
}

bool	init_data(t_data *data, int argc, char **argv)
{
	if (!check_valid_input(argv[1]) || !check_valid_input(argv[2])
		|| !check_valid_input(argv[3]) || !check_valid_input(argv[4]))
		return (false);
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		if (!check_valid_input(argv[5]))
			return (false);
		data->must_eat = ft_atoi(argv[5]);
	}
	else
		data->must_eat = -1;
	if (data->num_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| (argc == 6 && data->must_eat <= 0))
		return (false);
	return (true);
}
