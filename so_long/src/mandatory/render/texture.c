/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:54 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/06 09:45:53 by spyun         ########   odam.nl         */
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
	{
		ft_putendl_fd("Failed to load texture", STDERR_FILENO);
		return (NULL);
	}
	img = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	if (!img)
	{
		ft_putendl_fd("Failed to convert texture to image", STDERR_FILENO);
		return (NULL);
	}
	return (img);
}

static bool	check_image_loading(t_game *game)
{
	if (!game->wall_img || !game->player_img || !game->collect_img
		|| !game->exit_img || !game->empty_img)
	{
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
		return (false);
	}
	return (true);
}

bool	load_textures(t_game *game)
{
	if (!game || !game->mlx)
		return (false);
	game->wall_img = load_image(game, "textures/wall.png");
	game->player_img = load_image(game, "textures/player.png");
	game->collect_img = load_image(game, "textures/collect.png");
	game->exit_img = load_image(game, "textures/exit.png");
	game->empty_img = load_image(game, "textures/empty.png");
	return (check_image_loading(game));
}
