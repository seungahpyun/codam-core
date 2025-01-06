/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display_bonus.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 11:01:02 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/06 13:57:41 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

char	*create_moves_str(int moves)
{
	char	*temp;
	char	*moves_str;
	int		len;

	temp = ft_itoa(moves);
	if (!temp)
		return (NULL);
	len = ft_strlen("Moves: ") + ft_strlen(temp) + 1;
	moves_str = (char *)malloc(sizeof(char) * len);
	if (!moves_str)
	{
		free(temp);
		return (NULL);
	}
	ft_memset(moves_str, 0, len);
	ft_strlcpy(moves_str, "Moves: ", len);
	ft_strlcat(moves_str, temp, len);
	free(temp);
	return (moves_str);
}

void	display_moves(t_game *game)
{
	char	*moves_str;

	if (!game || !game->mlx)
		return ;
	moves_str = NULL;
	moves_str = create_moves_str(game->moves);
	if (!moves_str)
		error_exit("Error: Failed to create moves string", game);
	if (game->moves_text)
	{
		mlx_delete_image(game->mlx, game->moves_text);
		game->moves_text = NULL;
	}
	game->moves_text = mlx_put_string(game->mlx, moves_str, 30, 30);
	free(moves_str);
	if (!game->moves_text)
		error_exit("Error: Failed to display moves", game);
}
