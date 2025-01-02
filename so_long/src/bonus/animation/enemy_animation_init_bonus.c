/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy_animation_init_bonus.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/31 11:48:19 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/02 09:45:06 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	cleanup_enemy_animation(t_game *game)
{
	t_direction	dir;
	int			i;

	if (!game || !game->mlx)
		return ;
	dir = DIRECTION_UP;
	while (dir <= DIRECTION_RIGHT)
	{
		i = 0;
		while (i < ENEMY_FRAME_COUNT)
		{
			if (game->enemy_frames[i])
				mlx_delete_image(game->mlx, game->enemy_frames[i]);
			i++;
		}
		dir++;
	}
}
