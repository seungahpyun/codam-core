/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:20:59 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/09 14:03:00 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	child_process(t_pipex *pipex, char **envp)
{
	int	infile_fd;

	infile_fd = open(pipex->infile, O_RDONLY);
	if (infile_fd == -1)
		error_exit("Input file error");
	if (dup2(infile_fd, STDIN_FILENO) == -1)
		error_exit("Dup2 failed");
	if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
		error_exit("Dup2 failed");
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	close(infile_fd);
	execute_cmd(pipex->cmd1, envp);
}

static void	parent_process(t_pipex *pipex, char **envp)
{
	int	outfile_fd;

	outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
		error_exit("Output file error");
	if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
		error_exit("Dup2 failed");
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		error_exit("Dup2 failed");
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	close(outfile_fd);
	execute_cmd(pipex->cmd2, envp);
}

void	execute_commands(t_pipex *pipex, char **envp)
{
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
		error_exit("Fork failed");
	if (pipex->pid1 == 0)
		child_process(pipex, envp);
	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
		error_exit("Fork failed");
	if (pipex->pid2 == 0)
		parent_process(pipex, envp);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
}
