/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 11:48:57 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/13 15:32:17 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include "mlx.h"

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
	void		*frames[4][4]; // 4 directions, 4 frames
}	t_player;

typedef struct s_enemy
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	void	*sprite;
	int		current_frame;
	int		frame_count;
}	t_enemy;

# define ANIMATION_SPEED 10

typedef struct s_game
{
	char	**map;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		collectibles;
	int		moves;
	void	*window;
	void	*mlx;
	void	*wall_img;
	void	*player_img;
	void	*collect_img;
	void	*exit_img;
	void	*empty_img;
	t_enemy	*enemies;
	int		enemy_count;
}	t_game;

typedef struct s_path
{
	int	width;
	int	height;
	int	collectibles;
	int	exit_found;
}	t_path;

/* Initialization and cleanup */
void	check_args(int argc, char **argv);
int		init_game(t_game *game, char *file);
void	exit_game(t_game *game, int status);
void	error_exit(char *message, t_game *game);
int		close_game(t_game *game);

/* Map parsing and validation */
int		parse_map(t_game *game, char *file);
int		validate_map(t_game *game);
int		validate_elements(t_game *game);
int		check_valid_path(t_game *game);
int		allocate_and_fill_map(t_game *game, char *file);
void	free_allocated_map(t_game *game, int last_row);

/* Graphics and rendering */
void	load_textures(t_game *game);
int		render_frame(t_game *game);
int		render_next_frame(t_game *game);

/* Player and game mechanics */
int		key_hook(int keycode, t_game *game);
void	move_player(t_game *game, int new_x, int new_y);
int		check_collision(t_game *game, int new_x, int new_y);
void	collect_item(t_game *game, int x, int y);
int		check_exit(t_game *game, int x, int y);

/* Game states and updates */
void	update_game_state(t_game *game);
void	display_moves(t_game *game);

int		init_enemies(t_game *game);
void	update_enemies(t_game *game);
void	render_enemies(t_game *game);
void	game_over(t_game *game);

#endif
