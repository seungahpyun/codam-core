/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:49 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/23 08:41:11 by spyun         ########   odam.nl         */
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

static bool check_enemy_collision(t_game *game, int x, int y)
{
	int	i;

	if (!game || !game->enemies)
		return (false);
	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].x == x && game->enemies[i].y == y)
		{
			ft_putendl_fd("Game Over! You hit an enemy!", 1);
			return (true);
		}
		i++;
	}
	return (false);
}


void    move_player(t_game *game, int new_x, int new_y)
{
	if (!game || !is_valid_move(game, new_x, new_y))
		return ;
	if (check_enemy_collision(game, new_x, new_y))
	{
		cleanup_game(game);
		exit(EXIT_SUCCESS);
	}
	update_player_direction(game, new_x, new_y);
	game->moves++;
	display_moves(game);
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
	game->player.direction = DIRECTION_RIGHT;
	game->player.current_frame = 0;
	game->player.frame_count = 4;
	game->player.frame_delay = 0;
	game->moves = 0;
	return (true);
}

void	update_player_position(t_game *game)
{
	if (!game || !game->player_img || !game->player_img->instances)
		return ;
	game->player_img->instances[0].x = game->player_x * TILE_SIZE;
	game->player_img->instances[0].y = game->player_y * TILE_SIZE;
}
