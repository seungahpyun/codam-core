/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_lifecycle.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:00:14 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/12 14:16:09 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	init_game(t_game *game, char *file)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	if (parse_map(game, file) == 0)
		return (0);
	game->window = mlx_new_window(game->mlx, game->width * 32, game->height * 32, "so_long");
	if (!game->window)
		return (0);
	mlx_hook(game->window, 2, 1L << 0, key_hook, game);
	mlx_hook(game->window, 17, 1L << 17, close_game, game);
	mlx_loop_hook(game->mlx, render_next_frame, game);
	mlx_loop(game->mlx);
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
			free(game->map[i]);
			i++;
		}
		free(game->map);
	}
	if (game->window && game->mlx)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(status);
}
