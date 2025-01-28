/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup_bonus.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 14:40:13 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/28 17:31:41 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	close_semaphores(t_data *data)
{
	if (data->forks)
		sem_close(data->forks);
	if (data->print_sem)
		sem_close(data->print_sem);
	if (data->dead_sem)
		sem_close(data->dead_sem);
	if (data->meal_sem)
		sem_close(data->meal_sem);
}

void	sem_unlink_all(void)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_print");
	sem_unlink("/philo_dead");
	sem_unlink("/philo_meal");
}

static void	kill_processes(t_data *data)
{
	int	i;

	if (!data->philos)
		return ;
	i = 0;
	while (i < data->num_philos)
	{
		if (data->philos[i].pid > 0)
			kill(data->philos[i].pid, SIGKILL);
		i++;
	}
}

void	cleanup(t_data *data)
{
	kill_processes(data);
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	close_semaphores(data);
	sem_unlink_all();
}
