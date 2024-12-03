/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_handler.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 10:33:10 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/03 09:08:23 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_sort_three(t_stack **stack_a)
{
	if (ft_min(*stack_a) == (*stack_a)->nbr)
	{
		ft_rra(stack_a, 0);
		ft_sa(stack_a, 0);
	}
	else if (ft_max(*stack_a) == (*stack_a)->nbr)
	{
		ft_ra(stack_a, 0);
		if (!ft_is_sorted(*stack_a))
			ft_sa(stack_a, 0);
	}
	else
	{
		if (ft_find_index(*stack_a, ft_max(*stack_a)) == 1)
			ft_rra(stack_a, 0);
		else
			ft_sa(stack_a, 0);
	}
}

void	ft_sort_small_stack(t_stack **stack_a)
{
	if (ft_stack_size(*stack_a) == 2 && (*stack_a)->nbr > (*stack_a)->next->nbr)
		ft_sa(stack_a, 0);
	else if (ft_stack_size(*stack_a) == 3)
		ft_sort_three(stack_a);
}

void	ft_sort(t_stack **stack_a)
{
	t_stack	*stack_b;

	if (!stack_a || !*stack_a
		|| ft_stack_size(*stack_a) <= 1 || ft_is_sorted(*stack_a))
		return ;
	if (ft_stack_size(*stack_a) <= 3)
		return (ft_sort_small_stack(stack_a));
	stack_b = ft_initialize_stack_b(stack_a);
	if (stack_b)
		ft_move_back_to_a(stack_a, &stack_b);
	ft_align_stack(stack_a);
}
