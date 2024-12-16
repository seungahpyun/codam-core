/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_lifecycle.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:00:14 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/16 12:14:01 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_textures(t_game *game)
{
	if (!game)
		return ;
	if (game->wall_img)
		mlx_delete_image(game->mlx, game->wall_img);
	if (game->player_img)
		mlx_delete_image(game->mlx, game->player_img);
	if (game->collect_img)
		mlx_delete_image(game->mlx, game->collect_img);
	if (game->exit_img)
		mlx_delete_image(game->mlx, game->exit_img);
	if (game->empty_img)
		mlx_delete_image(game->mlx, game->empty_img);
	if (game->enemy_img)
		mlx_delete_image(game->mlx, game->enemy_img);
}

static void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game)
		return ;
	render_frame(game);
}

static void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	else if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		&& keydata.action == MLX_PRESS)
		move_player(game, game->player_x, game->player_y - 1);
	else if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		&& keydata.action == MLX_PRESS)
		move_player(game, game->player_x, game->player_y + 1);
	else if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		&& keydata.action == MLX_PRESS)
		move_player(game, game->player_x - 1, game->player_y);
	else if ((keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		&& keydata.action == MLX_PRESS)
		move_player(game, game->player_x + 1, game->player_y);
}

int	init_game(t_game *game, char *file)
{
	if (!game || !file)
		return (0);
	ft_memset(game, 0, sizeof(t_game));
	game->width = 0;
	game->height = 0;
	game->moves = 0;
	game->collectibles = 0;
	game->enemy_count = 0;
	game->map = NULL;
	game->mlx = NULL;
	if (!parse_map(game, file))
	{
		ft_putendl_fd("Error: Failed to parse map", 2);
		return (0);
	}
	game->mlx = mlx_init(game->width * TILE_SIZE, game->height * TILE_SIZE,
		"so_long", true);
	if (!game->mlx)
		return (0);
	load_textures(game);
	mlx_key_hook(game->mlx, key_handler, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_close_hook(game->mlx, (mlx_closefun)close_game, game);
	return (1);
}

void	exit_game(t_game *game, int status)
{
	int	i;

	i = 0;
	if (game->map)
	{
		while (i < game->height)
		{
			if (game->map[i])
				free(game->map[i]);
			i++;
		}
		free(game->map);
	}
	if (game->mlx)
	{
		free_textures(game);
		mlx_terminate(game->mlx);
	}
	exit(status);
}

int	close_game(t_game *game)
{
	exit_game(game, 0);
	return (0);
}
