/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_element.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 10:44:27 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/16 16:34:11 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_single_element(t_game *game, int i, int j, char type)
{
	if (!game || !game->map)
		return (0);
	if (game->map[i][j] == type)
	{
		if (type == 'P')
		{
			game->player_x = j;
			game->player_y = i;
			return (1);
		}
		if (type == 'C')
		{
			game->collectibles++;
			return (0);
		}
		return (1);
	}
	return (0);
}

int	count_elements(t_game *game)
{
	int	i;
	int	j;
	int	player;
	int	exit;

	if (!game || !game->map)
		return (0);
	i = -1;
	player = 0;
	exit = 0;
	game->collectibles = 0;
	while (++i < game->height)
	{
		j = -1;
		while (++j < game->width)
		{
			player += check_single_element(game, i, j, 'P');
			exit += check_single_element(game, i, j, 'E');
			check_single_element(game, i, j, 'C');
		}
	}
	return (player == 1 && exit == 1 && game->collectibles > 0);
}

int	find_player(t_game *game)
{
	int	i;
	int	j;
	int	player_found;

	if (!game || !game->map)
		return (0);
	player_found = 0;
	i = -1;
	while (++i < game->height)
	{
		j = -1;
		while (++j < game->width)
		{
			if (game->map[i][j] == 'P')
			{
				game->player_x = j;
				game->player_y = i;
				player_found++;
			}
		}
	}
	return (player_found == 1);
}

int	validate_elements(t_game *game)
{
	if (!game)
		return (0);
	if (!count_elements(game))
	{
		ft_putendl_fd("Error: Invalid number of elements", 2);
		return (0);
	}
	if (!find_player(game))
	{
		ft_putendl_fd("Error: Invalid player position", 2);
		return (0);
	}
	return (1);
}
