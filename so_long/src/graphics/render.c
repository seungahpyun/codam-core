/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:52 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/16 16:30:38 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	render_tile(t_game *game, int x, int y, mlx_image_t *img)
{
	if (!game || !img || !img->instances)
		return ;
	img->instances[0].x = x * TILE_SIZE;
	img->instances[0].y = y * TILE_SIZE;
}

static void	render_player(t_game *game)
{
	if (!game || !game->player_img || !game->player_img->instances)
		return ;
	game->player_img->instances[0].x = game->player_x * TILE_SIZE;
	game->player_img->instances[0].y = game->player_y * TILE_SIZE;
}

static void	render_map(t_game *game)
{
	int	x;
	int	y;

	if (!game || !game->map)
		return ;
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

int	render_frame(t_game *game)
{
	if (!game)
		return (0);
	render_map(game);
	if (game->enemy_count > 0)
		render_enemy(game);
	render_player(game);
	display_moves(game);
	return (0);
}
