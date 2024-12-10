/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:12:45 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/10 09:01:47 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		status;
	int		exit_status;

	status = 0;
	exit_status = 0;
	if (argc < 5)
		error_exit("Usage: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2", &pipex);
	init_pipex(&pipex, argc, argv);
	create_pipes(&pipex);
	execute_commands(&pipex, envp);
	cleanup_pipex(&pipex);
	while (wait(&status) > 0)
	{
		if (WIFSIGNALED(status))
			exit_status = 128 + WTERMSIG(status);
		else if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
	}
	return (exit_status);
}
