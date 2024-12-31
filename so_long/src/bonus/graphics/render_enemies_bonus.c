/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_enemies_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/24 13:34:51 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/31 11:34:39 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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

void	init_enemy_rendering(t_game *game)
{
	int	i;

	if (!game || !game->enemy_img || game->enemy_count <= 0)
		return ;
	i = -1;
	while (++i < game->enemy_count)
	{
		if (mlx_image_to_window(game->mlx, game->enemy_img,
				game->enemies[i].x * TILE_SIZE,
				game->enemies[i].y * TILE_SIZE) < 0)
			error_exit("Failed to initialize enemy rendering", game);
	}
}

void	update_enemy_positions(t_game *game)
{
	int	i;

	if (!game || !game->enemy_img || !game->enemy_img->instances)
		return ;
	i = -1;
	while (++i < game->enemy_count)
	{
		game->enemy_img->instances[i].x = game->enemies[i].x * TILE_SIZE;
		game->enemy_img->instances[i].y = game->enemies[i].y * TILE_SIZE;
	}
}
