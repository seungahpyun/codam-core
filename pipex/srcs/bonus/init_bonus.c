/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:13:41 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/10 09:01:32 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	init_here_doc(t_pipex *pipex, int argc, char **argv)
{
	pipex->here_doc = true;
	pipex->limiter = argv[2];
	pipex->cmd_count = argc - 4;
	pipex->pipe_count = pipex->cmd_count - 1;
	pipex->infile = NULL;
	pipex->outfile = argv[argc - 1];
	pipex->cmds = argv + 3;
}

static void	init_regular(t_pipex *pipex, int argc, char **argv)
{
	pipex->cmd_count = argc - 3;
	pipex->pipe_count = pipex->cmd_count - 1;
	pipex->infile = argv[1];
	pipex->outfile = argv[argc - 1];
	pipex->cmds = argv + 2;
}

static void	allocate_memory(t_pipex *pipex)
{
	pipex->pipes = malloc(sizeof(int *) * pipex->pipe_count);
	if (!pipex->pipes)
		error_exit("Malloc failed", pipex);
	pipex->pids = malloc(sizeof(pid_t) * pipex->cmd_count);
	if (!pipex->pids)
	{
		free(pipex->pipes);
		error_exit("Malloc failed", pipex);
	}
}

void	init_pipex(t_pipex *pipex, int argc, char **argv)
{
	pipex->here_doc = false;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		init_here_doc(pipex, argc, argv);
	else
		init_regular(pipex, argc, argv);
	allocate_memory(pipex);
}
