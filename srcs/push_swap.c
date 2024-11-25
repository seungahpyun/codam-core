/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/20 15:22:25 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/25 15:09:09 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	main(int argc, char **argv)
{
	t_stack		*a;

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
