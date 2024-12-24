/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_allocation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/24 11:22:56 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/24 11:24:01 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	allocate_map(t_game *game)
{
	int	i;

	if (!game || game->height <= 0 || game->width <= 0)
		return (false);
	game->map = (char **)malloc(sizeof(char *) * game->height);
	if (!game->map)
		return (false);
	i = 0;
	while (i < game->height)
	{
		game->map[i] = (char *)malloc(sizeof(char) * (game->width + 1));
		if (!game->map[i])
		{
			free_allocated_map(game, i);
			return (false);
		}
		game->map[i][game->width] = '\0';
		i++;
	}
	return (true);
}

bool	allocate_collect_instances(t_game *game)
{
	int	i;

	if (!game || game->height <= 0 || game->width <= 0)
		return (false);
	game->collect_instances = (int **)malloc(sizeof(int *) * game->height);
	if (!game->collect_instances)
		return (false);
	i = 0;
	while (i < game->height)
	{
		game->collect_instances[i] = (int *)malloc(sizeof(int) * game->width);
		if (!game->collect_instances[i])
		{
			while (--i >= 0)
				free(game->collect_instances[i]);
			free(game->collect_instances);
			return (false);
		}
		ft_memset(game->collect_instances[i], -1, sizeof(int) * game->width);
		i++;
	}
	return (true);
}
