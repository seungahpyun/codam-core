/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:59 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/12 14:44:08 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	check_wall(t_game *game)
{
	int i;

	i = 0;
	while(i < game->width)
	{
		if(game->map[0][i] != '1' || game->map[game->height - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while(i < game->height)
	{
		if(game->map[i][0] != '1' || game->map[i][game->width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

static int	count_elements(t_game *game)
{
	int	i;
	int	j;
	int	player;
	int exit;

	i = 0;
	player = 0;
	exit = 0;
	while(i < game->height)
	{
		j = 0;
		while(j < game->width)
		{
			if(game->map[i][j] == 'P')
			{
				player++;
				game->player_x = j;
				game->player_y = i;
			}
			else if(game->map[i][j] == 'E')
				exit++;
			else if(game->map[i][j] == 'C')
				game->collectibles++;
			j++;
		}
		i++;
	}
	return (player == 1 && exit == 1 && game->collectibles > 0);
}

static int	check_characters(t_game *game)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			c = game->map[i][j];
			if (c != '0' && c != '1' && c != 'C' && 
				c != 'E' && c != 'P')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_map(t_game *game)
{
	if(!check_wall(game))
		return (0);
	if(!check_player(game))
		return (0);
	if(!count_elements(game))
		return (0);
	return (1);
}
