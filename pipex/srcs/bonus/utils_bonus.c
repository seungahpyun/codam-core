/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:17:30 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/10 09:00:10 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	cleanup_pipex(t_pipex *pipex)
{
	int	i;

	if (pipex->pipes)
	{
		i = 0;
		while (i < pipex->pipe_count)
			free(pipex->pipes[i++]);
		free(pipex->pipes);
	}
	if (pipex->pids)
		free(pipex->pids);
}

void	error_exit(const char *msg, t_pipex *pipex)
{
	cleanup_pipex(pipex);
	perror(msg);
	exit(EXIT_FAILURE);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}
