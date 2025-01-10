/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 14:40:15 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/10 11:51:00 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	sem_unlink_all(void)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_print");
	sem_unlink("/philo_dead");
	sem_unlink("/philo_meal");
}

bool	init_semaphores(t_data *data)
{
	sem_unlink_all();
	data->forks = sem_open("/philo_forks", O_CREAT | O_EXCL, 0644,
			data->num_philos);
	if (data->forks == SEM_FAILED)
		return (false);
	data->print_sem = sem_open("/philo_print", O_CREAT | O_EXCL, 0644, 1);
	if (data->print_sem == SEM_FAILED)
		return (false);
	data->dead_sem = sem_open("/philo_dead", O_CREAT | O_EXCL, 0644, 1);
	if (data->dead_sem == SEM_FAILED)
		return (false);
	data->meal_sem = sem_open("/philo_meal", O_CREAT | O_EXCL, 0644, 1);
	if (data->meal_sem == SEM_FAILED)
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
		data->philos[i].pid = 0;
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
