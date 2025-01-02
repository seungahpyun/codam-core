/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 11:01:05 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/02 09:34:22 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static bool	is_valid_move(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->width || y >= game->height)
		return (false);
	if (game->map[y][x] == '1' || game->map[y][x] == 'C'
		|| game->map[y][x] == 'E')
		return (false);
	return (true);
}

static void	reverse_enemy_direction(t_enemy *enemy)
{
	enemy->dx *= -1;
	enemy->dy *= -1;
}

void	move_single_enemy(t_game *game, t_enemy *enemy)
{
	int	next_x;
	int	next_y;

	next_x = enemy->x + enemy->dx;
	next_y = enemy->y + enemy->dy;
	if (!is_valid_move(game, next_x, next_y))
	{
		reverse_enemy_direction(enemy);
		return ;
	}
	enemy->x = next_x;
	enemy->y = next_y;
}

void	render_enemy(t_game *game)
{
	int	i;

	if (!game || !game->enemy_img || !game->enemy_img->instances)
		return ;
	i = 0;
	while (i < game->enemy_count)
	{
		game->enemy_img->instances[i].x = game->enemies[i].x * TILE_SIZE;
		game->enemy_img->instances[i].y = game->enemies[i].y * TILE_SIZE;
		i++;
	}
}

bool	check_enemy_collision(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		if (game->player_x == game->enemies[i].x
			&& game->player_y == game->enemies[i].y)
			return (true);
		i++;
	}
	return (false);
}
