/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 11:48:57 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/12 20:03:54 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

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
}	t_game;

typedef struct s_path
{
	int	width;
	int	height;
	int	collectibles;
	int	exit_found;
}	t_path;

void	check_args(int argc, char **argv);
int		init_game(t_game *game, char *file);
void	exit_game(t_game *game, int status);

#endif
