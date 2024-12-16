/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 11:48:57 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/16 14:25:49 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
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
	mlx_image_t	*frames[4][4]; // 4 directions, 4 frames
}	t_player;

typedef struct s_enemy
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	int		current_frame;
	int		frame_count;
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

/* Initialization and cleanup */
void	check_args(int argc, char **argv);
int		init_game(t_game *game, char *file);
void	exit_game(t_game *game, int status);
void	error_exit(char *message, t_game *game);
void		close_game(t_game *game);

/* Map memory management */
int     allocate_map(t_game *game);
int     fill_map(t_game *game, char *file);
void    free_allocated_map(t_game *game, int last_row);

/* Map parsing and validation */
int		parse_map(t_game *game, char *file);
int		validate_map(t_game *game);
int		validate_elements(t_game *game);
int		check_valid_path(t_game *game);
int		allocate_and_fill_map(t_game *game, char *file);
void	free_allocated_map(t_game *game, int last_row);

/* Graphics and rendering */
mlx_image_t	*load_image(t_game *game, const char *path);
void	load_textures(t_game *game);
int		render_frame(t_game *game);
int		render_next_frame(t_game *game);

/* Animation functions */
void     init_player_animation(t_game *game);
void    update_animation(t_game *game);
void    *get_current_player_sprite(t_game *game);

/* Player and game mechanics */
int		key_hook(int keycode, t_game *game);
void	move_player(t_game *game, int x, int y);

/* Game states and updates */
void	update_game_state(t_game *game);
void	display_moves(t_game *game);

/* Map validation functions */
int     find_player(t_game *game);
int     count_elements(t_game *game);

int		init_enemy(t_game *game);
void	update_enemy(t_game *game);
void	render_enemy(t_game *game);
void	game_over(t_game *game);

#endif
