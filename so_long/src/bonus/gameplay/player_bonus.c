/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_bonus.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:49 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/24 09:35:46 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void    update_player_position(t_game *game)
{
    if (!game || !game->player_img || !game->player_img->instances)
        return ;
    game->player_img->instances[0].x = game->player_x * TILE_SIZE;
    game->player_img->instances[0].y = game->player_y * TILE_SIZE;
}

bool    init_player(t_game *game)
{
    if (!game)
        return (false);
    game->player.direction = DIRECTION_RIGHT;
    game->player.current_frame = 0;
    game->player.frame_count = 4;
    game->player.frame_delay = 0;
    game->moves = 0;
    return (true);
}
