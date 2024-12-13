/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 11:01:02 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/13 15:26:23 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static char	*create_moves_str(int moves)
{
	char	*moves_str;
	char	*temp;

	temp = ft_itoa(moves);
	if (!temp)
		return (NULL);
	moves_str = ft_strjoin("Moves: ", temp);
	free(temp);
	return (moves_str);
}

void	display_moves(t_game *game)
{
	char	*moves_str;
	void	*mlx;
	void	*win;

	mlx = game->mlx;
	win = game->window;
	moves_str = create_moves_str(game->moves);
	if (!moves_str)
		error_exit("Failed to create moves string", game);
	mlx_string_put(mlx, win, 10, 20, 0xFFFFFF, moves_str);
	free(moves_str);
}
