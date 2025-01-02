/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_enemies_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/24 13:34:51 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/02 10:00:42 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	init_enemies(t_game *game)
{
	int			i;
	mlx_image_t	*frame;

	if (!game || game->enemy_count <= 0)
		return ;
	i = 0;
	while (i < game->enemy_count)
	{
		frame = game->enemy_frames[0];
		if (!frame || mlx_image_to_window(game->mlx, frame,
				game->enemies[i].x * TILE_SIZE,
				game->enemies[i].y * TILE_SIZE) < 0)
			error_exit("Failed to render enemy", game);
		i++;
	}
}

void	init_enemy_rendering(t_game *game)
{
	int			i;
	mlx_image_t	*frame;
	int			j;

	if (!game || game->enemy_count <= 0)
		return ;
	j = 0;
	while (j < ENEMY_FRAME_COUNT)
	{
		frame = game->enemy_frames[j];
		if (!frame)
			error_exit("Enemy frame not loaded", game);
		i = 0;
		while (i < game->enemy_count)
		{
			if (mlx_image_to_window(game->mlx, frame,
					game->enemies[i].x * TILE_SIZE,
					game->enemies[i].y * TILE_SIZE) < 0)
				error_exit("Failed to initialize enemy rendering", game);
			if (j != 0)
				frame->instances[i].enabled = false;
			i++;
		}
		j++;
	}
}

void	update_enemy_positions(t_game *game)
{
	int			i;
	int			j;
	mlx_image_t	*frame;

	if (!game || game->enemy_count <= 0)
		return ;
	i = 0;
	while (i < game->enemy_count)
	{
		j = 0;
		while (j < ENEMY_FRAME_COUNT)
		{
			frame = game->enemy_frames[j];
			if (frame && frame->instances)
			{
				frame->instances[i].x = game->enemies[i].x * TILE_SIZE;
				frame->instances[i].y = game->enemies[i].y * TILE_SIZE;
				frame->instances[i].enabled
					= (j == game->enemies[i].current_frame);
			}
			j++;
		}
		i++;
	}
}
