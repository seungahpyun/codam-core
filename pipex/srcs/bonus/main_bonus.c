/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:12:45 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/10 07:36:49 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		exit_status;

	if (argc < 5)
		error_exit("Usage: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2");
	init_pipex(&pipex, argc, argv);
	create_pipes(&pipex);
	execute_commands(&pipex, envp);
	cleanup_pipex(&pipex);
	while  (wait(&exit_status) > 0)
		;
	return (0);
}
