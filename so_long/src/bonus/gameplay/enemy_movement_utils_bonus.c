/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy_movement_utils_bonus.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/02 10:03:23 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/02 10:04:03 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	get_random_direction(int *dx, int *dy)
{
	int	direction;

	direction = rand() % 4;
	*dx = 0;
	*dy = 0;
	if (direction == 0)
		*dx = 1;
	else if (direction == 1)
		*dx = -1;
	else if (direction == 2)
		*dy = 1;
	else if (direction == 3)
		*dy = -1;
}

void	get_chase_direction(t_game *game, t_enemy *enemy, int *dx, int *dy)
{
	*dx = 0;
	*dy = 0;
	if (game->player_x > enemy->x)
		*dx = 1;
	else if (game->player_x < enemy->x)
		*dx = -1;
	if (game->player_y > enemy->y)
		*dy = 1;
	else if (game->player_y < enemy->y)
		*dy = -1;
}
