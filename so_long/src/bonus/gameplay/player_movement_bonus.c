/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_movement_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/24 09:07:07 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/24 11:01:07 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static bool	is_valid_move(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_y < 0 || new_x >= game->width || new_y >= game->height)
		return (false);
	if (game->map[new_y][new_x] == '1')
		return (false);
	return (true);
}

static void	collect_item(t_game *game, int x, int y)
{
	if (!game || !game->map)
		return ;
	if (game->map[y][x] == 'C')
	{
		game->collectibles--;
		game->map[y][x] = '0';
		ft_putstr_fd("Collected item! Remaining: ", 1);
		ft_putnbr_fd(game->collectibles, 1);
		ft_putchar_fd('\n', 1);
	}
}

static void	update_player_direction(t_game *game, int new_x, int new_y)
{
	if (!game)
		return ;
	if (new_x > game->player_x)
		game->player.direction = DIRECTION_RIGHT;
	else if (new_x < game->player_x)
		game->player.direction = DIRECTION_LEFT;
	else if (new_y > game->player_y)
		game->player.direction = DIRECTION_DOWN;
	else if (new_y < game->player_y)
		game->player.direction = DIRECTION_UP;
}

static bool	check_exit(t_game *game, int x, int y)
{
	if (!game || !game->map)
		return (false);
	if (game->map[y][x] == 'E')
	{
		if (game->collectibles == 0)
		{
			ft_putendl_fd("Congratulations! Game Complete!", 1);
			return (true);
		}
		ft_putstr_fd("Collect all items first! Remaining: ", 1);
		ft_putnbr_fd(game->collectibles, 1);
		ft_putchar_fd('\n', 1);
	}
	return (false);
}

void	move_player(t_game *game, int new_x, int new_y)
{
	if (!game || !is_valid_move(game, new_x, new_y))
		return ;
	update_player_direction(game, new_x, new_y);
	game->moves++;
	display_moves(game);
	collect_item(game, new_x, new_y);
	if (check_exit(game, new_x, new_y))
	{
		cleanup_game(game);
		exit(EXIT_SUCCESS);
	}
	if (check_enemy_collision(game))
	{
		ft_putendl_fd("Game Over! You hit an enemy!", 1);
		cleanup_game(game);
		exit(EXIT_SUCCESS);
	}
	game->player_x = new_x;
	game->player_y = new_y;
}
