/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   small_sort_handler.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 14:33:58 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/25 14:36:06 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_sort_three(t_stack **stack)
{
	if (ft_min(*stack) == (*stack)->nbr)
	{
		ft_rra(stack, 0);
		ft_sa(stack, 0);
	}
	else if (ft_max(*stack) == (*stack)->nbr)
	{
		ft_ra(stack, 0);
		if (!ft_is_sorted(*stack))
			ft_sa(stack, 0);
	}
	else
	{
		if (ft_find_index(*stack, ft_max(*stack)) == 1)
			ft_rra(stack, 0);
		else
			ft_sa(stack, 0);
	}
}
