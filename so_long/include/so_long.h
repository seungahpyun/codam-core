/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/23 09:26:01 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/29 13:00:41 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include "libft.h"
# include "MLX42.h"

# define TILE_SIZE 128
# define MAX_MAP_WIDTH 50
# define MAX_MAP_HEIGHT 50

typedef struct s_path
{
	int		width;
	int		height;
	int		collectibles;
	bool	exit_found;
}	t_path;

typedef struct s_game
{
	mlx_t		*mlx;
	char		**map;
	int			width;
	int			height;
	int			player_x;
	int			player_y;
	int			collectibles;
	int			**collect_instances;
	int			moves;
	mlx_image_t	*wall_img;
	mlx_image_t	*player_img;
	mlx_image_t	*collect_img;
	mlx_image_t	*exit_img;
	mlx_image_t	*empty_img;
}	t_game;

bool		init_game(t_game *game, char *file);
void		cleanup_game(t_game *game);

bool		parse_map(t_game *game, char *file);
bool		validate_map(t_game *game);
bool		validate_elements(t_game *game);
bool		check_valid_path(t_game *game);
bool		allocate_map(t_game *game);
bool		allocate_and_fill_map(t_game *game, char *file);
bool		allocate_collect_instances(t_game *game);
void		free_allocated_map(t_game *game, int last_row);

void		move_player(t_game *game, int new_x, int new_y);
bool		init_player(t_game *game);
void		init_player_image(t_game *game);
void		update_player_position(t_game *game);

void		init_background(t_game *game);
void		init_walls(t_game *game);

void		init_collectibles_and_exit(t_game *game);
int			render_frame(t_game *game);

bool		load_textures(t_game *game);
mlx_image_t	*load_image(t_game *game, const char *path);

void		error_exit(char *message, t_game *game);
void		validate_file_extension(const char *filename);
void		check_file_access(const char *filename);
void		handle_close(void *param);

#endif
