/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   animation_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 11:00:59 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/24 09:43:02 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	create_frame_path(char *path, const char *base_path, int frame_num)
{
	ft_memset(path, 0, sizeof(char) * 256);
	ft_strlcpy(path, base_path, 256);
	ft_strlcat(path, "/", 256);
	ft_strlcat(path, base_path + ft_strlen("textures/player/"), 256);
	path[ft_strlen(path)] = frame_num + '1';
	ft_strlcat(path, ".png", 256);
}

bool	load_direction_frames(t_game *game, t_direction dir,
	const char *base_path)
{
	char	path[256];
	int		i;

	i = 0;
	while (i < 4)
	{
		create_frame_path(path, base_path, i);
		game->player.frames[dir][i] = load_image(game, path);
		if (!game->player.frames[dir][i])
			return (false);
		i++;
	}
	return (true);
}

void	update_animation(t_game *game)
{
	if (!game)
		return ;
	game->player.frame_delay++;
	if (game->player.frame_delay >= ANIMATION_SPEED)
	{
		game->player.frame_delay = 0;
		game->player.current_frame++;
		if (game->player.current_frame >= game->player.frame_count)
			game->player.current_frame = 0;
		update_player_position(game);
	}
}

mlx_image_t	*get_current_player_sprite(t_game *game)
{
	if (!game || !game->player.frames[game->player.direction])
		return (NULL);
	return (game->player.frames[game->player.direction]
		[game->player.current_frame]);
}
