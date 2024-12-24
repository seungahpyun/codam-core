/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_objects.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/24 11:18:50 by spyun         #+#    #+#                */
/*   Updated: 2024/12/24 12:04:04 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	render_collectible(t_game *game, int x, int y)
{
	if (!game->collect_img)
		return ;
	game->collect_instances[y][x] = mlx_image_to_window(game->mlx,
			game->collect_img, x * TILE_SIZE, y * TILE_SIZE);
	if (game->collect_instances[y][x] < 0)
		error_exit("Error: Failed to render collectible", game);
}

static void	render_exit(t_game *game, int x, int y)
{
	if (!game->exit_img)
		return ;
	if (mlx_image_to_window(game->mlx, game->exit_img,
			x * TILE_SIZE, y * TILE_SIZE) < 0)
		error_exit("Error: Failed to render exit", game);
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
			if (game->map[y][x] == 'C')
				render_collectible(game, x, y);
			if (game->map[y][x] == 'E')
				render_exit(game, x, y);
			x++;
		}
		y++;
	}
}
