/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 14:40:18 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/10 15:24:51 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	wait_for_processes(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->num_philos)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == EXIT_FAILURE)
		{
			i = 0;
			while (i < data->num_philos)
			{
				if (data->philos[i].pid > 0)
					kill(data->philos[i].pid, SIGKILL);
				i++;
			}
			break ;
		}
		i++;
	}
}

static int	start_simulation(t_data *data)
{
	int		i;
	pid_t	pid;

	data->start_time = get_time();
	data->someone_died = false;
	i = 0;
	while (i < data->num_philos)
	{
		pid = fork();
		if (pid == -1)
			return (error_msg("Fork failed"));
		if (pid == 0)
		{
			data->philos[i].last_meal = data->start_time;
			philo_routine(&data->philos[i]);
			exit(EXIT_SUCCESS);
		}
		data->philos[i].pid = pid;
		i++;
		usleep(100);
	}
	wait_for_processes(data);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (argc != 5 && argc != 6)
		return (error_msg("Error: wrong number of arguments"));
	if (!init_data(&data, argc, argv))
		return (error_msg("Error: invalid arguments"));
	if (!init_semaphores(&data))
		return (error_cleanup("Error: semaphore initialization failed",
				&data));
	if (!init_philos(&data))
		return (error_cleanup("Error: philosopher initialization failed",
				&data));
	if (start_simulation(&data) != EXIT_SUCCESS)
		return (error_cleanup("Error: simulation failed", &data));
	cleanup(&data);
	return (EXIT_SUCCESS);
}
