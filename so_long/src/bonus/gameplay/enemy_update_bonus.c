/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy_update_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/24 09:05:45 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/02 09:34:30 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	update_enemy(t_game *game)
{
	static double	last_move = -1.0;
	double			current_time;
	int				i;

	if (!game || !game->enemies || game->enemy_count <= 0)
		return ;
	current_time = mlx_get_time();
	if (last_move < 0.0)
	{
		last_move = current_time;
		return ;
	}
	if (current_time - last_move < 1.0)
		return ;
	i = -1;
	while (++i < game->enemy_count)
		move_chase_player(game, &game->enemies[i]);
	update_enemy_positions(game);
	last_move = current_time;
}

static void	init_enemy_properties(t_enemy *enemy)
{
	enemy->move_delay = 0;
	enemy->sight_range = 5;
	enemy->type = CHASE_PLAYER;
	enemy->dx = 0;
	enemy->dy = 0;
	enemy->current_frame = 0;
	enemy->frame_delay = 0;
}

void	init_enemy_positions(t_game *game)
{
	int	x;
	int	y;
	int	count;

	y = -1;
	count = 0;
	while (++y < game->height)
	{
		x = -1;
		while (++x < game->width)
		{
			if (game->map[y][x] == 'X' && count < game->enemy_count)
			{
				game->enemies[count].x = x;
				game->enemies[count].y = y;
				init_enemy_properties(&game->enemies[count]);
				game->map[y][x] = '0';
				count++;
			}
		}
	}
}

bool	init_enemy(t_game *game)
{
	if (!game || game->enemy_count <= 0)
		return (true);
	game->enemies = malloc(sizeof(t_enemy) * game->enemy_count);
	if (!game->enemies)
		return (false);
	if (!load_enemy_frames(game))
	{
		free(game->enemies);
		game->enemies = NULL;
		return (false);
	}
	init_enemy_positions(game);
	return (true);
}
