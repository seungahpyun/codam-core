/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_bonus.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:52 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/24 11:13:31 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	init_background(t_game *game)
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
					error_exit("Failed to render background", game);
			}
			x++;
		}
		y++;
	}
}

static void	init_walls(t_game *game)
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
					error_exit("Failed to render wall", game);
			}
			x++;
		}
		y++;
	}
}

void	init_images(t_game *game)
{
	init_background(game);
	init_walls(game);
	init_collectibles_and_exit(game);
	init_player_image(game);
	if (game->enemy_count > 0)
		render_enemy(game);
}

int	render_frame(t_game *game)
{
	static bool	initialized = false;

	if (!game)
		return (0);
	if (!initialized)
	{
		init_images(game);
		initialized = true;
		return (0);
	}
	update_player(game);
	if (game->enemy_count > 0)
		update_enemy(game);
	update_collectibles(game);
	display_moves(game);
	return (0);
}
