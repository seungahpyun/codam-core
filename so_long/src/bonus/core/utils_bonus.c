/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 13:54:06 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/24 09:29:56 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	handle_close(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game)
		return ;
	cleanup_game(game);
	exit(EXIT_SUCCESS);
}

void	error_exit(char *message, t_game *game)
{
	if(message)
		ft_putendl_fd(message, STDERR_FILENO);
	if (game)
		cleanup_game(game);
	exit(EXIT_FAILURE);
}

void	validate_file_extension(const char *filename)
{
	size_t	len;

	if (!filename)
		error_exit("Error: No filename provided", NULL);
	len = ft_strlen(filename);
	if (len < 4)
		error_exit("Error: Invalid filename", NULL);
	if (ft_strncmp(filename + len - 4, ".ber", 4) != 0)
		error_exit("Error: File must be a .ber file", NULL);
}

void	check_file_access(const char *filename)
{
	int	fd;

	if (!filename)
		error_exit("Error: No filename provided", NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_exit("Error: Cannot access map file", NULL);
	close(fd);
}

