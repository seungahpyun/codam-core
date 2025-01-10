/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/20 15:22:25 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/10 14:32:58 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_stack		*stack_a;

	if (argc < 2 || (argc == 2 && !*argv[1]))
		exit(EXIT_SUCCESS);
	stack_a = ft_parse_input(argc, argv);
	if (!stack_a || ft_has_duplicates(stack_a))
	{
		ft_free(&stack_a);
		ft_error();
	}
	if (!ft_is_sorted(stack_a))
		ft_sort(&stack_a);
	ft_free(&stack_a);
	return (EXIT_SUCCESS);
}
