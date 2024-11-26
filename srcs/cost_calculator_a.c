/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cost_calculator_a.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 11:04:15 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/26 15:07:54 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_calc_rarb_a(t_stack *a, t_stack *b, int c)
{
	int	i;

	if (!a || !b)
		return (0);
	i = ft_find_place_a(a, c);
	if (i < ft_find_index(b, c))
		i = ft_find_index(b, c);
	return (i);
}

int	ft_calc_rarrb_a(t_stack *a, t_stack *b, int c)
{
	int	i;

	if (!a || !b)
		return (0);
	i = 0;
	if (ft_find_index(b, c))
		i = ft_stack_size(b) - ft_find_index(b, c);
	i = ft_find_place_a(a, c) + i;
	return (i);
}

int	ft_calc_rrarb_a(t_stack *a, t_stack *b, int c)
{
	int	i;

	if (!a || !b)
		return (0);
	i = 0;
	if (ft_find_place_a(a, c))
		i = ft_stack_size(a) - ft_find_place_a(a, c);
	i = ft_find_index(b, c) + i;
	return (i);
}

int	ft_calc_rrarrb_a(t_stack *a, t_stack *b, int c)
{
	int	i;
	int	j;

	if (!a || !b)
		return (0);
	i = 0;
	if (ft_find_place_a(a, c))
		i = ft_stack_size(a) - ft_find_place_a(a, c);
	j = ft_stack_size(b) - ft_find_index(b, c);
	if ((i < j) && ft_find_index(b, c))
		i = j;
	return (i);
}
