/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 11:48:57 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/12 13:58:23 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_map
{
	char	**map;
	int		rows;
	int		cols;
}	t_map;

typedef struct s_game
{
	t_map	map;
	int		player_x;
	int		player_y;
	int		collectibles;
	int		moves;
	void	*window;
	void	*mlx;
}	t_game;

void	check_args(int argc, char **argv);
int		init_game(t_game *game, char *file);
void	exit_game(t_game *game, int status);

#endif
