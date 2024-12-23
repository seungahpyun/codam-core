/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:12:45 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/23 12:25:56 by spyun         ########   odam.nl         */
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
	{
		ft_putendl_fd("Error: Not enough arguments", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	init_pipex(&pipex, argc, argv);
	create_pipes(&pipex);
	execute_commands(&pipex, envp);
	while (wait(&status) > 0)
	{
		if (WIFSIGNALED(status))
			exit_status = 128 + WTERMSIG(status);
		else if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
	}
	cleanup_pipex(&pipex);
	return (exit_status);
}
