/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 13:54:06 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/13 09:54:34 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	error_exit(char *message, t_game *game)
{
	ft_putendl_fd(message, STDERR_FILENO);
	if (game)
		exit_game(game, EXIT_FAILURE);
	else
		exit(EXIT_FAILURE);
}

void	check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl_fd("Error, invalid number of arguments", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 4) != 0)
	{
		ft_putendl_fd("Error, file must be a .ber file", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}
