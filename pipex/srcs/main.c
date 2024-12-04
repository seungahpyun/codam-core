/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/04 09:51:48 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/04 10:50:34 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <unistd.h>
#include <sys/wait.h>

int	main(int argc, char **argv)
{
	check_args(argc, argv);
	create_pipe(argv, NULL);
	
	wait(NULL);
	wait(NULL);
	return (0);
}
