/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parser_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:47 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/29 12:55:23 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	process_map_line(char *line, t_game *game)
{
	size_t	line_len;

	if (!line || !line[0])
		return (0);
	line_len = ft_strlen(line);
	if (line[line_len - 1] == '\n')
	{
		line[line_len - 1] = '\0';
		line_len--;
	}
	if (game->height == 0)
		game->width = line_len;
	else if (game->width != (int)line_len)
		return (0);
	game->height++;
	return (1);
}

static int	validate_dimensions(t_game *game)
{
	if (game->width <= 0 || game->height <= 0)
		return (0);
	if (game->width > MAX_MAP_WIDTH || game->height > MAX_MAP_HEIGHT)
		return (0);
	return (1);
}

static int	get_map_dimensions(t_game *game, char *file)
{
	int		fd;
	char	*line;

	if (!game || !file)
		return (0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	game->height = 0;
	game->width = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!process_map_line(line, game))
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
	}
	close(fd);
	return (validate_dimensions(game));
}

static void	handle_map_error(char *error_msg, t_game *game)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(error_msg, 2);
	if (game && game->map)
		free_allocated_map(game, game->height);
}

bool	parse_map(t_game *game, char *file)
{
	if (!game || !file)
		return (false);
	if (!get_map_dimensions(game, file))
	{
		handle_map_error("Invalid map dimensions", NULL);
		return (false);
	}
	if (!allocate_map(game))
	{
		handle_map_error("Map allocation failed", NULL);
		return (false);
	}
	if (!fill_map(game, file))
	{
		handle_map_error("Failed to fill map", game);
		return (false);
	}
	if (!validate_map(game))
	{
		free_allocated_map(game, game->height);
		return (false);
	}
	return (true);
}
