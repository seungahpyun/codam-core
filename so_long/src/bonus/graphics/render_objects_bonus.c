/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_objects_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/24 09:11:36 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/24 13:35:17 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	render_collectible(t_game *game, int x, int y)
{
	if (!game->collect_img)
		return ;
	if (mlx_image_to_window(game->mlx, game->collect_img,
			x * TILE_SIZE, y * TILE_SIZE) < 0)
		error_exit("Failed to render collectible", game);
}

static void	render_exit(t_game *game, int x, int y)
{
	if (!game->exit_img)
		return ;
	if (mlx_image_to_window(game->mlx, game->exit_img,
			x * TILE_SIZE, y * TILE_SIZE) < 0)
		error_exit("Failed to render exit", game);
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
