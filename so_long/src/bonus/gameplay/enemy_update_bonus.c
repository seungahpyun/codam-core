/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy_update_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/24 09:05:45 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/24 10:53:41 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	handle_enemy_collision(t_game *game)
{
	ft_putendl_fd("Game Over! You hit an enemy!", 1);
	cleanup_game(game);
	exit(EXIT_SUCCESS);
}

void	update_enemy(t_game *game)
{
	static int	delay_count = 0;
	int			i;

	if (!game || !game->enemies)
		return ;
	if (check_enemy_collision(game))
		handle_enemy_collision(game);
	delay_count++;
	if (delay_count < ENEMY_MOVE_DELAY)
		return ;
	delay_count = 0;
	i = 0;
	while (i < game->enemy_count)
	{
		move_single_enemy(game, &game->enemies[i]);
		i++;
	}
	if (check_enemy_collision(game))
		handle_enemy_collision(game);
}

static void	init_enemy_position(t_game *game, int x, int y, int index)
{
	game->enemies[index].x = x;
	game->enemies[index].y = y;
	game->enemies[index].dx = 1;
	game->enemies[index].dy = 0;
	game->map[y][x] = '0';
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
	y = -1;
	while (++y < game->height)
	{
		x = -1;
		while (++x < game->width)
		{
			if (game->map[y][x] == 'X')
			{
				if (i >= game->enemy_count)
					return (false);
				init_enemy_position(game, x, y, i++);
			}
		}
	}
	return (i == game->enemy_count);
}
