/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_handler.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 10:33:10 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/25 15:36:10 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_stack	*ft_sort_a(t_stack **a, t_stack **b)
{
	t_stack	*temp;
	int		i;

	while (*b)
	{
		temp = *b;
		i = ft_rotate_type_ba(*a, *b);
		while (i >= 0)
		{
			if (i == ft_calc_rarb_a(*a, *b, temp->nbr))
				i = ft_apply_rarb(a, b, temp->nbr, 'b');
			else if (i == ft_calc_rarrb_a(*a, *b, temp->nbr))
				i = ft_apply_rarrb(a, b, temp->nbr, 'b');
			else if (i == ft_calc_rrarrb_a(*a, *b, temp->nbr))
				i = ft_apply_rrarrb(a, b, temp->nbr, 'b');
			else if (i == ft_calc_rrarb_a(*a, *b, temp->nbr))
				i = ft_apply_rrarb(a, b, temp->nbr, 'b');
			else
				temp = temp->next;
		}
	}
	return (*a);
}

t_stack	*ft_sort_b(t_stack **stack_a)
{
	t_stack	*stack_b;

	stack_b = NULL;
	if (ft_stack_size(*stack_a) > 3 && !ft_is_sorted(*stack_a))
		ft_pb(stack_a, &stack_b, 0);
	if (ft_stack_size(*stack_a) > 3 && !ft_is_sorted(*stack_a))
		ft_pb(stack_a, &stack_b, 0);
	if (ft_stack_size(*stack_a) > 3 && !ft_is_sorted(*stack_a))
		ft_sort_b_till_3(stack_a, &stack_b);
	if (!ft_is_sorted(*stack_a))
		ft_sort_three(stack_a);
	return (stack_b);
}

void	ft_sort_b_till_3(t_stack **stack_a, t_stack **stack_b)
{
	int		i;
	t_stack	*tmp;

	while (ft_stack_size(*stack_a) > 3 && !ft_is_sorted(*stack_a))
	{
		tmp = *stack_a;
		i = ft_rotate_type_ab(*stack_a, *stack_b);
		while (i >= 0)
		{
			if (i == ft_calc_rarb_a(*stack_a, *stack_b, tmp->nbr))
				i = ft_apply_rarb(stack_a, stack_b, tmp->nbr, 'a');
			else if (i == ft_calc_rarrb_a(*stack_a, *stack_b, tmp->nbr))
				i = ft_apply_rarrb(stack_a, stack_b, tmp->nbr, 'a');
			else if (i == ft_calc_rrarrb_a(*stack_a, *stack_b, tmp->nbr))
				i = ft_apply_rrarrb(stack_a, stack_b, tmp->nbr, 'a');
			else if (i == ft_calc_rrarb_a(*stack_a, *stack_b, tmp->nbr))
				i = ft_apply_rrarb(stack_a, stack_b, tmp->nbr, 'a');
			else
				tmp = tmp->next;
		}
	}
}

void ft_sort(t_stack **a)
{
	t_stack *b;
	int i, size;

	b = NULL;
	if (ft_stack_size(*a) == 2)
	{
		if ((*a)->nbr > (*a)->next->nbr)
			ft_sa(a, 0);
		return ;
	}
	b = ft_sort_b(a);
	*a = ft_sort_a(a, &b);
	i = ft_find_index(*a, ft_min(*a));
	size = ft_stack_size(*a);
	
	if (i <= size / 2)
	{
		while ((*a)->nbr != ft_min(*a))
		ft_ra(a, 0);
	}
	else
	{
		while ((*a)->nbr != ft_min(*a))
			ft_rra(a, 0);
	}
}
