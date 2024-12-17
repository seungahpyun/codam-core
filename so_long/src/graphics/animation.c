/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   animation.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 11:00:59 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/17 17:20:41 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

static bool	load_direction_frames(t_game *game, t_direction dir,
	const char *base_path)
{
	char	path[256];
	char	num[2];
	int		i;

	i = 0;
	while (i < 4)
	{
		ft_memset(path, 0, sizeof(path));
		ft_strlcpy(path, base_path, sizeof(path));
		ft_strlcat(path, "/", sizeof(path));
		ft_strlcat(path, base_path + ft_strlen("textures/player/"), sizeof(path));
		num[0] = (i + 1) + '0';
		num[1] = '\0';
		ft_strlcat(path, num, sizeof(path));
		ft_strlcat(path, ".png", sizeof(path));

		printf("Loading animation frame: %s\n", path);
		game->player.frames[dir][i] = load_image(game, path);
		if (!game->player.frames[dir][i])
			return (false);
		i++;
	}
	return (true);
}

bool	init_player_animation(t_game *game)
{
	if (!game)
		return (false);
	game->player.current_frame = 0;
	game->player.frame_count = 4;
	game->player.frame_delay = 0;
	game->player.direction = DIRECTION_RIGHT;
	if (!load_direction_frames(game, DIRECTION_RIGHT,
			"textures/player/right"))
		return (false);
	if (!load_direction_frames(game, DIRECTION_LEFT,
			"textures/player/left"))
		return (false);
	if (!load_direction_frames(game, DIRECTION_UP,
			"textures/player/up"))
		return (false);
	if (!load_direction_frames(game, DIRECTION_DOWN,
			"textures/player/down"))
		return (false);
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

void	cleanup_player_animation(t_game *game)
{
	int			i;
	t_direction	dir;

	if (!game || !game->mlx)
		return ;
	dir = DIRECTION_UP;
	while (dir <= DIRECTION_RIGHT)
	{
		i = 0;
		while (i < 4)
		{
			if (game->player.frames[dir][i])
				mlx_delete_image(game->mlx, game->player.frames[dir][i]);
			i++;
		}
		dir++;
	}
}
