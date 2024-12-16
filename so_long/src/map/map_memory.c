/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_memory.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 10:46:15 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/16 14:36:38 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_allocated_map(t_game *game, int last_row)
{
	int	i;

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

int	fill_map(t_game *game, char *file)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	i = 0;
	while (i < game->height)
	{
		line = get_next_line(fd);
		if (!line)
		{
			close(fd);
			return (0);
		}
		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		ft_strlcpy(game->map[i], line, game->width + 1);
		free(line);
		i++;
	}
	close(fd);
	return (1);
}

int	allocate_map(t_game *game)
{
	int	i;

	if (!game || game->height <= 0 || game->width <= 0)
		return (0);
	game->map = (char **)malloc(sizeof(char *) * game->height);
	if (!game->map)
		return (0);
	i = 0;
	while (i < game->height)
	{
		game->map[i] = (char *)malloc(sizeof(char) * (game->width + 1));
		if (!game->map[i])
		{
			free_allocated_map(game, i);
			return (0);
		}
		game->map[i][game->width] = '\0';
		i++;
	}
	return (1);
}

int	allocate_and_fill_map(t_game *game, char *file)
{
	if (!allocate_map(game))
		return (0);
	if (!fill_map(game, file))
	{
		free_allocated_map(game, game->height);
		return (0);
	}
	return (1);
}
