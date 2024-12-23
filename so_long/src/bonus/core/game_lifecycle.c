/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_lifecycle.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:00:14 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/23 08:53:07 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
static void	free_textures(t_game *game)
{
	if (!game || !game->mlx)
		return ;
	cleanup_player_animation(game);
	if (game->wall_img)
		mlx_delete_image(game->mlx, game->wall_img);
	if (game->collect_img)
		mlx_delete_image(game->mlx, game->collect_img);
	if (game->exit_img)
		mlx_delete_image(game->mlx, game->exit_img);
	if (game->empty_img)
		mlx_delete_image(game->mlx, game->empty_img);
	if (game->enemy_img)
		mlx_delete_image(game->mlx, game->enemy_img);
	if (game->moves_text)
		mlx_delete_image(game->mlx, game->moves_text);
}

static void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	int		new_x;
	int		new_y;

	game = (t_game *)param;
	if (!game || !game->mlx)
		return ;
	new_x = game->player_x;
	new_y = game->player_y;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		cleanup_game(game);
		exit(EXIT_SUCCESS);
	}
	else if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		&& keydata.action == MLX_PRESS)
		new_y--;
	else if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		&& keydata.action == MLX_PRESS)
		new_y++;
	else if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		&& keydata.action == MLX_PRESS)
		new_x--;
	else if ((keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		&& keydata.action == MLX_PRESS)
		new_x++;
	if (new_x != game->player_x || new_y != game->player_y)
		move_player(game, new_x, new_y);
}

static void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game)
		return ;
	update_animation(game);
	if (game->enemy_count > 0)
		update_enemy(game);
	render_frame(game);
}

bool	init_game(t_game *game, char *file)
{
	if (!game || !file)
		return (false);
	if (!parse_map(game, file))
		return (false);
	game->mlx = mlx_init(game->width * TILE_SIZE,
			game->height * TILE_SIZE, "so_long", true);
	if (!game->mlx)
		return (false);
	load_textures(game);
	if (!init_player(game))
		return (false);
	if (!init_player_animation(game))
	{
		cleanup_game(game);
		return (false);
	}
	if (game->enemy_count > 0 && !init_enemy(game))
	{
		cleanup_game(game);
		return (false);
	}
	mlx_key_hook(game->mlx, &key_handler, game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	return (true);
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->enemies)
	{
		free(game->enemies);
		game->enemies = NULL;
	}
	if (game->map)
	{
		free_allocated_map(game, game->height);
		game->map = NULL;
	}
	if (game->mlx)
	{
		free_textures(game);
		mlx_terminate(game->mlx);
		game->mlx = NULL;
	}
}
