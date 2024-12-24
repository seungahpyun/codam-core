/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_player_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/24 09:12:05 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/24 09:30:23 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	init_player_image(t_game *game)
{
	t_direction	dir;
	int			frame;

	if (!game)
		return ;
	dir = DIRECTION_UP;
	while (dir <= DIRECTION_RIGHT)
	{
		frame = 0;
		while (frame < 4)
		{
			if (game->player.frames[dir][frame])
			{
				if (mlx_image_to_window(game->mlx,
					game->player.frames[dir][frame],
					game->player_x * TILE_SIZE,
					game->player_y * TILE_SIZE) < 0)
					error_exit("Failed to render player frame", game);
				if (dir != game->player.direction || frame != 0)
					game->player.frames[dir][frame]->instances[0].enabled = false;
			}
			frame++;
		}
		dir++;
	}
}

void	update_player(t_game *game)
{
	t_direction	dir;
	int			frame;
	mlx_image_t	*current_sprite;

	if (!game)
		return ;
	dir = DIRECTION_UP;
	while (dir <= DIRECTION_RIGHT)
	{
		frame = 0;
		while (frame < 4)
		{
			if (game->player.frames[dir][frame] &&
				game->player.frames[dir][frame]->instances)
				game->player.frames[dir][frame]->instances[0].enabled = false;
			frame++;
		}
		dir++;
	}
	current_sprite = get_current_player_sprite(game);
	if (current_sprite && current_sprite->instances)
	{
		current_sprite->instances[0].x = game->player_x * TILE_SIZE;
		current_sprite->instances[0].y = game->player_y * TILE_SIZE;
		current_sprite->instances[0].enabled = true;
	}
}
