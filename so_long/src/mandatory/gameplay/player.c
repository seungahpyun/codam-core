/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:49 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/23 10:13:51 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		if (game->collect_img && game->collect_instances
			&& game->collect_instances[y][x] >= 0)
		{
			game->collect_img
				->instances[game->collect_instances[y][x]].enabled = false;
		}
		ft_putstr_fd("Collected item! Remaining: ", 1);
		ft_putnbr_fd(game->collectibles, 1);
		ft_putchar_fd('\n', 1);
	}
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
	game->moves++;
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(game->moves, 1);
	ft_putchar_fd('\n', 1);
	collect_item(game, new_x, new_y);
	if (check_exit(game, new_x, new_y))
	{
		cleanup_game(game);
		exit(EXIT_SUCCESS);
	}
	game->player_x = new_x;
	game->player_y = new_y;
}

bool	init_player(t_game *game)
{
	if (!game)
		return (false);
	game->moves = 0;
	return (true);
}
