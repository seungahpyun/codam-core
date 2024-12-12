/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:52 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/12 20:07:40 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	render_tile(t_game *game, int x, int y, void *img)
{
	mlx_put_image_to_window(game->mlx, game->window, img, x * 32, y * 32);
}

static void	render_player(t_game *game, int x, int y)
{
	render_tile(game, game->player_x, game->player_y, game->player_img);
}

static void render_map(t_game *game)
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

int render_frame(t_game *game)
{
	render_map(game);
	render_player(game);
	return (0);
}
