/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   animation.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 11:00:59 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/13 15:29:36 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	init_player_animation(t_game *game)
{
	game->player.current_frame = 0;
	game->player.frame_count = 4;
	game->player.frame_delay = 0;
	game->player.direction = DIRECTION_RIGHT;
	game->player.frames[DIRECTION_RIGHT][0] = load_image(game,
			"textures/player_right1.xpm");
	game->player.frames[DIRECTION_RIGHT][1] = load_image(game,
			"textures/player_right2.xpm");
	game->player.frames[DIRECTION_RIGHT][2] = load_image(game,
			"textures/player_right3.xpm");
	game->player.frames[DIRECTION_RIGHT][3] = load_image(game,
			"textures/player_right4.xpm");
	game->player.frames[DIRECTION_LEFT][0] = load_image(game,
			"textures/player_left1.xpm");
	game->player.frames[DIRECTION_LEFT][1] = load_image(game,
			"textures/player_left2.xpm");
	game->player.frames[DIRECTION_LEFT][2] = load_image(game,
			"textures/player_left3.xpm");
	game->player.frames[DIRECTION_LEFT][3] = load_image(game,
			"textures/player_left4.xpm");
	game->player.frames[DIRECTION_UP][0] = load_image(game,
			"textures/player_up1.xpm");
	game->player.frames[DIRECTION_UP][1] = load_image(game,
			"textures/player_up2.xpm");
	game->player.frames[DIRECTION_UP][2] = load_image(game,
			"textures/player_up3.xpm");
	game->player.frames[DIRECTION_UP][3] = load_image(game,
			"textures/player_up4.xpm");
	game->player.frames[DIRECTION_DOWN][0] = load_image(game,
			"textures/player_down1.xpm");
	game->player.frames[DIRECTION_DOWN][1] = load_image(game,
			"textures/player_down2.xpm");
	game->player.frames[DIRECTION_DOWN][2] = load_image(game,
			"textures/player_down3.xpm");
	game->player.frames[DIRECTION_DOWN][3] = load_image(game,
			"textures/player_down4.xpm");
}

void	update_animation(t_game *game)
{
	game->player.frame_delay++;
	if (game->player.frame_delay >= ANIMATION_SPEED)
	{
		game->player.frame_delay = 0;
		game->player.current_frame++;
		if (game->player.current_frame >= game->player.frame_count)
			game->player.current_frame = 0;
	}
}

void	*get_current_player_sprite(t_game *game)
{
	return (game->player.frames[game->player.direction]
		[game->player.current_frame]);
}
