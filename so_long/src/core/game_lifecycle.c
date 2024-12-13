/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_lifecycle.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:00:14 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/12 20:27:49 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	free_textures(t_game *game)
{
	if (game->wall_img)
		mlx_destroy_image(game->mlx, game->wall_img);
	if (game->player_img)
		mlx_destroy_image(game->mlx, game->player_img);
	if (game->collect_img)
		mlx_destroy_image(game->mlx, game->collect_img);
	if (game->exit_img)
		mlx_destroy_image(game->mlx, game->exit_img);
	if (game->empty_img)
		mlx_destroy_image(game->mlx, game->empty_img);
}

int	close_game(t_game *game)
{
	exit_game(game, 0);
	return (0);
}

int	render_next_frame(t_game *game)
{
	render_frame(game);
	return (0);
}

int	init_game(t_game *game, char *file)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->moves = 0;
	game->collectibles = 0;
	if (!parse_map(game, file))
	{
		ft_putendl_fd("Error: Failed to parse map", 2);
		return (0);
	}
	game->window = mlx_new_window(game->mlx, game->width * 32,
			game->height * 32, "so_long");
	if (!game->window)
		return (0);
	load_textures(game);
	mlx_hook(game->window, 2, 1L << 0, key_hook, game);
	mlx_hook(game->window, 17, 1L << 17, close_game, game);
	mlx_loop_hook(game->mlx, render_next_frame, game);
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
		if (game->window)
			mlx_destroy_window(game->mlx, game->window);
		free(game->mlx);
	}
	exit(status);
}
