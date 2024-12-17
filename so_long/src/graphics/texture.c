/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:54 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/17 17:17:51 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

mlx_image_t	*load_image(t_game *game, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	if (!game || !game->mlx || !path)
		return (NULL);

	printf("Attempting to load texture: %s\n", path);
	texture = mlx_load_png(path);
	if (!texture)
	{
		printf("Failed to load texture: %s\n", path);
		// Try to check if file exists
		int fd = open(path, O_RDONLY);
		if (fd == -1)
			printf("File does not exist or cannot be opened\n");
		else
		{
			close(fd);
			printf("File exists but failed to load as PNG\n");
		}
		return (NULL);
	}

	img = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	if (!img)
	{
		printf("Failed to convert texture to image\n");
		return (NULL);
	}

	printf("Successfully loaded texture: %s\n", path);
	return (img);
}

void	load_textures(t_game *game)
{
	if (!game)
		return ;

	printf("Starting texture loading...\n");

	// Get current working directory
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("Current working directory: %s\n", cwd);

	game->wall_img = load_image(game, "textures/wall.png");
	game->player_img = load_image(game, "textures/player/down/down1.png");
	game->collect_img = load_image(game, "textures/collect.png");
	game->exit_img = load_image(game, "textures/exit.png");
	game->empty_img = load_image(game, "textures/empty.png");
	game->enemy_img = load_image(game, "textures/enemy.png");

	if (!game->wall_img || !game->player_img || !game->collect_img ||
		!game->exit_img || !game->empty_img || !game->enemy_img)
		error_exit("Failed to load one or more textures", game);
}
