/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_memory.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 10:46:15 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/23 10:13:12 by spyun         ########   odam.nl         */
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

static bool	allocate_map(t_game *game)
{
	int	i;

	if (!game || game->height <= 0 || game->width <= 0)
		return (false);
	game->map = (char **)malloc(sizeof(char *) * game->height);
	if (!game->map)
		return (false);
	i = 0;
	while (i < game->height)
	{
		game->map[i] = (char *)malloc(sizeof(char) * (game->width + 1));
		if (!game->map[i])
		{
			free_allocated_map(game, i);
			return (false);
		}
		game->map[i][game->width] = '\0';
		i++;
	}
	return (true);
}

bool	allocate_collect_instances(t_game *game)
{
	int	i;

	if (!game || game->height <= 0 || game->width <= 0)
		return (false);
	game->collect_instances = (int **)malloc(sizeof(int *) * game->height);
	if (!game->collect_instances)
		return (false);
	i = 0;
	while (i < game->height)
	{
		game->collect_instances[i] = (int *)malloc(sizeof(int) * game->width);
		if (!game->collect_instances[i])
		{
			while (--i >= 0)
				free(game->collect_instances[i]);
			free(game->collect_instances);
			return (false);
		}
		ft_memset(game->collect_instances[i], -1, sizeof(int) * game->width);
		i++;
	}
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
