/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/16 18:35:57 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/16 16:54:36 by spyun         ########   odam.nl         */
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

# define TILE_SIZE 32
# define ANIMATION_SPEED 10

typedef void (*mlx_closefun)(void*);

typedef enum e_direction
{
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT
}	t_direction;

typedef struct s_player
{
	int			current_frame;
	int			frame_count;
	int			frame_delay;
	t_direction	direction;
	mlx_image_t	*frames[4][4];
}	t_player;

typedef struct s_enemy
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	current_frame;
	int	frame_count;
}	t_enemy;

typedef struct s_path
{
	int	width;
	int	height;
	int	collectibles;
	int	exit_found;
}	t_path;

typedef struct s_game
{
	mlx_t		*mlx;
	char		**map;
	int			width;
	int			height;
	int			player_x;
	int			player_y;
	int			moves;
	int			collectibles;
	int			enemy_count;
	t_enemy		*enemies;
	t_player	player;
	mlx_image_t	*wall_img;
	mlx_image_t	*player_img;
	mlx_image_t	*collect_img;
	mlx_image_t	*exit_img;
	mlx_image_t	*empty_img;
	mlx_image_t	*enemy_img;
	mlx_image_t	*moves_text;
}	t_game;


bool		init_game(t_game *game, char *file);
void		cleanup_game(t_game *game);
void		error_exit(char *message, t_game *game);
void		check_args(int argc, char **argv);

void		validate_file_extension(const char *filename);
void		check_file_access(const char *filename);

int			parse_map(t_game *game, char *file);
bool		validate_map(t_game *game);
int			validate_elements(t_game *game);
int			check_valid_path(t_game *game);
int			find_player(t_game *game);
int			count_elements(t_game *game);

int			allocate_map(t_game *game);
int			fill_map(t_game *game, char *file);
void		free_allocated_map(t_game *game, int last_row);
int			allocate_and_fill_map(t_game *game, char *file);

int			render_frame(t_game *game);
mlx_image_t	*load_image(t_game *game, const char *path);
void		load_textures(t_game *game);

void		move_player(t_game *game, int new_x, int new_y);
bool		init_player(t_game *game);
bool		init_player_animation(t_game *game);
void		update_player_position(t_game *game);
void		update_animation(t_game *game);
mlx_image_t	*get_current_player_sprite(t_game *game);
bool		init_enemy(t_game *game);
void		update_enemy(t_game *game);
void		render_enemy(t_game *game);

void		display_moves(t_game *game);

#endif
