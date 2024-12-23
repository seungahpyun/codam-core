/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:52 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/23 10:15:41 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
					error_exit("Error: Failed to render background", game);
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
					error_exit("Error\nFailed to render wall", game);
			}
			x++;
		}
		y++;
	}
}

static void	init_collectibles_and_exit(t_game *game)
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

static void	init_player_image(t_game *game)
{
	if (!game || !game->player_img)
		return ;
	if (mlx_image_to_window(game->mlx, game->player_img,
			game->player_x * TILE_SIZE, game->player_y * TILE_SIZE) < 0)
		error_exit("Error: Failed to render player", game);
}

static void	update_player_position(t_game *game)
{
	if (!game || !game->player_img || !game->player_img->instances)
		return ;
	game->player_img->instances[0].x = game->player_x * TILE_SIZE;
	game->player_img->instances[0].y = game->player_y * TILE_SIZE;
}

int	render_frame(t_game *game)
{
	static bool	initialized = false;

	if (!game)
		return (0);
	if (!initialized)
	{
		init_background(game);
		init_walls(game);
		init_collectibles_and_exit(game);
		init_player_image(game);
		initialized = true;
		return (0);
	}
	update_player_position(game);
	return (0);
}
