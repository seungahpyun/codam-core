/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_enemies_utils_bonus.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/31 11:35:04 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/31 11:35:11 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	reset_collectible_instances(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->collect_img->count)
		game->collect_img->instances[i++].enabled = false;
}

static void	update_instance(t_game *game, int x, int y, size_t *idx)
{
	game->collect_img->instances[*idx].x = x * TILE_SIZE;
	game->collect_img->instances[*idx].y = y * TILE_SIZE;
	game->collect_img->instances[*idx].enabled = true;
	(*idx)++;
}

void	update_collectibles(t_game *game)
{
	int		x;
	int		y;
	size_t	instance_index;

	if (!game || !game->collect_img || !game->collect_img->instances)
		return ;
	reset_collectible_instances(game);
	y = 0;
	instance_index = 0;
	while (y < game->height && instance_index < game->collect_img->count)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == 'C')
				update_instance(game, x, y, &instance_index);
			x++;
		}
		y++;
	}
}
