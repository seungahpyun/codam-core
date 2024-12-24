/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_player.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/24 11:18:50 by spyun         #+#    #+#                */
/*   Updated: 2024/12/24 12:04:04 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_player_image(t_game *game)
{
	if (!game || !game->player_img)
		return ;
	if (mlx_image_to_window(game->mlx, game->player_img,
			game->player_x * TILE_SIZE, game->player_y * TILE_SIZE) < 0)
		error_exit("Error: Failed to render player", game);
}

void	update_player_position(t_game *game)
{
	if (!game || !game->player_img || !game->player_img->instances)
		return ;
	game->player_img->instances[0].x = game->player_x * TILE_SIZE;
	game->player_img->instances[0].y = game->player_y * TILE_SIZE;
}
