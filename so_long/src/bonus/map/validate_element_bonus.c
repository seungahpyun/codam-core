/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_element_bonus.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 10:44:27 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/24 09:53:18 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	init_element_count(t_game *game)
{
	game->collectibles = 0;
	game->player_x = -1;
	game->player_y = -1;
}

static bool	update_element_count(t_game *game, char element, int x, int y)
{
	static int	player_count = 0;
	static int	exit_count = 0;

	if (element == 'P')
	{
		player_count++;
		game->player_x = x;
		game->player_y = y;
	}
	else if (element == 'E')
		exit_count++;
	else if (element == 'C')
		game->collectibles++;
	if (player_count > 1 || exit_count > 1)
		return (false);
	return (true);
}

static bool	check_element_requirements(int player_found, int exit_found,
	t_game *game)
{
	if (!player_found)
	{
		ft_putendl_fd("Error: No player found", STDERR_FILENO);
		return (false);
	}
	if (!exit_found)
	{
		ft_putendl_fd("Error: No exit found", STDERR_FILENO);
		return (false);
	}
	if (game->collectibles == 0)
	{
		ft_putendl_fd("Error: No collectibles found", STDERR_FILENO);
		return (false);
	}
	return (true);
}

static bool	scan_map_elements(t_game *game)
{
	int		i;
	int		j;
	bool	player_found;
	bool	exit_found;

	init_element_count(game);
	player_found = false;
	exit_found = false;
	i = -1;
	while (++i < game->height)
	{
		j = -1;
		while (++j < game->width)
		{
			if (game->map[i][j] == 'P')
				player_found = true;
			else if (game->map[i][j] == 'E')
				exit_found = true;
			if (!update_element_count(game, game->map[i][j], j, i))
			{
				ft_putendl_fd("Error: Duplicate player or exit", STDERR_FILENO);
				return (false);
			}
		}
	}
	return (check_element_requirements(player_found, exit_found, game));
}

bool	validate_elements(t_game *game)
{
	if (!game || !game->map)
	{
		ft_putendl_fd("Error: Invalid game state", STDERR_FILENO);
		return (false);
	}
	if (!scan_map_elements(game))
		return (false);
	return (true);
}
