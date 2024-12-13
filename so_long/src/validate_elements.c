/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_elements.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 10:44:27 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/13 10:56:59 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	check_single_element(t_game *game, int i, int j, char type)
{
	if (game->map[i][j] == type)
	{
		if (type == 'P')
		{
			game->player_x = j;
			game->player_y = i;
			return (1);
		}
		else if (type == 'C')
		{
			game->collectibles++;
			return (0);
		}
		return (1);
	}
	return (0);
}

static int	count_elements(t_game *game)
{
	int	i;
	int	j;
	int	player;
	int	exit;

	i = 0;
	player = 0;
	exit = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			player += check_single_element(game, i, j, 'P');
			exit += check_single_element(game, i, j, 'E');
			check_single_element(game, i, j, 'C');
			j++;
		}
		i++;
	}
	return (player == 1 && exit == 1 && game->collectibles > 0);
}

static int	find_player(t_game *game)
{
	int	i;
	int	j;
	int	player_found;

	player_found = 0;
	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			if (game->map[i][j] == 'P')
			{
				game->player_x = j;
				game->player_y = i;
				player_found++;
			}
			j++;
		}
		i++;
	}
	return (player_found);
}

int	validate_elements(t_game *game)
{
	if (!count_elements(game))
		return (0);
	if (!find_player(game))
		return (0);
	return (1);
}
