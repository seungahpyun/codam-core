/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_element_check_bonus.c                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/24 13:38:14 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/29 12:45:39 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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

static bool	scan_map_elements(t_game *game)
{
	t_element_status	status;

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
