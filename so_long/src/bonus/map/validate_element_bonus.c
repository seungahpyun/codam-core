/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_element_bonus.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 10:44:27 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/24 13:37:57 by spyun         ########   odam.nl         */
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
