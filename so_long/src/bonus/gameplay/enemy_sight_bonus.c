/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy_sight_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/02 10:44:04 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/02 10:46:20 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static float	get_step_size(float dx, float dy)
{
	if (fabs(dx) > fabs(dy))
		return (fabs(dx));
	return (fabs(dy));
}

bool	check_line_of_sight(t_game *game, t_sight_line *line)
{
	float	dx;
	float	dy;
	float	step;
	int		i;

	dx = line->x2 - line->x1;
	dy = line->y2 - line->y1;
	step = get_step_size(dx, dy);
	dx /= step;
	dy /= step;
	line->x = line->x1;
	line->y = line->y1;
	i = 1;
	while (i <= step)
	{
		if (game->map[(int)line->y][(int)line->x] == '1')
			return (false);
		line->x += dx;
		line->y += dy;
		i++;
	}
	return (true);
}

bool	is_player_in_sight(t_game *game, t_enemy *enemy)
{
	int				dx;
	int				dy;
	t_sight_line	line;

	dx = abs(game->player_x - enemy->x);
	dy = abs(game->player_y - enemy->y);
	if (dx > enemy->sight_range || dy > enemy->sight_range)
		return (false);
	line.x1 = enemy->x;
	line.y1 = enemy->y;
	line.x2 = game->player_x;
	line.y2 = game->player_y;
	return (check_line_of_sight(game, &line));
}
