/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_bonus.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:16:05 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/10 09:10:26 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	handle_first_cmd(t_pipex *pipex, char **envp, int cmd_index)
{
	int	fd_in;

	if (pipex->here_doc)
		handle_here_doc(pipex);
	else
	{
		fd_in = open(pipex->infile, O_RDONLY);
		if (fd_in == -1)
			error_exit("Input file error", pipex);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (cmd_index < pipex->pipe_count)
		dup2(pipex->pipes[cmd_index][1], STDOUT_FILENO);
	close_pipes(pipex);
	execute_cmd(pipex->cmds[cmd_index], envp, pipex);
}

static void	handle_middle_cmd(t_pipex *pipex, char **envp, int cmd_index)
{
	dup2(pipex->pipes[cmd_index - 1][0], STDIN_FILENO);
	dup2(pipex->pipes[cmd_index][1], STDOUT_FILENO);
	close_pipes(pipex);
	execute_cmd(pipex->cmds[cmd_index], envp, pipex);
}

static void	handle_last_cmd(t_pipex *pipex, char **envp, int cmd_index)
{
	int	fd_out;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (pipex->here_doc)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd_out = open(pipex->outfile, flags, 0644);
	if (fd_out == -1)
		error_exit("Output file error", pipex);
	dup2(pipex->pipes[cmd_index - 1][0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	close_pipes(pipex);
	execute_cmd(pipex->cmds[cmd_index], envp, pipex);
}

void	execute_commands(t_pipex *pipex, char **envp)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipex->cmd_count)
	{
		pipex->pids[i] = fork();
		if (pipex->pids[i] == -1)
			error_exit("Fork failed", pipex);
		if (pipex->pids[i] == 0)
		{
			if (i == 0)
				handle_first_cmd(pipex, envp, i);
			else if (i == pipex->cmd_count - 1)
				handle_last_cmd(pipex, envp, i);
			else
				handle_middle_cmd(pipex, envp, i);
		}
		i++;
	}
	close_pipes(pipex);
	i = 0;
	while (i < pipex->cmd_count)
		waitpid(pipex->pids[i++], &status, 0);
}
