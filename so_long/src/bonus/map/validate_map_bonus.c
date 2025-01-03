/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:59 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/03 16:22:53 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static bool	check_horizontal_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->width)
	{
		if (game->map[0][i] != '1')
		{
			ft_putendl_fd("Error: Top wall broken", STDERR_FILENO);
			return (false);
		}
		if (game->map[game->height - 1][i] != '1')
		{
			ft_putendl_fd("Error: Bottom wall broken", STDERR_FILENO);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	check_vertical_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->height)
	{
		if (game->map[i][0] != '1')
		{
			ft_putendl_fd("Error: Left wall broken", STDERR_FILENO);
			return (false);
		}
		if (game->map[i][game->width - 1] != '1')
		{
			ft_putendl_fd("Error: Right wall broken", STDERR_FILENO);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	check_valid_characters(t_game *game)
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
			if (c != '0' && c != '1' && c != 'C' && c != 'E'
				&& c != 'P' && c != 'X')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

static void	count_enemy_positions(t_game *game)
{
	int	i;
	int	j;

	game->enemy_count = 0;
	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			if (game->map[i][j] == 'X')
				game->enemy_count++;
			j++;
		}
		i++;
	}
}

bool	validate_map(t_game *game)
{
	if (!game || !game->map)
		return (false);
	if (!check_horizontal_walls(game) || !check_vertical_walls(game))
		return (false);
	if (!check_valid_characters(game))
	{
		ft_putendl_fd("Error: Invalid characters in map", STDERR_FILENO);
		return (false);
	}
	if (!validate_elements(game))
		return (false);
	if (!check_valid_path(game))
		return (false);
	count_enemy_positions(game);
	return (true);
}
