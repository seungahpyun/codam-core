/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:47 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/16 14:30:40 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_line_length(char *line, int width)
{
	int	line_len;

	line_len = ft_strlen(line) - 1;
	return (line_len == width);
}

static int	process_map_lines(int fd, t_game *game)
{
	char	*line;
	int		success;

	success = 1;
	while (success)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		game->height++;
		if (!check_line_length(line, game->width))
			success = 0;
		free(line);
	}
	return (success);
}

static int	get_map_dimensions(t_game *game, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	game->height = 0;
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (0);
	}
	game->width = ft_strlen(line) - 1;
	free(line);
	if (!process_map_lines(fd, game))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	parse_map(t_game *game, char *file)
{
	if (!game || !file)
		return (0);
	if (!get_map_dimensions(game, file))
		return (0);
	if (!allocate_map(game))
		return (0);
	if (!fill_map(game, file))
	{
		free_allocated_map(game, game->height);
		return (0);
	}
	if (!validate_map(game))
	{
		free_allocated_map(game, game->height);
		return (0);
	}
	return (1);
}
