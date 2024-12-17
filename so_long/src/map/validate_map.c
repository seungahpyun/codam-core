/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:18:59 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/17 17:15:57 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

static bool	check_wall(t_game *game)
{
	int	i;

	if (!game || !game->map)
		return (false);

	printf("Checking walls...\n");
	i = 0;
	while (i < game->width)
	{
		if (game->map[0][i] != '1')
		{
			printf("Top wall broken at position %d\n", i);
			return (false);
		}
		if (game->map[game->height - 1][i] != '1')
		{
			printf("Bottom wall broken at position %d\n", i);
			return (false);
		}
		i++;
	}
	i = 0;
	while (i < game->height)
	{
		if (game->map[i][0] != '1')
		{
			printf("Left wall broken at position %d\n", i);
			return (false);
		}
		if (game->map[i][game->width - 1] != '1')
		{
			printf("Right wall broken at position %d\n", i);
			return (false);
		}
		i++;
	}
	printf("Wall check successful\n");
	return (true);
}

static bool	check_characters(t_game *game)
{
	int		i;
	int		j;
	char	c;

	if (!game || !game->map)
		return (false);
	i = -1;
	while (++i < game->height)
	{
		j = -1;
		while (++j < game->width)
		{
			c = game->map[i][j];
			if (c != '0' && c != '1' && c != 'C' && c != 'E' && c != 'P'
				&& c != 'X')
				return (false);
		}
	}
	return (true);
}

static void	count_enemy(t_game *game)
{
	int	i;
	int	j;

	if (!game || !game->map)
		return ;
	game->enemy_count = 0;
	i = -1;
	while (++i < game->height)
	{
		j = -1;
		while (++j < game->width)
		{
			if (game->map[i][j] == 'X')
				game->enemy_count++;
		}
	}
}

bool	validate_map(t_game *game)
{
	if (!game || !game->map)
		return (false);
	if (!check_wall(game))
	{
		ft_putendl_fd("Error: Invalid wall configuration", 2);
		return (false);
	}
	if (!check_characters(game))
	{
		ft_putendl_fd("Error: Invalid characters in map", 2);
		return (false);
	}
	if (!validate_elements(game))
		return (false);
	if (!check_valid_path(game))
		return (false);
	count_enemy(game);
	return (true);
}
