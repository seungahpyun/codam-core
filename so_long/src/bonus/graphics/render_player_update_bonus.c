/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_player_update_bonus.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/24 09:12:05 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/24 13:37:03 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	disable_frame(t_game *game, t_direction dir, int frame)
{
	if (game->player.frames[dir][frame]
		&& game->player.frames[dir][frame]->instances)
		game->player.frames[dir][frame]->instances[0].enabled = false;
}

static void	disable_all_frames(t_game *game)
{
	t_direction	dir;
	int			frame;

	dir = DIRECTION_UP;
	while (dir <= DIRECTION_RIGHT)
	{
		frame = 0;
		while (frame < 4)
		{
			disable_frame(game, dir, frame);
			frame++;
		}
		dir++;
	}
}

void	update_player(t_game *game)
{
	mlx_image_t	*current_sprite;

	if (!game)
		return ;
	disable_all_frames(game);
	current_sprite = get_current_player_sprite(game);
	if (current_sprite && current_sprite->instances)
	{
		current_sprite->instances[0].x = game->player_x * TILE_SIZE;
		current_sprite->instances[0].y = game->player_y * TILE_SIZE;
		current_sprite->instances[0].enabled = true;
	}
}
