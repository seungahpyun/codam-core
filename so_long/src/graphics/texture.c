/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:54 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/17 16:14:37 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_image_t	*load_image(t_game *game, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	if (!game || !game->mlx || !path)
		return (NULL);
	texture = mlx_load_png(path);
	if (!texture)
		error_exit("Failed to load texture", game);
	img = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	if (!img)
		error_exit("Failed to create image", game);
	return (img);
}

static bool	display_image(t_game *game, mlx_image_t *img)
{
	if (!game || !game->mlx || !img)
		return (false);
	if (mlx_image_to_window(game->mlx, img, 0, 0) < 0)
		return (false);
	return (true);
}

void	load_textures(t_game *game)
{
	if (!game)
		return ;
	game->wall_img = load_image(game, "textures/wall.png");
	game->player_img = load_image(game, "textures/player/down/down1.png");
	game->collect_img = load_image(game, "textures/collect.png");
	game->exit_img = load_image(game, "textures/exit.png");
	game->empty_img = load_image(game, "textures/empty.png");
	game->enemy_img = load_image(game, "textures/enemy.png");
	if (!display_image(game, game->wall_img)
		|| !display_image(game, game->player_img)
		|| !display_image(game, game->collect_img)
		|| !display_image(game, game->exit_img)
		|| !display_image(game, game->empty_img)
		|| !display_image(game, game->enemy_img))
	{
		error_exit("Failed to display textures", game);
	}
}
