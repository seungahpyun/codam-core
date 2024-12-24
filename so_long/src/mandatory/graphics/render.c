/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:52 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/24 11:22:09 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	render_frame(t_game *game)
{
	static bool	initialized = false;

	if (!game)
		return (0);
	if (!initialized)
	{
		init_background(game);
		init_walls(game);
		init_collectibles_and_exit(game);
		init_player_image(game);
		initialized = true;
		return (0);
	}
	update_player_position(game);
	return (0);
}
