/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_element_bonus.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 10:44:27 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/29 14:03:41 by spyun         ########   odam.nl         */
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

static bool	check_element_requirements(bool player_found, bool exit_found,
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

static bool	process_element(t_game *game, t_element_status *status)
{
	if (game->map[status->i][status->j] == 'P')
		status->player_found = true;
	else if (game->map[status->i][status->j] == 'E')
		status->exit_found = true;
	if (!update_element_count(game, game->map[status->i][status->j],
		status->j, status->i))
	{
		ft_putendl_fd("Error: Duplicate player or exit", STDERR_FILENO);
		return (false);
	}
	return (true);
}

bool	validate_elements(t_game *game)
{
	t_element_status	status;

	if (!game || !game->map)
	{
		ft_putendl_fd("Error: Invalid game state", STDERR_FILENO);
		return (false);
	}
	init_element_count(game);
	status.player_found = false;
	status.exit_found = false;
	status.i = -1;
	while (++status.i < game->height)
	{
		status.j = -1;
		while (++status.j < game->width)
		{
			if (!process_element(game, &status))
				return (false);
		}
	}
	return (check_element_requirements(status.player_found,
			status.exit_found, game));
}
