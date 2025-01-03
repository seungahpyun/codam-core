/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_path_check_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 15:18:09 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/03 16:22:38 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static char	**create_map_copy(t_game *game)
{
	char	**temp_map;
	int		i;

	if (!game || !game->map || game->height <= 0)
		return (NULL);
	temp_map = (char **)malloc(sizeof(char *) * game->height);
	if (!temp_map)
		return (NULL);
	ft_memset(temp_map, 0, sizeof(char *) * game->height);
	i = 0;
	while (i < game->height)
	{
		temp_map[i] = ft_strdup(game->map[i]);
		if (!temp_map[i])
		{
			free_temp_map(temp_map, i);
			return (NULL);
		}
		i++;
	}
	return (temp_map);
}

void	free_temp_map(char **temp_map, int height)
{
	int	i;

	if (!temp_map)
		return ;
	i = 0;
	while (i < height)
	{
		free(temp_map[i]);
		i++;
	}
	free(temp_map);
}

static void	explore_path(char **map, int x, int y, t_path *path)
{
	if (x < 0 || y < 0 || x >= path->width || y >= path->height)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	if (map[y][x] == 'C')
		path->collectibles++;
	if (map[y][x] == 'E')
		path->exit_found = 1;
	map[y][x] = 'F';
	explore_path(map, x + 1, y, path);
	explore_path(map, x - 1, y, path);
	explore_path(map, x, y + 1, path);
	explore_path(map, x, y - 1, path);
}

static bool	validate_path_result(t_path *path, int total_collectibles)
{
	return (path->collectibles == total_collectibles && path->exit_found);
}

bool	check_valid_path(t_game *game)
{
	char	**temp_map;
	t_path	path;
	bool	is_valid;

	if (!game || !game->map)
		return (false);
	temp_map = create_map_copy(game);
	if (!temp_map)
		return (false);
	path.width = game->width;
	path.height = game->height;
	path.collectibles = 0;
	path.exit_found = false;
	explore_path(temp_map, game->player_x, game->player_y, &path);
	is_valid = validate_path_result(&path, game->collectibles);
	free_temp_map(temp_map, game->height);
	if (!is_valid)
		ft_putendl_fd("Error: Invalid path in map", STDERR_FILENO);
	return (is_valid);
}
