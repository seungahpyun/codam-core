/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 07:21:58 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/12 09:01:19 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	check_infile(char *infile)
{
	if (access(infile, F_OK) == -1)
		perror_exit("Input file not found");
	if (access(infile, R_OK) == -1)
		perror_exit("Input file permission denied");
}

static void	check_outfile(char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		perror_exit("Output file permission denied");
	close(fd);
}

void	check_args(int argc, char **argv)
{
	if (argc != 5)
		error_exit("Usage: ./pipex infile cmd1 cmd2 outfile\n");
	check_infile(argv[1]);
	check_outfile(argv[4]);
}
