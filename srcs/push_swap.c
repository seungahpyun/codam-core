/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/20 15:22:25 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/29 09:32:42 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_stack		*a;

	if (argc < 2 || (argc == 2 && !*argv[1]))
		exit(EXIT_SUCCESS);
	a = ft_parse_input(argc, argv);
	if (!a || ft_has_duplicates(a))
	{
		ft_free(&a);
		ft_error();
	}
	if (!ft_is_sorted(a))
		ft_sort(&a);
	ft_free(&a);
	return (0);
}
