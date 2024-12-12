/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:20:34 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/12 09:02:01 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_pipex(t_pipex *pipex, char **argv)
{
	pipex->infile = argv[1];
	pipex->outfile = argv[4];
	pipex->cmd1 = argv[2];
	pipex->cmd2 = argv[3];
}

void	create_pipe(t_pipex *pipex)
{
	if (pipe(pipex->pipe_fd) == -1)
		perror_exit("Pipe failed");
}
