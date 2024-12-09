/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:20:05 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/09 14:07:05 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	handle_child_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		status1;
	int		status2;
	int		final_status;

	check_args(argc, argv);
	init_pipex(&pipex, argv);
	create_pipe(&pipex);
	execute_commands(&pipex, envp);
	waitpid(pipex.pid1, &status1, 0);
	waitpid(pipex.pid2, &status2, 0);
	status1 = handle_child_status(status1);
	status2 = handle_child_status(status2);
	final_status = status2;
	if (status1 == 127 || status2 == 127)
		final_status = 127;
	else if (status1 == 126 || status2 == 126)
		final_status = 126;
	return (final_status);
}
