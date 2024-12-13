/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:59 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/13 10:45:17 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	check_wall(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->width)
	{
		if (game->map[0][i] != '1' || game->map[game->height - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < game->height)
	{
		if (game->map[i][0] != '1' || game->map[i][game->width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

static int	check_player(t_game *game)
{
	int	player_found;
	int	valid_path;

	player_found = find_player(game);
	if (player_found != 1)
		return (0);
	valid_path = check_valid_path(game);
	return (valid_path);
}

static int	check_characters(t_game *game)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			c = game->map[i][j];
			if (c != '0' && c != '1' && c != 'C'
				&& c != 'E' && c != 'P')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_map(t_game *game)
{
	if (!check_wall(game))
	{
		ft_putendl_fd("Error: Invalid wall configuration", 2);
		return (0);
	}
	if (!check_characters(game))
	{
		ft_putendl_fd("Error: Invalid characters in map", 2);
		return (0);
	}
	if (!count_elements(game))
	{
		ft_putendl_fd("Error: Invalid number of elements", 2);
		return (0);
	}
	if (!check_player(game))
	{
		ft_putendl_fd("Error: Invalid player position or path", 2);
		return (0);
	}
	return (1);
}
