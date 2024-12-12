/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:59 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/12 20:26:49 by spyun         ########   odam.nl         */
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

static int	check_player(t_game *game)
{
	int	valid_path;
	int	player_found;
	int	i;
	int	j;

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
	if (player_found != 1)
		return (0);
	valid_path = check_valid_path(game);
	return (valid_path);
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
	if (!check_wall(game))
	{
		ft_putendl_fd("Error: Invalid wall configuration", 2);
		return (0);
	}
	if (!check_characters(game))
	{
		ft_putendl_fd("Error: Invalid characters in map", 2);
		return (0);
	}
	if (!count_elements(game))
	{
		ft_putendl_fd("Error: Invalid number of elements", 2);
		return (0);
	}
	if (!check_player(game))
	{
		ft_putendl_fd("Error: Invalid player position or path", 2);
		return (0);
	}
	return (1);
}

