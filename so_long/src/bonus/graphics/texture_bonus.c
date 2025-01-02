/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture_bonus.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:54 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/02 09:15:29 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

mlx_image_t	*load_image(t_game *game, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;
	int				fd;

	if (!game || !game->mlx || !path)
		return (NULL);
	texture = mlx_load_png(path);
	if (!texture)
	{
		ft_putendl_fd("Failed to load texture", STDERR_FILENO);
		fd = open(path, O_RDONLY);
		if (fd == -1)
			ft_putendl_fd("File does not exist or cannot be opened",
				STDERR_FILENO);
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

bool	load_textures(t_game *game)
{
	if (!game)
		return (false);
	game->wall_img = load_image(game, "textures/wall.png");
	game->player_img = load_image(game, "textures/player/down/down1.png");
	game->collect_img = load_image(game, "textures/collect.png");
	game->exit_img = load_image(game, "textures/exit.png");
	game->empty_img = load_image(game, "textures/empty.png");
	game->enemy_img = load_image(game, "textures/enemy/right1.png");
	if (!game->wall_img || !game->player_img || !game->collect_img
		|| !game->exit_img || !game->empty_img || !game->enemy_img)
		return (false);
	return (true);
}
