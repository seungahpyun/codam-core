/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:20:05 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/10 09:53:46 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		status;

	check_args(argc, argv);
	init_pipex(&pipex, argv);
	create_pipe(&pipex);
	execute_commands(&pipex, envp);
	waitpid(pipex.pid1, &status, 0);
	waitpid(pipex.pid2, &status, 0);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}
