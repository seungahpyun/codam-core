/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_helpers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/26 15:42:58 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/26 15:43:39 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_sort_small_stack(t_stack **stack_a)
{
	if (ft_stack_size(*stack_a) == 2 && (*stack_a)->nbr > (*stack_a)->next->nbr)
		ft_sa(stack_a, 0);
	else if (ft_stack_size(*stack_a) == 3)
		ft_sort_three(stack_a);
}

void	ft_align_stack(t_stack **stack_a)
{
	int	i;

	i = ft_find_index(*stack_a, ft_min(*stack_a));
	if (i < ft_stack_size(*stack_a) - i)
		while ((*stack_a)->nbr != ft_min(*stack_a))
			ft_ra(stack_a, 0);
	else
		while ((*stack_a)->nbr != ft_min(*stack_a))
			ft_rra(stack_a, 0);
}
