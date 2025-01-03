/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_background.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/24 11:18:50 by spyun         #+#    #+#                */
/*   Updated: 2024/12/24 12:04:04 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->empty_img)
			{
				if (mlx_image_to_window(game->mlx, game->empty_img,
						x * TILE_SIZE, y * TILE_SIZE) < 0)
					error_exit("Error: Failed to render background", game);
			}
			x++;
		}
		y++;
	}
}

void	init_walls(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == '1' && game->wall_img)
			{
				if (mlx_image_to_window(game->mlx, game->wall_img,
						x * TILE_SIZE, y * TILE_SIZE) < 0)
					error_exit("Error: Failed to render wall", game);
			}
			x++;
		}
		y++;
	}
}
