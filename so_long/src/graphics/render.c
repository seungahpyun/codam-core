/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:52 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/16 10:17:58 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	render_tile(t_game *game, int x, int y, mlx_image_t *img)
{
	(void)game;
	if (img && img->instances)
	{
		img->instances[0].x = x * TILE_SIZE;
		img->instances[0].y = y * TILE_SIZE;
	}
}

static void	render_player(t_game *game)
{
	if(game->player_img && game->player_img->instances)
	{
		game->player_img->instances[0].x = game->player_x * TILE_SIZE;
		game->player_img->instances[0].y = game->player_y * TILE_SIZE;
	}
}

static void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == '1')
				render_tile(game, x, y, game->wall_img);
			else if (game->map[y][x] == 'C')
				render_tile(game, x, y, game->collect_img);
			else if (game->map[y][x] == 'E')
				render_tile(game, x, y, game->exit_img);
			else if (game->map[y][x] == '0')
				render_tile(game, x, y, game->empty_img);
			x++;
		}
		y++;
	}
}

int	render_frame(t_game *game)
{
	render_map(game);
	render_enemy(game);
	render_player(game);
	display_moves(game);
	return (0);
}
