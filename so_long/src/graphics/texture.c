/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:54 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/13 10:38:46 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	*load_image(t_game *game, char *path)
{
	int		width;
	int		height;
	void	*img;

	img = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (!img)
	{
		ft_putendl_fd("Error: Failed to load image", 2);
		exit_game(game, 1);
	}
	return (img);
}

void	load_textures(t_game *game)
{
	game->wall_img = NULL;
	game->player_img = NULL;
	game->collect_img = NULL;
	game->exit_img = NULL;
	game->empty_img = NULL;
	game->wall_img = load_image(game, "textures/wall.xpm");
	game->player_img = load_image(game, "textures/player.xpm");
	game->collect_img = load_image(game, "textures/collectible.xpm");
	game->exit_img = load_image(game, "textures/exit.xpm");
	game->empty_img = load_image(game, "textures/empty.xpm");
}
