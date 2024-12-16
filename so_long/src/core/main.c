/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 11:56:04 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/16 16:23:41 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		error_exit("Error: Invalid number of arguments", NULL);
	validate_file_extension(argv[1]);
	check_file_access(argv[1]);
	if (!init_game(&game, argv[1]))
	{
		ft_putendl_fd("Error: Game initialization failed", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (EXIT_SUCCESS);
}
