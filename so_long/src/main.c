/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 11:56:04 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/12 13:50:51 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;
	
	check_args(argc, argv);
	ft_memset(&game, 0, sizeof(t_game));
	if (init_game(&game, argv[1]) == -1)
	{
		ft_putendl_fd("Error", 2);
		exit_game(&game, 1);
	}
	mlx_loop(game.mlx);
	return (0);
}
