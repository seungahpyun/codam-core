/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:00:14 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/23 10:09:59 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_textures(t_game *game)
{
	if (!game || !game->mlx)
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
}

static void	handle_movement(int *new_x, int *new_y,
	mlx_key_data_t keydata)
{
	if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		&& keydata.action == MLX_PRESS)
		(*new_y)--;
	else if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		&& keydata.action == MLX_PRESS)
		(*new_y)++;
	else if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		&& keydata.action == MLX_PRESS)
		(*new_x)--;
	else if ((keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		&& keydata.action == MLX_PRESS)
		(*new_x)++;
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
	handle_movement(&new_x, &new_y, keydata);
	if (new_x != game->player_x || new_y != game->player_y)
		move_player(game, new_x, new_y);
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
	if (!allocate_collect_instances(game))
		return (false);
	if (!load_textures(game))
	{
		free_allocated_map(game, game->height);
		return (false);
	}
	if (!init_player(game))
	{
		free_allocated_map(game, game->height);
		return (false);
	}
	mlx_loop_hook(game->mlx, (void *)&render_frame, game);
	mlx_key_hook(game->mlx, &key_handler, game);
	return (true);
}

void	cleanup_game(t_game *game)
{
	int	i;

	if (!game)
		return ;
	if (game->map)
		free_allocated_map(game, game->height);
	if (game->collect_instances)
	{
		i = 0;
		while (i < game->height)
		{
			if (game->collect_instances[i])
				free(game->collect_instances[i]);
			i++;
		}
		free(game->collect_instances);
	}
	if (game->mlx)
	{
		free_textures(game);
		mlx_terminate(game->mlx);
	}
}
