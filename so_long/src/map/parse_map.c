/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:47 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/16 16:32:39 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_line_length(char *line, int width)
{
	int	line_len;

	if (!line)
		return (0);
	line_len = ft_strlen(line);
	if (line[line_len - 1] == '\n')
		line_len--;
	return (line_len == width);
}

static int	get_first_line_width(int fd, int *width)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (0);
	*width = ft_strlen(line);
	if (line[*width - 1] == '\n')
		(*width)--;
	free(line);
	return (1);
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

	if (!game || !file)
		return (0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	game->height = 0;
	if (!get_first_line_width(fd, &game->width))
	{
		close(fd);
		return (0);
	}
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
	{
		ft_putendl_fd("Error: Invalid map dimensions", 2);
		return (0);
	}
	if (!allocate_and_fill_map(game, file))
	{
		ft_putendl_fd("Error: Map allocation failed", 2);
		return (0);
	}
	if (!validate_map(game))
	{
		free_allocated_map(game, game->height);
		return (0);
	}
	return (1);
}
