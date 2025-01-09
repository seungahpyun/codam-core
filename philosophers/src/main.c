/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/07 11:53:19 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/09 09:42:40 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_simulation(t_data *data)
{
	int	i;

	data->start_time = get_time();
	data->someone_died = false;
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].last_meal = get_time();
		if (pthread_create(&data->philos[i].thread,
				NULL, philo_routine, &data->philos[i]))
			return (EXIT_SUCCESS);
		i++;
	}
	monitoring(data);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (argc != 5 && argc != 6)
		return (error_msg("Error: wrong number of arguments"));
	if (!init_data(&data, argc, argv))
		return (error_msg("Error: invalid arguments"));
	if (!init_mutex(&data))
		return (error_msg("Error: mutex initialization failed"));
	if (!init_philos(&data))
		return (error_cleanup("Error: philosopher initialization failed",
				&data));
	if (!start_simulation(&data))
		return (error_cleanup("Error: simulation failed", &data));
	cleanup(&data);
	return (EXIT_SUCCESS);
}
