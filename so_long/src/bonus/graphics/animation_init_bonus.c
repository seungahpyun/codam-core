/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   animation_init_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/24 09:10:28 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/24 09:30:13 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static bool	init_player_direction(t_game *game, t_direction dir,
	const char *direction)
{
	char	base_path[256];

	ft_memset(base_path, 0, sizeof(base_path));
	ft_strlcpy(base_path, "textures/player/", sizeof(base_path));
	ft_strlcat(base_path, direction, sizeof(base_path));
	return (load_direction_frames(game, dir, base_path));
}

bool	init_player_animation(t_game *game)
{
	if (!game)
		return (false);
	game->player.current_frame = 0;
	game->player.frame_count = 4;
	game->player.frame_delay = 0;
	game->player.direction = DIRECTION_RIGHT;
	if (!init_player_direction(game, DIRECTION_RIGHT, "right"))
		return (false);
	if (!init_player_direction(game, DIRECTION_LEFT, "left"))
		return (false);
	if (!init_player_direction(game, DIRECTION_UP, "up"))
		return (false);
	if (!init_player_direction(game, DIRECTION_DOWN, "down"))
		return (false);
	return (true);
}

void	cleanup_player_animation(t_game *game)
{
	t_direction	dir;
	int			i;

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
