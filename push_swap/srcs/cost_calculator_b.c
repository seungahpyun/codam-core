/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cost_calculator_b.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 11:04:17 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/26 14:48:41 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_calc_rarb_b(t_stack *a, t_stack *b, int c)
{
	int	i;

	if (!a || !b)
		return (0);
	i = ft_find_place_b(b, c);
	if (i < ft_find_index(a, c))
		i = ft_find_index(a, c);
	return (i);
}

int	ft_calc_rarrb_b(t_stack *a, t_stack *b, int c)
{
	int	i;

	if (!a || !b)
		return (0);
	i = 0;
	if (ft_find_place_b(b, c))
		i = ft_stack_size(b) - ft_find_place_b(b, c);
	i = ft_find_index(a, c) + i;
	return (i);
}

int	ft_calc_rrarb_b(t_stack *a, t_stack *b, int c)
{
	int	i;

	if (!a || !b)
		return (0);
	i = 0;
	if (ft_find_index(a, c))
		i = ft_stack_size(a) - ft_find_index(a, c);
	i = ft_find_place_b(b, c) + i;
	return (i);
}

int	ft_calc_rrarrb_b(t_stack *a, t_stack *b, int c)
{
	int	i;
	int	j;

	if (!a || !b)
		return (0);
	i = 0;
	if (ft_find_place_b(b, c))
		i = ft_stack_size(b) - ft_find_place_b(b, c);
	j = ft_stack_size(a) - ft_find_index(a, c);
	if ((i < j) && ft_find_index(a, c))
		i = j;
	return (i);
}
