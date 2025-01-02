/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy_movement_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/31 10:50:38 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/02 10:06:44 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static bool	is_valid_enemy_move(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->width || y >= game->height)
		return (false);
	if (game->map[y][x] == '1' || game->map[y][x] == 'E'
		|| game->map[y][x] == 'C')
		return (false);
	return (true);
}

static void	try_move(t_game *game, t_enemy *enemy, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = enemy->x + dx;
	new_y = enemy->y + dy;
	if (is_valid_enemy_move(game, new_x, new_y))
	{
		enemy->x = new_x;
		enemy->y = new_y;
	}
	else if (dx != 0 && is_valid_enemy_move(game, new_x, enemy->y))
		enemy->x = new_x;
	else if (dy != 0 && is_valid_enemy_move(game, enemy->x, new_y))
		enemy->y = new_y;
}

static bool	is_player_in_sight(t_game *game, t_enemy *enemy)
{
	return (abs(game->player_x - enemy->x) <= enemy->sight_range
		&& abs(game->player_y - enemy->y) <= enemy->sight_range);
}

void	move_chase_player(t_game *game, t_enemy *enemy)
{
	int	dx;
	int	dy;

	if (is_player_in_sight(game, enemy))
		get_chase_direction(game, enemy, &dx, &dy);
	else
		get_random_direction(&dx, &dy);
	try_move(game, enemy, dx, dy);
}
