/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:52 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/17 17:28:32 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

static void	render_tile(t_game *game, int x, int y, mlx_image_t *img)
{
	if (!game || !img)
		return ;

	// Update instance position instead of creating new one
	if (!img->instances)
	{
		if (mlx_image_to_window(game->mlx, img, x * TILE_SIZE, y * TILE_SIZE) < 0)
		{
			printf("Failed to render tile at x:%d, y:%d\n", x, y);
			return ;
		}
	}
	else
	{
		img->instances[0].x = x * TILE_SIZE;
		img->instances[0].y = y * TILE_SIZE;
	}
}

static void	render_map(t_game *game)
{
	int	x;
	int	y;

	if (!game || !game->map)
		return ;

	printf("Rendering map...\n");
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == '1' && game->wall_img)
				render_tile(game, x, y, game->wall_img);
			else if (game->map[y][x] == 'C' && game->collect_img)
				render_tile(game, x, y, game->collect_img);
			else if (game->map[y][x] == 'E' && game->exit_img)
				render_tile(game, x, y, game->exit_img);
			else if (game->map[y][x] == '0' && game->empty_img)
				render_tile(game, x, y, game->empty_img);
			x++;
		}
		y++;
	}
}

static void	render_player(t_game *game)
{
	mlx_image_t *current_frame;

	if (!game)
		return ;

	current_frame = get_current_player_sprite(game);
	if (!current_frame)
		return ;

	if (!current_frame->instances)
	{
		if (mlx_image_to_window(game->mlx, current_frame,
			game->player_x * TILE_SIZE, game->player_y * TILE_SIZE) < 0)
		{
			printf("Failed to render player\n");
			return ;
		}
	}
	else
	{
		current_frame->instances[0].x = game->player_x * TILE_SIZE;
		current_frame->instances[0].y = game->player_y * TILE_SIZE;
	}
}

int	render_frame(t_game *game)
{
	if (!game)
		return (0);

	printf("Starting frame render\n");
	render_map(game);

	if (game->enemy_count > 0)
		render_enemy(game);
	render_player(game);
	display_moves(game);

	printf("Frame render complete\n");
	return (0);
}
