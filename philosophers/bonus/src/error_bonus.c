/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/17 14:42:09 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/17 14:43:26 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	emergency_cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (data->philos[i].pid > 0)
			kill(data->philos[i].pid, SIGKILL);
		i++;
	}
	cleanup(data);
	exit(EXIT_FAILURE);
}

int	error_msg(char *msg)
{
	printf("%s\n", msg);
	return (EXIT_FAILURE);
}

int	error_cleanup(char *msg, t_data *data)
{
	printf("%s\n", msg);
	cleanup(data);
	return (EXIT_FAILURE);
}
