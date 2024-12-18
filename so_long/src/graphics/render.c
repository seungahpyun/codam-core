/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:52 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/18 15:05:01 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->empty_img)
			{
				if (mlx_image_to_window(game->mlx, game->empty_img,
					x * TILE_SIZE, y * TILE_SIZE) < 0)
					error_exit("Failed to render background", game);
			}
			x++;
		}
		y++;
	}
}

static void	init_walls(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == '1' && game->wall_img)
			{
				if (mlx_image_to_window(game->mlx, game->wall_img,
					x * TILE_SIZE, y * TILE_SIZE) < 0)
					error_exit("Failed to render wall", game);
			}
			x++;
		}
		y++;
	}
}

static void	init_collectibles_and_exit(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == 'C' && game->collect_img)
			{
				if (mlx_image_to_window(game->mlx, game->collect_img,
					x * TILE_SIZE, y * TILE_SIZE) < 0)
					error_exit("Failed to render collectible", game);
			}
			if (game->map[y][x] == 'E' && game->exit_img)
			{
				if (mlx_image_to_window(game->mlx, game->exit_img,
					x * TILE_SIZE, y * TILE_SIZE) < 0)
					error_exit("Failed to render exit", game);
			}
			x++;
		}
		y++;
	}
}

static void	init_enemies(t_game *game)
{
	int	i;

	if (!game->enemy_img || game->enemy_count <= 0)
		return ;
	i = 0;
	while (i < game->enemy_count)
	{
		if (mlx_image_to_window(game->mlx, game->enemy_img,
			game->enemies[i].x * TILE_SIZE,
			game->enemies[i].y * TILE_SIZE) < 0)
			error_exit("Failed to render enemy", game);
		i++;
	}
}

static void	update_player(t_game *game)
{
	mlx_image_t	*current_sprite;

	if (!game)
		return ;
	for (t_direction dir = DIRECTION_UP; dir <= DIRECTION_RIGHT; dir++)
	{
		for (int frame = 0; frame < 4; frame++)
		{
			if (game->player.frames[dir][frame] &&
				game->player.frames[dir][frame]->instances)
			{
				game->player.frames[dir][frame]->instances[0].enabled = false;
			}
		}
	}
	current_sprite = get_current_player_sprite(game);
	if (current_sprite && current_sprite->instances)
	{
		current_sprite->instances[0].x = game->player_x * TILE_SIZE;
		current_sprite->instances[0].y = game->player_y * TILE_SIZE;
		current_sprite->instances[0].enabled = true;
	}
}

static void	init_player_image(t_game *game)
{
	t_direction	dir;
	int			frame;

	if (!game)
		return ;
	dir = DIRECTION_UP;
	while (dir <= DIRECTION_RIGHT)
	{
		frame = 0;
		while (frame < 4)
		{
			if (game->player.frames[dir][frame])
			{
				if (mlx_image_to_window(game->mlx,
					game->player.frames[dir][frame],
					game->player_x * TILE_SIZE,
					game->player_y * TILE_SIZE) < 0)
					error_exit("Failed to render player frame", game);
				if (dir != game->player.direction || frame != 0)
					game->player.frames[dir][frame]->instances[0].enabled = false;
			}
			frame++;
		}
		dir++;
	}
}

static void	init_images(t_game *game)
{
	init_background(game);
	init_walls(game);
	init_collectibles_and_exit(game);
	init_player_image(game);
	init_enemies(game);
}

static void	update_enemies(t_game *game)
{
	int	i;

	if (!game || !game->enemy_img || !game->enemy_img->instances
		|| game->enemy_count <= 0)
		return ;
	i = 0;
	while (i < game->enemy_count)
	{
		game->enemy_img->instances[i].x = game->enemies[i].x * TILE_SIZE;
		game->enemy_img->instances[i].y = game->enemies[i].y * TILE_SIZE;
		i++;
	}
}

static void	update_collectibles(t_game *game)
{
	int		x;
	int		y;
	size_t	i;
	size_t	instance_index;

	if (!game || !game->collect_img || !game->collect_img->instances)
		return ;
	i = 0;
	while (i < game->collect_img->count)
	{
		game->collect_img->instances[i].enabled = false;
		i++;
	}
	y = 0;
	instance_index = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == 'C' &&
				instance_index < game->collect_img->count)
			{
				game->collect_img->instances[instance_index].x = x * TILE_SIZE;
				game->collect_img->instances[instance_index].y = y * TILE_SIZE;
				game->collect_img->instances[instance_index].enabled = true;
				instance_index++;
			}
			x++;
		}
		y++;
	}
}

int	render_frame(t_game *game)
{
	static bool	initialized = false;

	if (!game)
		return (0);
	if (!initialized)
	{
		init_images(game);
		initialized = true;
		return (0);
	}
	update_player(game);
	update_enemies(game);
	update_collectibles(game);
	display_moves(game);
	return (0);
}
