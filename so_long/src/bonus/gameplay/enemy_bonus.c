/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 11:01:05 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/23 08:40:31 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

# define ENEMY_MOVE_DELAY 30

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

static void	move_single_enemy(t_game *game, t_enemy *enemy)
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

void	update_enemy(t_game *game)
{
	static int	delay_count = 0;
	int			i;

	if (!game || !game->enemies)
		return ;
	i = 0;
	while (i < game->enemy_count)
	{
		if (game->player_x == game->enemies[i].x &&
			game->player_y == game->enemies[i].y)
		{
			ft_putendl_fd("Game Over! You hit an enemy!", 1);
			cleanup_game(game);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	delay_count++;
	if (delay_count < ENEMY_MOVE_DELAY)
		return ;
	delay_count = 0;
	i = 0;
	while (i < game->enemy_count)
	{
		move_single_enemy(game, &game->enemies[i]);
		if (game->player_x == game->enemies[i].x &&
			game->player_y == game->enemies[i].y)
		{
			ft_putendl_fd("Game Over! You hit an enemy!", 1);
			cleanup_game(game);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
}

bool	init_enemy(t_game *game)
{
	int	i;
	int	x;
	int	y;

	if (!game || game->enemy_count <= 0)
		return (true);
	game->enemies = malloc(sizeof(t_enemy) * game->enemy_count);
	if (!game->enemies)
		return (false);
	i = 0;
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == 'X')
			{
				if (i >= game->enemy_count)
					return (false);
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
	return (i == game->enemy_count);
}
