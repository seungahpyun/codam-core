/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/04 09:51:48 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/04 14:16:02 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	int		status;
	pid_t	wpid;
	int		last_status;
	int		exit_status;

	last_status = 0;
	check_args(argc, argv);
	create_pipe(argv, envp);
	while ((wpid = wait(&status)) > 0)
	{
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			if (exit_status != 0)
				last_status = exit_status;
		}
	return (last_status);
}
