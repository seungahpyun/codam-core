/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_check.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 15:18:09 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/12 20:30:00 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static char **copy_map(t_game *game)
{
	char	**temp_map;
	int		i;

	temp_map = (char **)malloc(sizeof(char *) * game->height);
	if (!temp_map)
		return (NULL);
	i = 0;
	while (i < game->height)
	{
		temp_map[i] = ft_strdup(game->map[i]);
		if (!temp_map[i])
		{
			while (i > 0)
			{
				free(temp_map[--i]);
			}
			free(temp_map);
			return (NULL);
		}
		i++;
	}
	return (temp_map);
}

static void	flood_fill(char **map, int x, int y, t_path *path)
{
	if (x < 0 || y < 0 || x >= path->width || y >= path->height)
		return ;
	if (map[y][x] == 'C')
		path->collectibles++;
	if (map[y][x] == 'E')
		path->exit_found = 1;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, path);
	flood_fill(map, x - 1, y, path);
	flood_fill(map, x, y + 1, path);
	flood_fill(map, x, y - 1, path);
}

static void	clean_temp_map(char **temp_map, int height)
{
	int	i;

	i = 0;
	while (i < height && temp_map[i])
	{
		free(temp_map[i]);
		i++;
	}
	free(temp_map);
}

int	check_valid_path(t_game *game)
{
	char	**temp_map;
	t_path	path;
	int		is_valid;

	temp_map = copy_map(game);
	if (!temp_map)
		return (0);
	path.width = game->width;
	path.height = game->height;
	path.collectibles = 0;
	path.exit_found = 0;
	flood_fill(temp_map, game->player_x, game->player_y, &path);
	is_valid = (path.collectibles == game->collectibles && path.exit_found);
	clean_temp_map(temp_map, game->height);
	if (!is_valid)
		ft_putendl_fd("Error: Invalid path in map", 2);
	return (is_valid);
}
