/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:15:03 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/10 08:10:09 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	create_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->pipe_count)
	{
		pipex->pipes[i] = malloc(sizeof(int) * 2);
		if (!pipex->pipes[i])
		{
			while (--i >= 0)
				free(pipex->pipes[i]);
			free(pipex->pipes);
			error_exit("Malloc failed");
		}
		if (pipe(pipex->pipes[i]) == -1)
		{
			while (i >= 0)
				free(pipex->pipes[i--]);
			free(pipex->pipes);
			error_exit("Pipe failed");
		}
		i++;
	}
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->pipe_count)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		i++;
	}
}
