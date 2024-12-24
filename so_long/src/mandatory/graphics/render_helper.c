/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_helper.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/24 11:18:50 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/24 11:19:29 by spyun         ########   odam.nl         */
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
					error_exit("Error\nFailed to render wall", game);
			}
			x++;
		}
		y++;
	}
}

void	init_collectibles_and_exit(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == 'C' && game->collect_img)
			{
				game->collect_instances[y][x] = mlx_image_to_window(game->mlx,
						game->collect_img, x * TILE_SIZE, y * TILE_SIZE);
				if (game->collect_instances[y][x] < 0)
					error_exit("Error: Failed to render collectible", game);
			}
			if (game->map[y][x] == 'E' && game->exit_img)
			{
				if (mlx_image_to_window(game->mlx, game->exit_img,
						x * TILE_SIZE, y * TILE_SIZE) < 0)
					error_exit("Error: Failed to render exit", game);
			}
			x++;
		}
		y++;
	}
}

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
