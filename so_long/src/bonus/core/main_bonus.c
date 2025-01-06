/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 11:56:04 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/06 10:05:14 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	init_game_struct(t_game *game)
{
	if (!game)
		error_exit("Error: Game structure is NULL", NULL);
	ft_memset(game, 0, sizeof(t_game));
	game->moves = 0;
	game->collectibles = 0;
	game->enemy_count = 0;
	game->player_x = -1;
	game->player_y = -1;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		error_exit("Error: Invalid number of arguments", NULL);
	validate_file_extension(argv[1]);
	check_file_access(argv[1]);
	init_game_struct(&game);
	if (!init_game(&game, argv[1]))
	{
		cleanup_game(&game);
		error_exit("Error: Game initialization failed", NULL);
	}
	mlx_close_hook(game.mlx, &handle_close, &game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (EXIT_SUCCESS);
}
