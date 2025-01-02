/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy_movement_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/31 10:50:38 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/02 09:50:32 by spyun         ########   odam.nl         */
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

static void	try_diagonal_move(t_game *game, t_enemy *enemy, int dx, int dy)
{
	if (is_valid_enemy_move(game, enemy->x + dx, enemy->y + dy))
	{
		enemy->x += dx;
		enemy->y += dy;
		return ;
	}
	if (is_valid_enemy_move(game, enemy->x + dx, enemy->y))
	{
		enemy->x += dx;
		return ;
	}
	if (is_valid_enemy_move(game, enemy->x, enemy->y + dy))
	{
		enemy->y += dy;
		return ;
	}
}

static void	add_random_movement(int *dx, int *dy)
{
	int	random;

	random = rand() % 10;
	if (random < 2)
	{
		*dx += (rand() % 3) - 1;
		*dy += (rand() % 3) - 1;
	}
}

static void	get_direction(t_game *game, t_enemy *enemy, int *dx, int *dy)
{
	*dx = 0;
	*dy = 0;
	if (game->player_x > enemy->x)
		*dx = 1;
	else if (game->player_x < enemy->x)
		*dx = -1;
	if (game->player_y > enemy->y)
		*dy = 1;
	else if (game->player_y < enemy->y)
		*dy = -1;
}

void	move_chase_player(t_game *game, t_enemy *enemy)
{
	int	dx;
	int	dy;

	get_direction(game, enemy, &dx, &dy);
	add_random_movement(&dx, &dy);
	try_diagonal_move(game, enemy, dx, dy);
}
