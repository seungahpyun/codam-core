/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_player_init_bonus.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/24 13:36:27 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/29 12:41:02 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	render_player_frame(t_game *game, t_direction dir, int frame)
{
	if (!game->player.frames[dir][frame])
		return ;
	if (mlx_image_to_window(game->mlx,
			game->player.frames[dir][frame],
		game->player_x * TILE_SIZE,
		game->player_y * TILE_SIZE) < 0)
		error_exit("Failed to render player frame", game);
}

static void	set_frame_visibility(t_game *game, t_direction dir, int frame)
{
	if (!game->player.frames[dir][frame])
		return ;
	if (dir != game->player.direction || frame != 0)
		game->player.frames[dir][frame]->instances[0].enabled = false;
}

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
			render_player_frame(game, dir, frame);
			set_frame_visibility(game, dir, frame);
			frame++;
		}
		dir++;
	}
}
