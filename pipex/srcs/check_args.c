/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/04 09:55:05 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/05 10:07:12 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void	check_infile(char *infile)
{
	if (access(infile, F_OK) == -1)
		error_exit();
	if (access(infile, R_OK) == -1)
		error_exit();
}

void	check_outfile(char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error_exit();
	close(fd);
}

void	check_args(int argc, char **argv)
{
	if (argc != 5)
		error_exit();
	check_infile(argv[1]);
	check_outfile(argv[4]);
}
