/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 11:56:04 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/16 14:35:40 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	check_args(argc, argv);
	if (init_game(&game, argv[1]) == -1)
	{
		exit_game(&game, 1);
		return (1);
	}
	if (!game.mlx)
	{
		ft_putendl_fd("Error: MLX not initialized", 2);
		exit_game(&game, 1);
		return (1);
	}
	mlx_loop(game.mlx);
	exit_game(&game, 0);
	return (0);
}
