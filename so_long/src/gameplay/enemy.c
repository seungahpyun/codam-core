/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 11:01:05 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/16 10:20:45 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	game_over(t_game *game)
{
	ft_putendl_fd("Game Over! You hit an enemy!", 1);
	exit_game(game, 0);
}

void	render_enemy(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemy_img && game->enemy_img->instances)
		{
			game->enemy_img->instances[i].x = game->enemies[i].x * TILE_SIZE;
			game->enemy_img->instances[i].y = game->enemies[i].y * TILE_SIZE;
		}
		i++;
	}
}

static void	move_enemy(t_game *game, t_enemy *enemy)
{
	int	next_x;
	int	next_y;

	next_x = enemy->x + enemy->dx;
	next_y = enemy->y + enemy->dy;
	if (game->map[next_y][next_x] == '1' ||
		game->map[next_y][next_x] == 'C' ||
		game->map[next_y][next_x] == 'E')
	{
		enemy->dx *= -1;
		enemy->dy *= -1;
		return ;
	}
	enemy->x = next_x;
	enemy->y = next_y;
}

void	update_enemy(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		move_enemy(game, &game->enemies[i]);
		if (game->player_x == game->enemies[i].x &&
			game->player_y == game->enemies[i].y)
			game_over(game);
		i++;
	}
}

int	init_enemy(t_game *game)
{
	int	i;
	int	x;
	int	y;

	game->enemies = malloc(sizeof(t_enemy) * game->enemy_count);
	if (!game->enemies)
		return (0);
	i = 0;
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == 'X')
			{
				game->enemies[i].x = x;
				game->enemies[i].y = y;
				game->enemies[i].dx = 1;
				game->enemies[i].dy = 0;
				game->map[y][x] = '0';
				i++;
			}
			x++;
		}
		y++;
	}
	return (1);
}
