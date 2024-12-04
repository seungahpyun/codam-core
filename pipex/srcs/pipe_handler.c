/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_handler.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/04 10:26:37 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/04 14:14:34 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void	child_process(char **argv, char **envp, int *pipe_fd)
{
	int	infile_fd;

	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd == -1)
		error_exit("ERROR : infile open failed", EXIT_FAILURE);
	dup2(infile_fd, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(infile_fd);
	execute_cmd(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *pipe_fd)
{
	int	outfile_fd;

	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
		error_exit("ERROR : outfile open failed", EXIT_FAILURE);
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(outfile_fd);
	execute_cmd(argv[3], envp);
}

void	create_pipe(char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		error_exit("ERROR : pipe failed", EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		error_exit("ERROR : fork failed", EXIT_FAILURE);
	if (pid == 0)
		child_process(argv, envp, pipe_fd);
	else
		parent_process(argv, envp, pipe_fd);
}
