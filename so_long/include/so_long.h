/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 11:48:57 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/12 13:49:55 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

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

#endif
