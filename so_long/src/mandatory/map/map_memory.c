/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_memory.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 10:46:15 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/24 11:26:48 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_allocated_map(t_game *game, int last_row)
{
	int	i;

	if (!game || !game->map)
		return ;
	i = 0;
	while (i < last_row)
	{
		if (game->map[i])
			free(game->map[i]);
		i++;
	}
	free(game->map);
	game->map = NULL;
}

static bool	fill_single_row(t_game *game, char *line, int row)
{
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	if (!ft_strlcpy(game->map[row], line, game->width + 1))
		return (false);
	return (true);
}

static bool	fill_map(t_game *game, char *file)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (false);
	i = 0;
	while (i < game->height)
	{
		line = get_next_line(fd);
		if (!line || !fill_single_row(game, line, i))
		{
			if (line)
				free(line);
			close(fd);
			return (false);
		}
		free(line);
		i++;
	}
	close(fd);
	return (true);
}

bool	allocate_and_fill_map(t_game *game, char *file)
{
	if (!game || !file)
		return (false);
	if (!allocate_map(game))
		return (false);
	if (!fill_map(game, file))
	{
		free_allocated_map(game, game->height);
		return (false);
	}
	return (true);
}
