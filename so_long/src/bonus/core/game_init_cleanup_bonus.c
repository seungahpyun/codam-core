/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_init_cleanup_bonus.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/24 09:03:10 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/24 09:29:44 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	free_textures(t_game *game)
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

bool	init_mlx_window(t_game *game)
{
	game->mlx = mlx_init(game->width * TILE_SIZE,
			game->height * TILE_SIZE, "so_long", true);
	return (game->mlx != NULL);
}

bool	init_game_components(t_game *game)
{
	if (!load_textures(game))
		return (false);
	if (!init_player(game))
		return (false);
	if (!init_player_animation(game))
		return (false);
	if (game->enemy_count > 0 && !init_enemy(game))
		return (false);
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
