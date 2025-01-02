/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_lifecycle_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:00:14 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/02 09:53:51 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	process_movement(t_game *game, int new_x, int new_y)
{
	if (new_x != game->player_x || new_y != game->player_y)
		move_player(game, new_x, new_y);
}

static void	handle_key_press(mlx_key_data_t keydata, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x;
	new_y = game->player_y;
	if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		new_y--;
	else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		new_y++;
	else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		new_x--;
	else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		new_x++;
	process_movement(game, new_x, new_y);
}

void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game || !game->mlx)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		cleanup_game(game);
		exit(EXIT_SUCCESS);
	}
	if (keydata.action == MLX_PRESS)
		handle_key_press(keydata, game);
}

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game)
		return ;
	update_animation(game);
	if (game->enemy_count > 0 && game->enemies)
	{
		update_enemy(game);
		update_enemy_animation(game);
	}
	render_frame(game);
}

bool	init_game(t_game *game, char *file)
{
	if (!game || !file)
		return (false);
	if (!parse_map(game, file))
		return (false);
	if (!init_mlx_window(game))
		return (false);
	if (!init_game_components(game))
	{
		cleanup_game(game);
		return (false);
	}
	mlx_key_hook(game->mlx, &key_handler, game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	return (true);
}
