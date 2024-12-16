/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:54 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/16 09:55:15 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

mlx_image_t	*load_image(t_game *game, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(path);
	if (!texture)
		error_exit("Failed to load texture", game);
	img = mlx_texture_to_image(game->mlx, texture);
	if (!img)
	{
		mlx_delete_texture(texture);
		error_exit("Failed to create image", game);
	}
	mlx_delete_texture(texture);
	return (img);
}

void	load_textures(t_game *game)
{
	game->wall_img = load_image(game, "textures/wall.png");
	game->player_img = load_image(game, "textures/player.png");
	game->collect_img = load_image(game, "textures/collect.png");
	game->exit_img = load_image(game, "textures/exit.png");
	game->empty_img = load_image(game, "textures/empty.png");
	if ((mlx_image_to_window(game->mlx, game->wall_img, 0, 0) < 0
		|| mlx_image_to_window(game->mlx, game->player_img, 0, 0) < 0
		|| mlx_image_to_window(game->mlx, game->collect_img, 0, 0) < 0
		|| mlx_image_to_window(game->mlx, game->exit_img, 0, 0) < 0
		|| mlx_image_to_window(game->mlx, game->empty_img, 0, 0) < 0))
	{
		error_exit("Failed to display textures", game);
	}
}
