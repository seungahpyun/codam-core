/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long_bonus.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/16 18:35:57 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/24 13:43:49 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

/* Standard Libraries */
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>

/* Custom Libraries */
# include "libft.h"
# include "MLX42.h"

/* Constants */
# define TILE_SIZE 128
# define MAX_MAP_WIDTH 50
# define MAX_MAP_HEIGHT 50
# define ANIMATION_SPEED 10
# define ENEMY_MOVE_DELAY 30

/* Type Definitions */
typedef void	(*mlx_closefun)(void*);

typedef enum e_direction
{
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT
}	t_direction;

typedef struct s_enemy
{
	int	x;
	int	y;
	int	dx;
	int	dy;
}	t_enemy;

typedef struct s_player
{
	t_direction	direction;
	int			current_frame;
	int			frame_count;
	int			frame_delay;
	mlx_image_t	*frames[4][4];
}	t_player;

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
	int			collectibles;
	int			moves;
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

/* Function Prototypes */

/* Main game functions */
bool		init_game(t_game *game, char *file);
void		cleanup_game(t_game *game);
bool		init_mlx_window(t_game *game);
bool		init_game_components(t_game *game);

/* Animation functions */
void		update_animation(t_game *game);
void		update_enemy(t_game *game);

/* Map related functions */
bool		parse_map(t_game *game, char *file);
bool		validate_map(t_game *game);
bool		validate_elements(t_game *game);
bool		check_valid_path(t_game *game);
bool		allocate_map(t_game *game);
bool		fill_map(t_game *game, char *file);
void		free_allocated_map(t_game *game, int last_row);
void		free_temp_map(char **temp_map, int height);

/* Player related functions */
bool		init_player(t_game *game);
void		move_player(t_game *game, int new_x, int new_y);
void		update_player_position(t_game *game);

/* Enemy related functions */
bool		init_enemy(t_game *game);
void		update_enemy(t_game *game);
void		render_enemy(t_game *game);
bool		check_enemy_collision(t_game *game);
void		move_single_enemy(t_game *game, t_enemy *enemy);

/* Animation functions */
bool        init_player_animation(t_game *game);
bool	load_direction_frames(t_game *game, t_direction dir,
	const char *base_path);
void        update_animation(t_game *game);
void        cleanup_player_animation(t_game *game);
mlx_image_t	*get_current_player_sprite(t_game *game);

/* Render functions */
int			render_frame(t_game *game);
void		init_images(t_game *game);
bool		load_textures(t_game *game);
mlx_image_t	*load_image(t_game *game, const char *path);
void		init_collectibles_and_exit(t_game *game);
void		init_player_image(t_game *game);
void		update_player(t_game *game);
void		update_collectibles(t_game *game);

/* Display functions */
void		display_moves(t_game *game);

/* Utility functions */
void		handle_close(void *param);
void		error_exit(char *message, t_game *game);
void		validate_file_extension(const char *filename);
void		free_temp_map(char **temp_map, int height);
void		check_file_access(const char *filename);

#endif
