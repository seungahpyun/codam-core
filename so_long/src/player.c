/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:49 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/12 20:31:40 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	check_collision(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == '1')
		return (1);
	return (0);
}

static void	collect_item(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'C')
	{
		game->collectibles--;
		game->map[y][x] = '0';
	}
}

static int	check_exit(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'E')
	{
		if (game->collectibles == 0)
			return (1);
	}
	return (0);
}

static void	move_player(t_game *game, int new_x, int new_y)
{
	if (check_collision(game, new_x, new_y))
		return ;
	game->moves++;
	ft_putnbr_fd(game->moves, 1);
	ft_putchar_fd('\n', 1);
	if (check_exit(game, new_x, new_y))
	{
		ft_putendl_fd("Game Complete!", 1);
		exit_game(game, 0);
	}
	collect_item(game, new_x, new_y);
	game->player_x = new_x;
	game->player_y = new_y;
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit_game(game, 0);
	else if (keycode == KEY_W || keycode == KEY_UP)
		move_player(game, game->player_x, game->player_y - 1);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		move_player(game, game->player_x, game->player_y + 1);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		move_player(game, game->player_x - 1, game->player_y);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		move_player(game, game->player_x + 1, game->player_y);
	return (0);
}
