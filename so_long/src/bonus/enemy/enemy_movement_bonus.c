/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy_movement_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/31 10:50:38 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/02 14:02:43 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static bool	is_valid_enemy_move(t_game *game, int x, int y)
{
	int	i;

	if (x < 0 || y < 0 || x >= game->width || y >= game->height)
		return (false);
	if (game->map[y][x] == '1' || game->map[y][x] == 'E'
		|| game->map[y][x] == 'C')
		return (false);
	i = 0;
	while(i < game->enemy_count)
	{
		if (game->enemies[i].x == x && game->enemies[i].y == y)
			return (false);
		i++;
	}
	return (true);
}

static void	try_alternative_move(t_game *game, t_enemy *enemy)
{
	const int	dx[] = {0, 1, 0, -1};
	const int	dy[] = {-1, 0, 1, 0};
	int			i;
	int			dir;

	i = rand() % 4;
	dir = 0;
	while (dir < 4)
	{
		if (is_valid_enemy_move(game,
				enemy->x + dx[(i + dir) % 4],
				enemy->y + dy[(i + dir) % 4]))
		{
			enemy->x += dx[(i + dir) % 4];
			enemy->y += dy[(i + dir) % 4];
			return ;
		}
		dir++;
	}
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
		return ;
	}
	try_alternative_move(game, enemy);
}

void	move_chase_player(t_game *game, t_enemy *enemy)
{
	int	dx;
	int	dy;

	dx = 0;
	dy = 0;
	if (is_player_in_sight(game, enemy))
	{
		get_chase_direction(game, enemy, &dx, &dy);
		try_move(game, enemy, dx, dy);
	}
	else
	{
		get_random_direction(&dx, &dy);
		try_move(game, enemy, dx, dy);
	}
}
