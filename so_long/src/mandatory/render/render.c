/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:52 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/06 08:58:38 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	render_frame(t_game *game)
{
	static bool	initialized = false;

	if (!game)
		return (false);
	if (!initialized)
	{
		init_background(game);
		init_walls(game);
		init_collectibles_and_exit(game);
		init_player_image(game);
		initialized = true;
		return (true);
	}
	update_player_position(game);
	return (true);
}
