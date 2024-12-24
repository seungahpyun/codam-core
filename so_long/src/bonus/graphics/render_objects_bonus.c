/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_objects_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/24 09:11:36 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/24 11:12:21 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
				if (mlx_image_to_window(game->mlx, game->collect_img,
						x * TILE_SIZE, y * TILE_SIZE) < 0)
					error_exit("Failed to render collectible", game);
			}
			if (game->map[y][x] == 'E' && game->exit_img)
			{
				if (mlx_image_to_window(game->mlx, game->exit_img,
						x * TILE_SIZE, y * TILE_SIZE) < 0)
					error_exit("Failed to render exit", game);
			}
			x++;
		}
		y++;
	}
}

void	init_enemies(t_game *game)
{
	int	i;

	if (!game->enemy_img || game->enemy_count <= 0)
		return ;
	i = 0;
	while (i < game->enemy_count)
	{
		if (mlx_image_to_window(game->mlx, game->enemy_img,
				game->enemies[i].x * TILE_SIZE,
				game->enemies[i].y * TILE_SIZE) < 0)
			error_exit("Failed to render enemy", game);
		i++;
	}
}

void	update_collectibles(t_game *game)
{
	int		x;
	int		y;
	size_t	i;
	size_t	instance_index;

	if (!game || !game->collect_img || !game->collect_img->instances)
		return ;
	i = 0;
	while (i < game->collect_img->count)
		game->collect_img->instances[i++].enabled = false;
	y = 0;
	instance_index = 0;
	while (y < game->height && instance_index < game->collect_img->count)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == 'C')
			{
				game->collect_img->instances[instance_index].x = x * TILE_SIZE;
				game->collect_img->instances[instance_index].y = y * TILE_SIZE;
				game->collect_img->instances[instance_index++].enabled = true;
			}
			x++;
		}
		y++;
	}
}
