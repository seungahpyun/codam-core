/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:47 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/06 11:42:33 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	check_line_width(char *line, int width)
{
	int	len;

	if (!line)
		return (false);
	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		len--;
	return (len == width);
}

static bool	process_first_line(char *line, t_game *game)
{
	if (!line)
		return (false);
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	game->width = ft_strlen(line);
	game->height = 1;
	free(line);
	return (true);
}

static bool	process_next_lines(int fd, t_game *game)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!check_line_width(line, game->width))
		{
			free(line);
			return (false);
		}
		game->height++;
		free(line);
	}
	return (true);
}

static bool	get_map_dimensions(t_game *game, char *file)
{
	int		fd;
	bool	result;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (false);
	if (!process_first_line(get_next_line(fd), game))
	{
		close(fd);
		return (false);
	}
	result = process_next_lines(fd, game);
	close(fd);
	return (result && game->width > 0 && game->height > 0);
}

bool	parse_map(t_game *game, char *file)
{
	if (!game || !file)
		return (false);
	if (!get_map_dimensions(game, file))
	{
		ft_putendl_fd("Error: Invalid map dimensions", STDERR_FILENO);
		return (false);
	}
	if (game->width == game->height)
	{
		ft_putendl_fd("Error: Map cannot be square", STDERR_FILENO);
		return (false);
	}
	if (!allocate_and_fill_map(game, file))
	{
		ft_putendl_fd("Error: Map allocation failed", STDERR_FILENO);
		return (false);
	}
	if (!validate_map(game))
	{
		free_allocated_map(game, game->height);
		return (false);
	}
	return (true);
}
