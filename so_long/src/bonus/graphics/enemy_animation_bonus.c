/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy_animation_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/31 11:45:37 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/31 12:09:51 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	create_enemy_frame_path(char *path, int frame_num)
{
	ft_memset(path, 0, sizeof(char) * 256);
	ft_strlcpy(path, "textures/enemy/right", 256);
	path[ft_strlen(path)] = frame_num + '1';
	ft_strlcat(path, ".png", 256);
}

bool	load_enemy_frames(t_game *game)
{
	char	path[256];
	int		i;

	i = 0;
	while (i < ENEMY_FRAME_COUNT)
	{
		create_enemy_frame_path(path, i);
		game->enemy_frames[i] = load_image(game, path);
		if (!game->enemy_frames[i])
			return (false);
		i++;
	}
	return (true);
}

void	update_enemy_animation(t_game *game)
{
	int	i;

	if (!game)
		return ;
	i = 0;
	while (i < game->enemy_count)
	{
		game->enemies[i].frame_delay++;
		if (game->enemies[i].frame_delay >= ANIMATION_SPEED)
		{
			game->enemies[i].frame_delay = 0;
			game->enemies[i].current_frame++;
			if (game->enemies[i].current_frame >= ENEMY_FRAME_COUNT)
				game->enemies[i].current_frame = 0;
		}
		i++;
	}
}

mlx_image_t	*get_current_enemy_sprite(t_game *game, int enemy_index)
{
	if (!game || enemy_index >= game->enemy_count)
		return (NULL);
	return (game->enemy_frames[game->enemies[enemy_index].current_frame]);
}
